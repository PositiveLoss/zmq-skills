# Python integration

## Runtime and binding decisions

Prefer `pyzmq`; pin its resolved version with the project's lockfile (uv when already used). Inspect `zmq.pyzmq_version()`, `zmq.zmq_version()` and `zmq.has("curve")` separately. Use `zmq.asyncio.Context` and await multipart operations for asyncio applications. Keep one socket owner task with a bounded mailbox; do not run blocking `zmq.Context` operations on the event loop. Handle `zmq.Again`, cancellation and the REQ lifecycle explicitly. In Django/FastAPI start resources in the process lifespan, after worker fork, and shut down owners before terminating their context. Do not pass contexts/sockets across fork or assume free-threaded Python makes sockets shareable. Use bytes; prohibit pickle deserialization for untrusted inputs. Start with copying sends; for `copy=False` keep buffers unchanged/alive until the binding's completion tracker allows reuse. Test cancellation and event-loop compatibility with the selected loop, including rsloop if used, instead of asserting drop-in behavior.

## Starting fragment

Adapt to the pinned dependency and the owner's resource scope. This fragment is
not a full service or an interoperability test. The DEALER examples expect a
ROUTER service that strips its routing ID and returns the three body frames.
Use a unique request ID in real applications; example-1 is a fixture only.
Socket timeouts bound individual operations; impose an overall application
deadline as well. Check errors from every option setter and endpoint operation
when turning abbreviated JVM/C++ fragments into an implementation.

```python
import asyncio
import zmq
import zmq.asyncio

async def request(endpoint: str, payload: bytes) -> list[bytes]:
    ctx = zmq.asyncio.Context()
    sock = ctx.socket(zmq.DEALER)
    try:
        sock.setsockopt(zmq.LINGER, 0)  # intentional discard on close
        sock.setsockopt(zmq.SNDHWM, 128)
        sock.setsockopt(zmq.RCVHWM, 128)
        sock.setsockopt(zmq.IMMEDIATE, 1)
        sock.connect(endpoint)
        async with asyncio.timeout(2):  # Python 3.11+
            await sock.send_multipart([b"v1", b"example-1", payload])
            reply = await sock.recv_multipart()
        if len(reply) != 3 or reply[:2] != [b"v1", b"example-1"]:
            raise ValueError("invalid reply envelope")
        return reply
    finally:
        sock.close()
        ctx.term()
```

## Targeted checks

Run Ruff, Pyright, pytest; cancellation, fork/lifespan, RSS and buffer lifetime. Preserve existing project policies and add tests for externally
observable behavior, rather than merely mirroring implementation details.

## Primary sources

- Binding/runtime: https://pyzmq.readthedocs.io/en/latest/api/zmq.asyncio.html
- Buffer ownership and threads: https://pyzmq.readthedocs.io/en/latest/howto/morethanbindings.html

Checked on 2026-10-14. Recheck the deployed version before relying on platform or API support.
