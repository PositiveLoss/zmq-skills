# C checks

## Review priorities
Trace untrusted lengths, indexes, format strings and allocation sizes. Check bounds, initialization, integer conversion/overflow, use-after-free, double-free, ownership, aliasing and lifetime; command injection, filesystem races, parser complexity and secret handling. Review compiler/platform assumptions and error paths. Use audit-c-memory-safety, audit-c-undefined-behavior, audit-c-ffi-boundary and validate-c-concurrency for deeper analysis. Do not treat hardening flags as fixes for vulnerable code.

## Tool selection
Clang static analyzer and available compiler diagnostics; ASan/UBSan, MSan or TSan in separate compatible builds; libFuzzer/AFL++ with bounded harnesses.
Treat tools as candidates, not mandatory dependencies. Verify installed versions, current invocation syntax, target support and official documentation before use. A missing tool limits coverage; it does not make the audit fail automatically.

## Primary sources
- https://clang.llvm.org/docs/ClangStaticAnalyzer.html
- https://clang.llvm.org/docs/AddressSanitizer.html
- https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
- https://clang.llvm.org/docs/LibFuzzer.html
