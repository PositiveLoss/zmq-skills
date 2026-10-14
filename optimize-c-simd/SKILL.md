---
name: optimize-c-simd
description: "Optimize C SIMD. Use for vectorize kernels with safe tails and cpu dispatch in C applications, services and libraries."
---

# Optimize C SIMD

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Establish scalar reference, defined behavior, accuracy budget, target ISA and CPU dispatch requirements.
2. Inspect auto-vectorization reports first; identify alignment, aliasing, strides and reduction dependencies.
3. Implement intrinsics only where measured benefit justifies maintenance. Handle tails, unaligned addresses and tiny/zero lengths without out-of-bounds vector loads.
4. Detect CPU/OS support before dispatching ISA-specific kernels. Preserve a portable fallback; do not compile an entire distributable binary for an unsupported ISA.
5. Compare randomized/adversarial inputs, NaN/Inf where relevant and rounding/reduction differences. Benchmark size distributions and report accuracy-throughput tradeoffs.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
