# Loop lifecycle

Use the existing framework; choose libuv for a new cross-platform I/O design only
when its model matches the application. Preserve one owner loop and communicate
through the framework's supported wake-up/async path. Do not assume all APIs or
handles are thread-safe. Make request state explicit: new, pending, completing,
cancel-requested, completed, closing, closed. A cancellation request is not evidence
that a callback or remote side effect cannot still occur.

Keep a retained context alive until every completion/close callback that can
reference it has finished. Prevent callbacks from accessing already-freed parent
state. In libuv, keep handle storage until its close callback; stopping the loop
is not closing every handle. Drain close callbacks before loop disposal. Track
both handles and in-flight requests and test partial setup cleanup.

Bound each iteration's work, buffered bytes, pending jobs and worker slots. Use
monotonic local deadlines with bounded recomputation after interrupts. Handle
timer overruns and avoid periodic drift when the product requires stable cadence.

For ZeroMQ start with a dedicated socket owner plus zmq_poll and a bounded command
path. If integrating ZMQ_FD with another poller, read the exact libzmq contract:
the FD is an edge notification, not the TCP socket and not a source of payload
bytes. Query ZMQ_EVENTS, drain permitted nonblocking work and recheck state before
rearming. Limit batches to preserve fairness without losing future notifications.
Verify idle behavior, readiness races and spin CPU on the selected platform.

Primary references:
- https://docs.libuv.org/en/v1.x/design.html
- https://docs.libuv.org/en/v1.x/handle.html
- https://docs.libuv.org/en/v1.x/poll.html
- https://zeromq.github.io/libzmq/zmq_getsockopt.html
