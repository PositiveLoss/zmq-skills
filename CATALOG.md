# ZeroMQ and C application skills

40 independent skills: 11 ZeroMQ, 7 new C application skills, 22 existing C skills
extended for complete application development. Each directory includes SKILL.md
and its own linked resources. C is the main implementation language in the C
application workflows; PHP/Python are optional client/adapter integrations.

## Validation

- All 40 skill structures, metadata and local reference links validated.
- C11 codec, CLI and ROUTER fixture built with -Wall -Wextra -Werror -pedantic.
- Codec golden/binary/empty/truncation/size and CLI/UTF-8/argument checks passed.
- C ROUTER inproc binary/empty/correlation, malformed/extra/missing/max-frame
  acceptance and rejection checks passed on libzmq 4.3.5.
- C/Python ctypes inproc interoperability passed; this is not a PyZMQ test.
- GCC ASan+UBSan codec and ROUTER test paths passed with detect_leaks=0.
  LeakSanitizer is unavailable in this environment; no leak-check claim.
- PHP/ext-zmq and CMake were unavailable; PHP syntax/runtime and CMake
  configure/build/install were not executed. Windows/macOS were not tested.
- TCP/IPC native tests were blocked by the execution environment.

The C codec format and the ZeroMQ multipart envelope are different fixtures.
The echo service is a bounded adaptation fixture, not a production authenticated
service, durability guarantee or hard process-memory cap. Read its production
adaptation notes before use.

## Skills

