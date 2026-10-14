# C++ integration

## Runtime and binding decisions

Use cppzmq as a header-only wrapper over libzmq; identify both versions and the link/runtime library. Resolve with the existing CMake/package manager rather than adding a second dependency system. Check exception or optional-result semantics for each send/receive in the selected cppzmq version. Wrap contexts, sockets and messages in RAII; declare/destroy sockets before their shared context is terminated. Assign one ordinary socket to one std::thread owner and use a bounded queue or inproc control socket for commands. Catch zmq::error_t and preserve error categories. Use zmq::message_t and byte spans; never assume a frame is NUL terminated. Do not hand a buffer to a zero-copy message and then reuse/free it; verify deleter threading and allocator compatibility. Design a finite stop policy so a destructor cannot wait forever for linger or a blocked owner. Receive all multipart parts and enforce protocol size limits before decoding. Use ASan/UBSan for the adapter and explicit concurrency tests; sanitizers alone do not prove delivery.

## Starting fragment

Adapt to the pinned dependency and the owner's resource scope. This fragment is
not a full service or an interoperability test. The DEALER examples expect a
ROUTER service that strips its routing ID and returns the three body frames.
Use a unique request ID in real applications; example-1 is a fixture only.
Socket timeouts bound individual operations; impose an overall application
deadline as well. Check errors from every option setter and endpoint operation
when turning abbreviated JVM/C++ fragments into an implementation.

```cpp
// cppzmq fragment on a single owner thread.
zmq::context_t context{1};
zmq::socket_t socket{context, zmq::socket_type::dealer};
socket.set(zmq::sockopt::linger, 0);
socket.set(zmq::sockopt::sndhwm, 128);
socket.set(zmq::sockopt::rcvhwm, 128);
socket.set(zmq::sockopt::sndtimeo, 1000);
socket.set(zmq::sockopt::rcvtimeo, 1000);
socket.set(zmq::sockopt::immediate, 1);
socket.connect(endpoint);
if (!socket.send(zmq::buffer("v1", 2), zmq::send_flags::sndmore) ||
    !socket.send(zmq::buffer("example-1", 9), zmq::send_flags::sndmore) ||
    !socket.send(zmq::buffer(payload.data(), payload.size()), zmq::send_flags::none)) {
    throw std::runtime_error("multipart send failed; reset socket as required");
}
// Receive all frames and validate the envelope; handle partial-send failure.
```

## Targeted checks

Run CMake/CTest, compiler warnings, clang-tidy if used, ASan/UBSan; buffer deleter and shutdown tests. Preserve existing project policies and add tests for externally
observable behavior, rather than merely mirroring implementation details.

## Primary sources

- Binding/runtime: https://github.com/zeromq/cppzmq
- Zero-copy deallocator: https://zeromq.github.io/libzmq/zmq_msg_init_data.html

Checked on 2026-10-14. Recheck the deployed version before relying on platform or API support.
