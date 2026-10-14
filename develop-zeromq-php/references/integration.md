# PHP extension and worker integration

Use ext-zmq only after resolving a compatible PHP ABI/SAPI build and checking its
upstream source, release and packaging. The PHP manual labels this extension
experimental; this is not proof that every current PHP release is unsupported.
Record tested PHP, extension and native libzmq versions. Composer cannot install
the native extension simply by satisfying an ext-zmq platform requirement. Never
guess a Windows DLL, ZTS/NTS or architecture match. Inspect php --ri zmq and the
actual deployed SAPI, not just the developer CLI.

Contexts can be persistent by default. For one-request tests use new ZMQContext(1,
false) and no persistent socket ID. For FPM/long-lived workers specify process-local
reuse, request isolation and recycling policy; never carry a timed-out REQ state
into the next web request. Construct native resources after fork in the child and
do not transfer handles across runtimes or threads.

Use strings as byte arrays; compare bytes strictly and validate declared UTF-8
only for text fields. Avoid unserialize on untrusted payloads. recv/recvMulti in
nonblocking mode can return false; errors may throw ZMQSocketException. Check both
paths according to the resolved extension. Empty string is a valid frame, not
would-block. Verify sendMulti's return contract; avoid retrying an uncertain
partially-sent multipart message blindly.

Use ZMQPoll or finite operations with a monotonic hrtime-based application budget.
Polling does not acknowledge remote completion. Fibers alone do not make a blocking
native recv asynchronous; use the application's supported loop integration or a
bounded sidecar/worker. Keep PHP HTTP request deadlines distinct from business
completion and use durable idempotency at the C service/storage boundary.

The CLI fixture sends [v1, random ASCII ID, binary payload] through DEALER. The C
ROUTER receives [routing ID, v1, ID, payload] and returns those frames. It does
not include a REQ delimiter. Native ROUTER limits bound the echo fixture's frame
count/size; PHP recvMulti can allocate before application validation, so test peers,
transport limits and aggregate memory separately for untrusted deployments.

The extension does not expose every C lifecycle API. Do not invent close()/term()
methods. Drop nonpersistent sockets/poller references before context references;
use explicit finite linger and a controlled process lifecycle. Verify actual native
cleanup behavior on the deployed SAPI. Use CURVE/ZAP only after checking constants,
native build capability and authentication policy; never infer TLS from TCP.

Primary sources checked on 2026-10-14:
- https://www.php.net/manual/en/book.zmq.php
- https://github.com/zeromq/php-zmq
- https://www.php.net/manual/en/zmqcontext.construct.php
- https://www.php.net/manual/en/zmqsocket.recv.php
- https://www.php.net/manual/en/zmqsocket.recvmulti.php
- https://www.php.net/manual/en/zmqsocket.sendmulti.php
- https://www.php.net/manual/en/zmqpoll.poll.php
- https://www.php.net/manual/en/class.zmq.php

Run php -l assets/request.php for syntax and php assets/request.php endpoint for
native runtime behavior on a machine with the verified extension. Neither check
has been executed if PHP/ext-zmq is unavailable.