| Skill | Purpose |
| --- | --- |
| analyze-c-assembly | Analyze C Assembly. Use for inspect compiler output, vectorization and hot code in C applications, services and libraries. |
| audit-c-ffi-boundary | Audit C FFI Boundaries. Use for audit python, rust and go bindings to c in C applications, services and libraries. |
| audit-c-memory-safety | Audit C Memory Safety. Use for audit bounds, initialization and allocation lifetimes in C applications, services and libraries. |
| audit-c-security | Audit C source code and project configuration for exploitable security defects, dependency vulnerabilities, unsafe input handling, access-control failures and resource exhaustion. Use for security reviews, vulnerability triage, secure-code checks and requested security repairs; validate findings with evidence and state coverage limits. |
| audit-c-undefined-behavior | Audit C Undefined Behavior. Use for find overflow, aliasing and lifetime violations in C applications, services and libraries. |
| benchmark-c | Benchmark C. Use for build repeatable timing and allocation measurements in C applications, services and libraries. |
| develop-c-applications | Coordinate complete C application development: CLI tools, services, desktop apps and workers. Use for project architecture, module and ownership design, error contracts, platform adapters, native dependencies, lifecycle, testing and packaging when C is the main language. |
| develop-c-build-system | Develop C Build Systems. Use for maintain portable cmake, meson and make builds in C applications, services and libraries. |
| develop-c-cli | Develop C command-line applications with explicit argument/configuration parsing, byte/text handling, exit codes, stdout/stderr contracts, terminal behavior and portable deployment. Use for new C tools or improving CLI adapters around an existing C core. |
| develop-c-desktop-apps | Develop desktop applications mainly in C with GTK or an existing native C UI stack. Use for main-thread UI ownership, GObject resources, model/view separation, background I/O, callback cancellation, packaging and accessibility. |
| develop-c-dsp | Develop C DSP. Use for build bounded streaming audio and signal kernels in C applications, services and libraries. |
| develop-c-event-loops | Develop C event-driven applications using existing libuv, libevent, GLib or platform polling. Use for handle ownership, callback lifetimes, timers, worker offload, cancellation, backpressure, graceful stop and ZeroMQ event-loop integration. |
| develop-c-network-services | Develop network services primarily in C. Use for binary or HTTP transport selection, incremental parsing, connection state, native TLS/client libraries, admission limits, deadlines, worker pools, overload handling, ZeroMQ services and operational recovery. |
| develop-c-storage | Develop persistence for C applications using SQLite or an existing native database client such as libpq. Use for prepared statements, connection/statement ownership, transactions, migrations, durability, busy/retry policy and application idempotency. |
| develop-zeromq | Design, implement, debug, secure and validate ZeroMQ message systems across languages. Use for socket-pattern selection, REQ/REP recovery, DEALER/ROUTER framing, PUB/SUB readiness, PUSH/PULL workers, HWM/backpressure, CURVE/ZAP, interoperability, cancellation and shutdown. |
| develop-zeromq-c | Build, review, debug and validate ZeroMQ integrations in C using libzmq C API; optional CZMQ. Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in C applications. |
| develop-zeromq-cpp | Build, review, debug and validate ZeroMQ integrations in C++ using cppzmq over libzmq. Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in C++ applications. |
| develop-zeromq-go | Build, review, debug and validate ZeroMQ integrations in Go using github.com/pebbe/zmq4. Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in Go applications. |
| develop-zeromq-java | Build, review, debug and validate ZeroMQ integrations in Java using JeroMQ or jzmq. Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in Java applications. |
| develop-zeromq-kotlin | Build, review, debug and validate ZeroMQ integrations in Kotlin using JeroMQ on JVM; C interop on Native. Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in Kotlin applications. |
| develop-zeromq-lean4 | Build, review, debug and validate ZeroMQ integrations in Lean 4 using versioned C FFI adapter or sidecar. Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in Lean 4 applications. |
| develop-zeromq-php | Build, debug and validate ZeroMQ integrations in PHP with ext-zmq and C/libzmq workers. Use for binary or multipart messaging, CLI/FPM lifecycle, persistent contexts, deadlines, extension ABI/deployment, native-service interoperability and restart/cancellation handling. |
| develop-zeromq-python | Build, review, debug and validate ZeroMQ integrations in Python using PyZMQ. Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in Python applications. |
| develop-zeromq-rust | Build, review, debug and validate ZeroMQ integrations in Rust using zmq (libzmq binding). Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in Rust applications. |
| develop-zeromq-scala | Build, review, debug and validate ZeroMQ integrations in Scala using JeroMQ through Java interop. Use for binary or multipart messaging, owner-thread lifecycle, deadlines/cancellation, backpressure, cross-language interoperability, native dependencies and reliable recovery in Scala applications. |
| maintain-c-ci-release | Maintain C CI and Releases. Use for create selective builds, sanitizer jobs and releases in C applications, services and libraries. |
| optimize-c-concurrency | Optimize C Concurrency. Use for tune locks, queues and cache contention from evidence in C applications, services and libraries. |
| optimize-c-ffi-boundary | Optimize C FFI Boundaries. Use for reduce foreign-call overhead and buffer copying in C applications, services and libraries. |
| optimize-c-performance | Optimize C Performance. Use for measure and improve cpu, memory and data locality in C applications, services and libraries. |
| optimize-c-simd | Optimize C SIMD. Use for vectorize kernels with safe tails and cpu dispatch in C applications, services and libraries. |
| optimize-c-stdlib | Optimize C Standard Library. Use for improve buffers, strings and i/o with correct contracts in C applications, services and libraries. |
| package-c-applications | Build and package standalone C applications for their supported platforms. Use for executable installation, native library discovery, cross toolchains, runtime dependencies, symbol/debug artifacts, packaging metadata and clean-machine smoke tests. |
| refactor-c-functional | Refactor C Functionally. Use for separate pure computations from explicit state and i/o in C applications, services and libraries. |
| renovate-c | Renovate C. Use for modernize c while preserving compiler portability in C applications, services and libraries. |
| review-c-api-abi | Review C API and ABI. Use for check source and binary compatibility of c libraries in C applications, services and libraries. |
| review-c-idioms | Review C Idioms. Use for review pointers, errors, macros and resource cleanup in C applications, services and libraries. |
| test-c-correctness | Test C Correctness. Use for test boundaries, properties and fuzzed inputs in C applications, services and libraries. |
| validate-c-concurrency | Validate C Concurrency. Use for find races, deadlocks and invalid atomic ordering in C applications, services and libraries. |
| verify-c-formal | Verify C Formally. Use for specify and verify c properties with explicit bounds in C applications, services and libraries. |
| write-c-docs | Write C Documentation. Use for document ownership, errors and executable api examples in C applications, services and libraries. |
