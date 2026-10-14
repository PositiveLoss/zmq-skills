---
name: develop-zeromq-kotlin
description: Build, review, debug and validate ZeroMQ integrations in Kotlin using JeroMQ on JVM; C interop on Native. Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in Kotlin applications.
---

# Develop ZeroMQ in Kotlin

1. Inspect the existing Kotlin project, target platforms, dependency locks, ownership model and tests. Establish required message patterns, payload bounds and delivery/recovery behavior from the task.
2. Read [core.md](references/core.md) for topology, wire framing and operational rules. Specify bind/connect roles and a versioned binary contract before coding.
3. Read [integration.md](references/integration.md) for JeroMQ on JVM; C interop on Native selection, runtime-specific ownership, a starting fragment and validation guidance. Verify APIs against the resolved dependency; fragments are adaptation guides unless explicitly marked as executed.
4. Implement one end-to-end flow with bounded queues, complete frame parsing, typed errors and an explicit owner shutdown. Integrate it with the application's lifecycle instead of creating sockets per message.
5. Read [verification.md](references/verification.md); run relevant native/runtime checks and a TCP exchange with a different implementation when interoperability is required. Include unavailable peer, malformed frame, cancellation, restart and slow-consumer cases according to the changed behavior.
6. Report versions, transport, limits, executed tests, guarantees and remaining gaps. Provide reproduction commands; do not call static validation a runtime compatibility test.

## Focused application

Consider IMU telemetry/control gateway with Android lifecycle tests. Define the admission/recovery contract before translating the
example into production code. Keep durable state and business authorization
explicit in the surrounding application.
