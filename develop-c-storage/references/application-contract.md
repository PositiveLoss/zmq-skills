# C application design contract

Treat C as the application implementation language, not only an FFI layer.
Inspect the actual product: CLI, daemon, desktop UI, worker, library or embedded
target. Select a supported C standard from deployment/toolchain evidence;
use C11 as the bundled starter baseline, and opt into C17/C23 only after checking
required features on target compilers. Keep ISO C, POSIX and platform APIs distinct.

Separate pure domain/codec modules from OS adapters, transport, persistence,
UI and the composition root. Put dependency ownership in explicit application
state rather than globals. Document who owns each buffer/handle and when it can
be retained, moved, borrowed and destroyed. Make partial initialization and failed
allocation recoverable; pair every successful acquire with one cleanup path.

Use a typed status enum plus explicit out parameters or a documented result
structure. Save errno/library diagnostics before cleanup overwrites them.
Define capacities, integer widths, input limits and deadline budgets. Use opaque
public handles where useful; keep serialization independent of C struct layout.
Treat timeouts, malformed input, saturation and shutdown as application states.

Choose dependencies for required behavior, preserve the project's build system,
and lock resolved versions. Do not replace a mature parser/TLS/database library
with custom protocol code just because the main application is C. Include native
development packages, runtime library resolution and transitive licenses in the
deployment contract. Keep TLS certificate/hostname verification enabled.

Run a warning-clean supported build, semantic tests, justified failure injection
and separate compatible sanitizer configurations. Report actual platform coverage;
an executable tested on Linux is not evidence of Windows/macOS compatibility.
Prefer application-level tests for cancellation, restart and persistence boundaries.

Primary tool references checked on 2026-10-14:
- https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD.html
- https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html
- https://clang.llvm.org/docs/AddressSanitizer.html
