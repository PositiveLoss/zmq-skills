# Sources and evidence checklist
Consult relevant primary sources at task time:
- WG14 standards and drafts: https://www.open-std.org/jtc1/sc22/wg14/
- GCC manual: https://gcc.gnu.org/onlinedocs/gcc/
- Clang compiler: https://clang.llvm.org/docs/UsersManual.html
- AddressSanitizer: https://clang.llvm.org/docs/AddressSanitizer.html
- UndefinedBehaviorSanitizer: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
- ThreadSanitizer: https://clang.llvm.org/docs/ThreadSanitizer.html
- MemorySanitizer: https://clang.llvm.org/docs/MemorySanitizer.html
- libFuzzer: https://llvm.org/docs/LibFuzzer.html
- CBMC: https://www.cprover.org/cbmc/ ; https://www.cprover.org/cprover-manual/
- Frama-C/ACSL: https://www.frama-c.com/ ; https://www.frama-c.com/html/acsl.html
- CMake: https://cmake.org/cmake/help/latest/
- Meson: https://mesonbuild.com/Manual.html
- POSIX: https://pubs.opengroup.org/onlinepubs/9799919799/

## Evidence record
Record baseline revision; API/ABI contracts; compiler, flags, standard and target; workload; source/version supporting version-sensitive decisions; hypotheses; code locations; executed commands and results; remaining limits. Retain raw benchmark samples and formal-tool output when relevant.
Use separate sanitizer configurations when tools cannot be combined. ASan/UBSan can be combined on supported toolchains; TSan generally needs its own build. Tool support and instrumentation coverage vary. Passing instrumented runs does not prove absence of all memory/UB/race defects.
