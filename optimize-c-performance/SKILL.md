---
name: optimize-c-performance
description: "Optimize C Performance. Use for measure and improve cpu, memory and data locality in C applications, services and libraries."
---

# Optimize C Performance

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Establish optimized production-like baseline, workload, correctness oracle and performance budget.
2. Use available CPU/allocation/cache profiles to identify hotspots. Prioritize algorithmic work, data layout, locality and bounded allocation reuse.
3. Preserve C defined behavior; use restrict only when the API guarantees its aliasing contract. Do not introduce UB to encourage optimization.
4. Evaluate compiler options, LTO/PGO and batching under actual platform constraints. Do not enable fast-math without explicit acceptance of changed floating-point semantics.
5. Compare repeated runs with fixed hardware/compiler/options; report accuracy, memory, tails and variance. Keep sanitizer builds separate from timing builds.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
