# Messaging contract and operating rules

Treat ZeroMQ as a messaging transport. Specify persistence, acknowledgements,
retry limits, duplicate handling, and recovery in the application when required.
Do not claim delivery or completion from a successful local send.

## Pattern selection

| Need | Pattern | Design obligation |
| --- | --- | --- |
| Sequential command/reply | REQ/REP | Preserve alternating operations; recover the socket state after a timeout |
| Concurrent requests | DEALER/ROUTER | Correlate replies and bound in-flight work; preserve routing frames |
| Distribute independent work | PUSH/PULL | Add a separate result/acknowledgement path if completion matters |
| Broadcast live telemetry | PUB/SUB | Design for missing updates, subscription propagation and slow consumers |
| Forward subscriptions | XSUB/XPUB | Specify readiness and subscription forwarding; bound proxy resources |
| Local control channel | PAIR over inproc | Share a context and dedicate one socket to each owner |

Prefer stable socket types by default. Check draft support explicitly before
using CLIENT/SERVER or RADIO/DISH. Do not assume native ports expose libzmq's
complete option set. Use tcp:// for initial cross-language tests; verify ipc://
per platform and binding. Use inproc:// only inside one implementation/context.

## Ownership and framing

Assign each ordinary socket to one owner thread; share contexts only as supported
by the binding. Serialize coroutine access and the request/reply lifecycle.
Keep payloads as bytes. Specify codec, version, maximum frame count, frame sizes
and total message size. Receive the complete accepted multipart message before
application parsing. On a frame/count/aggregate violation, drain only within an
explicit budget or close/reset the owner socket; never continue on an ambiguous
partial message or drain an attacker-controlled stream without bounds.
Do not cast a C struct onto the wire. Specify integer byte order and units.

For a DEALER-to-ROUTER application message [version, request_id, payload],
the ROUTER sees [routing_id, version, request_id, payload]. Preserve routing_id
in replies. A REQ peer additionally introduces an empty delimiter; do not add
that delimiter blindly to DEALER-to-ROUTER traffic. Treat routing IDs as transport
addresses, not authenticated user IDs. Require a protocol-specific parser.

## Bounds and cancellation

Choose finite queue, message, in-flight and deadline budgets. Account for queues
per peer and socket: HWM measures messages, not a fixed process memory budget.
Set compatible options before bind/connect and check setter results. Treat
EAGAIN as a timeout/would-block outcome, EFSM as a protocol-state defect, EINTR
according to the remaining deadline, and ETERM as shutdown. A receive timeout
does not cancel remote processing; use idempotency and explicit cancellation.

For REQ retry, close/recreate the owner socket with an intentional linger policy,
or verify REQ_RELAXED plus REQ_CORRELATE support and test late replies. Retrying
side effects still requires deduplication. For durable effects, atomically
couple the idempotency ledger to the effect, or require sink-side deduplication;
a volatile cache cannot guarantee one effect through crashes. Choose a monotonic local deadline;
do not transfer monotonic timestamps across hosts. Transmit a remaining budget,
or define a clock-synchronization policy for wall-clock expiry.

Specify whether saturation blocks, rejects, drops, or replaces work. PUB can
drop updates; do not present it as a durable log. For latest-state telemetry,
use sequence numbers plus snapshot/resync. CONFLATE is inappropriate for a
multipart envelope. A connected event does not prove subscription readiness.
Use an observed subscription/data acknowledgement with a deadline, not a sleep.

## Shutdown and security

Stop admission, signal owners, drain or discard according to the documented
budget, close sockets in their owners, join workers, then terminate the context.
Use an explicit finite linger or zero only when discarding queued sends is
acceptable. Do not let a finalizer close a live socket from another thread.

Bind examples to loopback. For network deployments verify CURVE support,
pin the server public key, authenticate/authorize clients through an appropriate
ZAP policy, and manage secret keys outside source/logs. CURVE is not TLS; PLAIN
alone does not encrypt payloads. Limit untrusted messages and parser complexity.

## Primary references

- Socket semantics: https://zeromq.github.io/libzmq/zmq_socket.html
- Options: https://zeromq.github.io/libzmq/zmq_setsockopt.html
- Multipart receive: https://zeromq.github.io/libzmq/zmq_msg_recv.html
- Shutdown: https://zeromq.github.io/libzmq/zmq_ctx_term.html
- CURVE: https://zeromq.github.io/libzmq/zmq_curve.html
- Authentication: https://rfc.zeromq.org/spec/27/

Consult the exact deployed version. These links were checked on 2026-10-14;
they are not a promise about future versions or a certification of native ports.
