---
name: analyze-c-assembly
description: "Analyze C Assembly. Use for inspect compiler output, vectorization and hot code in C applications, services and libraries."
---

# Analyze C Assembly

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Identify profiled functions, exact compiler/version, architecture and build flags.
2. Produce compiler assembly and inspect final binary disassembly using compatible tools; distinguish source listings, IR and machine code.
3. Check inlining, vectorization reports, branches, spills, alias assumptions and memory accesses; validate that benchmark work survives optimization.
4. Relate observations to workload measurements, not instruction count alone. Check UB and restrict/fast-math assumptions before source changes.
5. Compile revised code and run correctness plus matched benchmarks; keep findings architecture/compiler-specific.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
