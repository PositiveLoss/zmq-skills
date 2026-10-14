---
name: develop-zeromq
description: Design, implement, debug, secure and validate ZeroMQ message systems across languages. Use for socket-pattern selection, REQ/REP recovery, DEALER/ROUTER framing, PUB/SUB readiness, PUSH/PULL workers, HWM/backpressure, CURVE/ZAP, interoperability, cancellation and shutdown.
---

# Develop ZeroMQ systems

1. Inspect the repository, existing bindings, deployment targets, dependency locks and tests. Preserve its toolchain. Establish payload sizes/rates, peer counts, delivery needs, latency budget and failure policy from task context; ask only for choices that affect the contract materially.
2. Read [core.md](references/core.md) for pattern, framing, ownership and operating rules. Write a compact message contract and choose one topology. Include bind/connect roles, codec, limits, readiness, retry/idempotency and shutdown budgets.
3. Select the binding using the language table below. Inspect the exact version's upstream API, supported transports/security and native build prerequisites. Do not assert full libzmq parity for native ports or assume a currently latest release.
4. Build the smallest end-to-end path with an owner per socket, complete multipart parsing, bounded admission and explicit error outcomes. Keep transport routing distinct from authorization.
5. Read [use-cases.md](references/use-cases.md) when adapting ASR, crawling, IMU/drone, inference, DSP or verified-code applications.
6. Use [verification.md](references/verification.md) to select meaningful failure and interoperability checks. Run `python3 scripts/check_libzmq.py` for a bounded local native-library smoke check; it requires a loadable libzmq and is not a certification of language wrappers. Pass `--c-server PATH` for a separately compiled C TCP responder, or `--c-adapter PATH` for the C inproc shared-library fixture. These optional fixtures are in develop-zeromq-c when that skill is installed; default diagnostics need no sibling skill.
7. Deliver the topology/protocol, implementation, exact versions, executed checks and unresolved platform gaps. Report concrete guarantees and observed evidence; distinguish queue acceptance from application completion.

## Language routes

| Target | Skill | Initial binding route |
| --- | --- | --- |
| Python | develop-zeromq-python | PyZMQ and zmq.asyncio |
| Rust | develop-zeromq-rust | zmq crate plus native libzmq |
| Go | develop-zeromq-go | pebbe/zmq4 plus cgo/libzmq |
| Java | develop-zeromq-java | JeroMQ; assess JNI separately |
| Kotlin | develop-zeromq-kotlin | JeroMQ on JVM; explicit Native adapter |
| Scala | develop-zeromq-scala | JeroMQ via Java interop |
| C++ | develop-zeromq-cpp | cppzmq plus libzmq |
| C | develop-zeromq-c | stable libzmq C API |
| Lean 4 | develop-zeromq-lean4 | C FFI bridge or sidecar |

Read only the selected language skill if available. Each language skill includes
its own operating and verification references and can be used independently.
