# C integration

## Runtime and binding decisions

Use the stable libzmq C API as the interoperability baseline; choose CZMQ only when its higher-level ownership/event-loop abstractions benefit the project. Resolve headers and runtime library together through the project's native build system. Check every pointer, option setter and integer return value and capture zmq_errno promptly. Use zmq_msg_init/recv/data/size/close for arbitrary frames; zmq_recv into a fixed buffer can report the full frame length even when storage is shorter, so never read beyond capacity. Initialize and close messages exactly once along every successful initialization path. Treat zmq_msg_init_data ownership transfer and its arbitrary-thread deallocator as a separate FFI contract. Use a single owner for each socket and a structured cleanup path; terminate contexts only after closing sockets. Handle EINTR with the remaining deadline and ETERM during shutdown. Enforce frame counts/aggregate limits; reject an invalid multipart envelope only after draining the message or resetting the socket safely. Keep uint sizes/endianness explicit and avoid unaligned structure casts. Use bounded loopback examples in assets/echo_rep.c, assets/request.c and assets/echo_inproc.c as a starting point; extend them into persistent owners for services.

## Starting fragment

Adapt to the pinned dependency and the owner's resource scope. This fragment is
not a full service or an interoperability test. The DEALER examples expect a
ROUTER service that strips its routing ID and returns the three body frames.
Use a unique request ID in real applications; example-1 is a fixture only.
Socket timeouts bound individual operations; impose an overall application
deadline as well. Check errors from every option setter and endpoint operation
when turning abbreviated JVM/C++ fragments into an implementation.

```c
/* Stable options before bind/connect; check all calls in production. */
void *context = zmq_ctx_new();
void *socket = context ? zmq_socket(context, ZMQ_DEALER) : NULL;
int timeout_ms = 1000, linger_ms = 0, hwm = 128;
/* On a failed creation, clean up context and return the captured error. */
/* zmq_setsockopt(socket, ZMQ_LINGER, &linger_ms, sizeof linger_ms); */
/* Also set SNDHWM, RCVHWM, SNDTIMEO, RCVTIMEO with checked results. */
/* Use zmq_msg_t for length-safe receive; do not treat bytes as a C string. */
/* See complete checked single-frame examples in assets/. */
```

## Targeted checks

Run compiler warnings, ASan/UBSan, native integration checks; error/cleanup paths and binary lengths. Preserve existing project policies and add tests for externally
observable behavior, rather than merely mirroring implementation details.

## Primary sources

- Binding/runtime: https://zeromq.github.io/libzmq/zmq_msg_recv.html
- Zero-copy deallocator: https://zeromq.github.io/libzmq/zmq_msg_init_data.html

Checked on 2026-10-14. Recheck the deployed version before relying on platform or API support.

## Complete C fixtures

Build the TCP responder/requester with the platform's libzmq headers and library:

```sh
cc -std=c11 -Wall -Wextra -Werror assets/echo_rep.c -lzmq -o echo_rep
cc -std=c11 -Wall -Wextra -Werror assets/request.c -lzmq -o request
```

Start echo_rep and use its printed endpoint for request. The responder receives
one binary request, echoes it, then waits for a fixture ACK before exiting.
The requester uses finite linger for the final ACK. Neither fixture implements
business completion, persistence, retries or a full application protocol.

For a shared-context interoperability fixture on Linux, compile:

```sh
cc -std=c11 -Wall -Wextra -Werror -fPIC -shared assets/echo_inproc.c -lzmq -o echo_inproc.so
```

Use develop-zeromq's diagnostic with `--c-adapter /absolute/path/echo_inproc.so`
when that skill is installed. This fixture demonstrates C/Python stdlib ctypes
inproc exchange on the same owner thread. It does not verify PyZMQ or TCP.
Use the platform's normal shared-library flags on macOS/Windows and verify
exported fixture symbols and matching libzmq instances there.
