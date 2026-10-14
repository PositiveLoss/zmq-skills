# Service contract

Choose an established transport/parser matching the product. libcurl is an HTTP
client, not an HTTP server. For an HTTP server inspect the existing C server
library's parser/TLS/lifecycle API rather than adapting a raw TCP echo into HTTP.
Use ZeroMQ for controlled message flows with explicit application recovery;
do not label it a durable queue. Use TLS/CURVE appropriate to the chosen transport.

For stream sockets define a bounded incremental parser with exact lengths,
versioning and integer byte order. TCP recv boundaries do not delimit messages;
EOF is not a zero-length successful request. Handle partial sends, retryable
would-block outcomes and half-closes explicitly. Bound headers, bodies, total
buffered bytes, accepted connections, worker slots and outstanding requests.

Keep sockets in owner loops and CPU/blocking work in bounded workers. Set an
overall operation budget including queue wait, transport, domain work and commit.
Publish health/readiness separately: bind success is not dependency readiness.
Measure enqueue separately from acknowledged business completion.

For retries of side effects couple a durable idempotency record to the operation
transaction, or require sink deduplication. For peer/session restarts use fencing
tokens and reject retired replies. Avoid claiming exactly-once from transport.
Log correlation/error categories and queue/load measurements without payload
secrets. Define a bounded drain and unresolved-work recovery at shutdown.

Primary client API: https://curl.se/libcurl/c/
