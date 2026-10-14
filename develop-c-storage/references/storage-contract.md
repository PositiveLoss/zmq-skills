# Persistence contract

Choose SQLite for an embedded database only after checking concurrency and deployment
requirements; use the existing remote database/client when shared durable coordination
is needed. Record selected SQLite/libpq versions and thread/connection usage policy.
Inspect open results even if the handle is non-null, and close partial resources.

For SQLite bind parameters rather than interpolating SQL. Use the right text/blob
length and lifetime: SQLITE_TRANSIENT copies; SQLITE_STATIC requires the buffer to
outlive its documented use. Treat embedded NULs as bytes. Reset/finalize statements
and preserve diagnostics before the connection is closed. Finalize statements
before closing the database; do not assume cleanup must succeed while work remains.

Specify transaction scope and write contention. Bound BUSY/LOCKED handling and
retries inside the original deadline; do not retry an uncertain commit as a new
effect. Select journal/synchronous settings from crash/durability requirements and
document tradeoffs. WAL does not remove all contention or make arbitrary network
filesystem deployment safe. Do not claim process-crash tests certify power-loss
durability. Store request digest/idempotency key and business effect in one
transaction when they share a database.

Test schema upgrades on prior realistic databases and preserve backups/recovery
policy. Check zero-row, constraint, rollback, malformed blob, busy, full disk,
and commit-then-response-loss behavior. For libpq inspect connection/result ownership,
parameterized query APIs and nonblocking state; never share a connection concurrently
without the client's permitted sequencing.

Primary sources:
- https://www.sqlite.org/c3ref/open.html
- https://www.sqlite.org/c3ref/stmt.html
- https://sqlite.org/lang_transaction.html
- https://www.postgresql.org/docs/current/libpq.html
