#!/usr/bin/env python3
"""Bounded native libzmq diagnostics; Python stdlib only, not a PyZMQ test."""
from __future__ import annotations

import argparse
import ctypes as c
import ctypes.util
import errno
import json
from pathlib import Path
import subprocess
import threading
import time

REQ, REP, DEALER, ROUTER, PULL, PUSH = 3, 4, 5, 6, 7, 8
LINGER, RCVTIMEO, SNDTIMEO, SNDHWM, RCVHWM, RCVMORE = 17, 27, 28, 23, 24, 13
EFSM = 156384763  # stable libzmq ZMQ_HAUSNUMERO + 51


class Native:
    def __init__(self) -> None:
        name = ctypes.util.find_library("zmq")
        if not name:
            raise RuntimeError("libzmq not found; install the native runtime library")
        self.lib = c.CDLL(name)
        signatures = {
            "zmq_ctx_new": (c.c_void_p, []),
            "zmq_ctx_term": (c.c_int, [c.c_void_p]),
            "zmq_socket": (c.c_void_p, [c.c_void_p, c.c_int]),
            "zmq_close": (c.c_int, [c.c_void_p]),
            "zmq_setsockopt": (c.c_int, [c.c_void_p, c.c_int, c.c_void_p, c.c_size_t]),
            "zmq_getsockopt": (c.c_int, [c.c_void_p, c.c_int, c.c_void_p, c.POINTER(c.c_size_t)]),
            "zmq_bind": (c.c_int, [c.c_void_p, c.c_char_p]),
            "zmq_connect": (c.c_int, [c.c_void_p, c.c_char_p]),
            "zmq_send": (c.c_int, [c.c_void_p, c.c_void_p, c.c_size_t, c.c_int]),
            "zmq_recv": (c.c_int, [c.c_void_p, c.c_void_p, c.c_size_t, c.c_int]),
            "zmq_errno": (c.c_int, []),
            "zmq_strerror": (c.c_char_p, [c.c_int]),
            "zmq_version": (None, [c.POINTER(c.c_int)] * 3),
        }
        for name, (result, args) in signatures.items():
            fn = getattr(self.lib, name)
            fn.restype, fn.argtypes = result, args
        self.context = self.lib.zmq_ctx_new()
        if not self.context:
            self.error()
        self.sockets: list[int] = []

    def error(self) -> None:
        number = self.lib.zmq_errno()
        raise OSError(number, self.lib.zmq_strerror(number).decode())

    def check(self, value: int) -> int:
        if value < 0:
            self.error()
        return value

    def option(self, socket: int, key: int, value: int) -> None:
        arg = c.c_int(value)
        self.check(self.lib.zmq_setsockopt(socket, key, c.byref(arg), c.sizeof(arg)))

    def socket(self, kind: int) -> int:
        socket = self.lib.zmq_socket(self.context, kind)
        if not socket:
            self.error()
        self.sockets.append(socket)
        for key, value in [(LINGER, 0), (RCVTIMEO, 1000), (SNDTIMEO, 1000), (SNDHWM, 16), (RCVHWM, 16)]:
            self.option(socket, key, value)
        return socket

    def pair(self, receiver: int, sender: int, name: bytes) -> tuple[int, int]:
        rx, tx = self.socket(receiver), self.socket(sender)
        self.check(self.lib.zmq_bind(rx, name))
        self.check(self.lib.zmq_connect(tx, name))
        return rx, tx

    def send(self, socket: int, frames: list[bytes]) -> None:
        if not frames:
            raise ValueError("a message requires at least one frame")
        for index, frame in enumerate(frames):
            data = c.create_string_buffer(frame)
            self.check(self.lib.zmq_send(socket, data, len(frame), 2 if index < len(frames) - 1 else 0))

    def receive(self, socket: int) -> list[bytes]:
        frames = []
        while True:
            buffer = c.create_string_buffer(65536)
            size = self.check(self.lib.zmq_recv(socket, buffer, len(buffer), 0))
            if size > len(buffer):
                raise ValueError("diagnostic frame exceeds fixed receive capacity")
            frames.append(buffer.raw[:size])
            more, length = c.c_int(), c.c_size_t(c.sizeof(c.c_int))
            self.check(self.lib.zmq_getsockopt(socket, RCVMORE, c.byref(more), c.byref(length)))
            if not more.value:
                return frames
            if len(frames) >= 16:
                raise ValueError("diagnostic multipart limit exceeded")

    def close(self) -> None:
        for socket in self.sockets:
            self.check(self.lib.zmq_close(socket))
        self.sockets.clear()
        while True:
            result = self.lib.zmq_ctx_term(self.context)
            if result == 0:
                return
            if self.lib.zmq_errno() != errno.EINTR:
                self.error()


def require(value: bool, detail: str) -> None:
    if not value:
        raise AssertionError(detail)


def expect_errno(fn, number: int) -> None:
    try:
        fn()
    except OSError as exc:
        require(exc.errno == number, f"expected errno {number}, received {exc.errno}")
    else:
        raise AssertionError(f"expected errno {number}")


