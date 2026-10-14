# C-owned ZeroMQ application service

Keep the application composition root in C. Own context, transport, configuration,
domain workers and persistence explicitly. Separate domain status from transport
errors. A PHP/Python client is an adapter to the C service, not its lifecycle owner.

Use one ROUTER owner loop, bounded mailboxes and finite polling. Keep compute and
blocking storage in bounded workers; carry immutable request data or transferred
buffers with documented release points. Store request ID, attempt/session and
remaining budget in the real protocol. A received message or echo is not a committed
business effect. Couple durable idempotency to the effect when retry safety matters.

The bundled router_service.c fixture accepts exactly [routing_id, v1, id, payload]
on ROUTER and echoes the full routing envelope. ID is 1..64 bytes, routing ID
1..255, payload 0..65536; client body is [v1, id, payload]. It receives initialized
zmq_msg_t objects and closes each exactly once. Invalid envelopes or multipart
send failures are fail-stop: the process closes the socket rather than continuing
an ambiguous partial multipart sequence. Adapt rejection/reset policy for a real
multi-tenant service so one bad client cannot trivially stop all work.

The four local message slots bound parser work, not libzmq allocation before
parsing. MAXMSGSIZE and HWM do not establish a hard aggregate/process memory cap
for hostile multipart traffic. Add and stress-test accepted-peer, in-flight-byte
and admission limits at a controlled boundary; do not claim transport memory
safety from the self-test.

Configure HWM, MAXMSGSIZE, ROUTER_MANDATORY, finite send/receive timeouts and linger
before bind/connect. Mandatory routing surfaces unavailable/full-peer outcomes;
POLLOUT on ROUTER does not mean every selected peer can receive. Decide whether
an EHOSTUNREACH/EAGAIN result rejects, retries or abandons the application operation.

Signal handlers only set a sig_atomic_t stop flag in this fixture. Do not allocate,
log or call ZeroMQ in a POSIX signal handler. For production cross-thread stop use
an owner control/wake-up path, with a deadline and tested native implementation.
Stop admission, resolve/drain in-flight work, close owners, join workers and then
terminate the context. Zero linger intentionally discards queued unsent data.

Build with the platform's real headers/library:

```sh
cc -std=c11 -Wall -Wextra -Werror -pedantic assets/router_service.c -lzmq -o router_service
./router_service --self-test
./router_service tcp://127.0.0.1:5555
```

Use develop-zeromq-php's request.php against that TCP endpoint when PHP/ext-zmq
is installed. The inproc self-test does not certify TCP, PHP or security behavior.
The echo service accepts a loopback TCP endpoint by default and implements no
CURVE; add a checked authentication configuration before wider deployment.

Primary references:
- https://zeromq.github.io/libzmq/zmq_socket.html
- https://zeromq.github.io/libzmq/zmq_getsockopt.html
- https://zeromq.github.io/libzmq/zmq_msg_recv.html
