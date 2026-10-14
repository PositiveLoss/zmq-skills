---
name: develop-zeromq-c
description: Build, review, debug and validate ZeroMQ integrations in C using libzmq C API; optional CZMQ. Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in C applications.
---

# Develop ZeroMQ in C

1. Inspect the existing C project, target platforms, dependency locks, ownership model and tests. Establish required message patterns, payload bounds and delivery/recovery behavior from the task.
2. Read [core.md](references/core.md) for topology, wire framing and operational rules. Specify bind/connect roles and a versioned binary contract before coding.
3. Read [integration.md](references/integration.md) for libzmq C API; optional CZMQ selection, runtime-specific ownership, a starting fragment and validation guidance. Verify APIs against the resolved dependency; fragments are adaptation guides unless explicitly marked as executed.
4. Implement one end-to-end flow with bounded queues, complete frame parsing, typed errors and an explicit owner shutdown. Integrate it with the application's lifecycle instead of creating sockets per message.
5. Read [verification.md](references/verification.md); run relevant native/runtime checks and a TCP exchange with a different implementation when interoperability is required. Include unavailable peer, malformed frame, cancellation, restart and slow-consumer cases according to the changed behavior.
6. Report versions, transport, limits, executed tests, guarantees and remaining gaps. Provide reproduction commands; do not call static validation a runtime compatibility test.

## Build C as the main service language

Read [application-service.md](references/application-service.md) for persistent
owner-loop architecture, multipart rejection, routing failures, shutdown and
the C/PHP wire contract. Use [router_service.c](assets/router_service.c) as a bounded
echo service fixture and run its --self-test before adapting it. Treat the fixture
as transport plumbing; add domain, authentication, durable recovery and operational
adapters before calling it a production service.

## Focused application

Consider C DSP/audio worker or language FFI adapter. Define the admission/recovery contract before translating the
example into production code. Keep durable state and business authorization
explicit in the surrounding application.