def c_exchange(native: Native, server_path: Path, payload: bytes) -> None:
    proc = subprocess.Popen([str(server_path.resolve())], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    try:
        # Bound readiness without sleeping or blocking indefinitely on readline.
        ready: list[bytes] = []
        def read_ready() -> None:
            assert proc.stdout is not None
            ready.append(proc.stdout.readline())
        reader = threading.Thread(target=read_ready, daemon=True)
        reader.start()
        reader.join(timeout=3)
        require(bool(ready), "C server readiness timed out")
        endpoint = ready[0].strip()
        if not endpoint:
            _, error = proc.communicate(timeout=3)
            raise RuntimeError(f"C server failed before readiness: {error.decode(errors='replace')}")
        require(endpoint.startswith(b"tcp://127.0.0.1:"), "invalid C endpoint")
        socket = native.socket(REQ)
        native.check(native.lib.zmq_connect(socket, endpoint))
        native.send(socket, [payload])
        require(native.receive(socket) == [payload], "C/Python binary echo mismatch")
        native.send(socket, [b"ACK"])
        _, error = proc.communicate(timeout=3)
        require(proc.returncode == 0, f"C server failed: {error.decode(errors='replace')}")
    finally:
        if proc.poll() is None:
            proc.kill()
            proc.communicate(timeout=3)


def c_inproc_exchange(native: Native, adapter_path: Path, payloads: list[bytes]) -> None:
    adapter = c.CDLL(str(adapter_path.resolve()))
    adapter.fixture_open_rep.argtypes = [c.c_void_p, c.c_char_p]
    adapter.fixture_open_rep.restype = c.c_void_p
    adapter.fixture_echo_once.argtypes = [c.c_void_p]
    adapter.fixture_echo_once.restype = c.c_int
    endpoint = b"inproc://c-adapter"
    rep = adapter.fixture_open_rep(native.context, endpoint)
    require(bool(rep), "C adapter socket creation failed")
    native.sockets.append(rep)
    req = native.socket(REQ)
    native.check(native.lib.zmq_connect(req, endpoint))
    for payload in payloads:
        native.send(req, [payload])
        require(adapter.fixture_echo_once(rep) == 0, "C adapter echo failed")
        require(native.receive(req) == [payload], "C/Python inproc bytes mismatch")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--c-server", type=Path)
    parser.add_argument("--c-adapter", type=Path, help="compiled echo_inproc shared library")
    args = parser.parse_args()
    native = Native()
    checks: list[str] = []
    major, minor, patch = c.c_int(), c.c_int(), c.c_int()
    native.lib.zmq_version(c.byref(major), c.byref(minor), c.byref(patch))
    started = time.monotonic()
    try:
        rep, req = native.pair(REP, REQ, b"inproc://req-rep")
        payloads = [b"", b"A\x00B\xff", "Привіт, ZeroMQ".encode(), bytes(range(256))]
        for payload in payloads:
            native.send(req, [payload])
            require(native.receive(rep) == [payload], "request bytes mismatch")
            native.send(rep, [payload])
            require(native.receive(req) == [payload], "reply bytes mismatch")
        checks.append("REQ/REP binary, empty, UTF-8 and byte-range round trips")
        native.option(req, RCVTIMEO, 50)
        native.send(req, [b"pending"])
        expect_errno(lambda: native.receive(req), errno.EAGAIN)
        expect_errno(lambda: native.send(req, [b"second"]), EFSM)
        require(native.receive(rep) == [b"pending"], "pending request mismatch")
        native.send(rep, [b"late"])
        require(native.receive(req) == [b"late"], "late reply mismatch")
        checks.append("REQ timeout retains state; second send returns EFSM; late reply recovers")
        router, dealer = native.pair(ROUTER, DEALER, b"inproc://route")
        envelope = [b"v1", b"id-1", b"A\x00B", b""]
        native.send(dealer, envelope)
        routed = native.receive(router)
        require(len(routed) == len(envelope) + 1 and routed[1:] == envelope, "routing/multipart mismatch")
        native.send(router, routed)
        require(native.receive(dealer) == envelope, "routed reply mismatch")
        checks.append("DEALER/ROUTER multipart and routing envelope")
        pull, push = native.pair(PULL, PUSH, b"inproc://pipeline")
        native.send(push, [b"job\x00data"])
        require(native.receive(pull) == [b"job\x00data"], "pipeline mismatch")
        native.option(pull, RCVTIMEO, 50)
        timeout_start = time.monotonic()
        expect_errno(lambda: native.receive(pull), errno.EAGAIN)
        require(time.monotonic() - timeout_start < 2, "receive deadline exceeded")
        checks.append("PUSH/PULL binary data and unavailable-data deadline")
        if args.c_adapter:
            c_inproc_exchange(native, args.c_adapter, payloads)
            checks.append("C adapter/Python ctypes inproc interoperability: four payload cases")
        if args.c_server:
            for payload in payloads:
                c_exchange(native, args.c_server, payload)
            checks.append("C responder/Python ctypes TCP interoperability: four payload cases")
    finally:
        native.close()
    print(json.dumps({"libzmq": f"{major.value}.{minor.value}.{patch.value}", "checks": checks,
                      "elapsed_seconds": round(time.monotonic() - started, 3)}, ensure_ascii=False))


if __name__ == "__main__":
    main()
