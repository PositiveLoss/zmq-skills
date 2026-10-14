# Verification and troubleshooting

Choose checks from this matrix according to the changed behavior. Keep evidence
separate from proposed tests. Do not claim a runtime was tested from lint alone.

| Scenario | Evidence to collect |
| --- | --- |
| Cross-language happy path | Exact byte equality, Unicode UTF-8, empty and embedded-NUL payloads |
| Multipart mismatch | Frame order/count, empty delimiters, preservation of routing IDs |
| Peer unavailable | Finite send/receive/poll deadline, explicit error mapping, bounded shutdown |
| Late reply or retry | Correlation, deduplication and one application effect per idempotency key |
| Slow consumer/HWM | RSS, latency, rejection/drop counters; prove the selected saturation policy |
| Restart | Reconnect, recovery/resync, and stale reply handling |
| PUB/SUB readiness | Observed subscription or data acknowledgement; sequence-gap/resync behavior |
| Cancellation | Local owner stops promptly; remote work outcome is explicitly represented |
| Security | Authorized key succeeds; wrong server/client key fails; secrets are absent from logs |
| Lifecycle | Owners close sockets, threads join, bounded context termination and no handle leaks |
| Oversized/malformed input | Bounded parser resources, safe rejection, complete multipart consumption |

Record implementation/binding/runtime versions, OS/architecture, transport,
pattern, payload distribution, peers, HWM, linger and timeouts. Compare sustained
throughput and p50/p95/p99 latency at an equal load; include CPU and RSS. Use an
application acknowledgement for end-to-end timing. Separate startup/warm-up and
transport enqueue timing from completed business work. Avoid changing several
knobs at once.

When diagnosing a hang, inspect socket state, ownership, option application,
pending messages and shutdown ordering. When diagnosing loss, inspect readiness,
PUB semantics, subscription prefix, sequence numbers and application retries.
When diagnosing an ABI issue, inspect native library resolution and package
versions. Never fix a race by adding an arbitrary sleep.

Use socket monitoring for connection/handshake observations, not as evidence of
business delivery: https://zeromq.github.io/libzmq/zmq_socket_monitor.html
Inspect reliable request/reply designs when persistence or retries are needed:
https://zguide.zeromq.org/docs/chapter4/
