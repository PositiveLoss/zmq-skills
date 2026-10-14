---
name: benchmark-c
description: "Benchmark C. Use for build repeatable timing and allocation measurements in C applications, services and libraries."
---

# Benchmark C

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Define inputs, timed region, outputs, accuracy and representative size distributions. Record compiler, flags, CPU, OS and affinity policy.
2. Use a platform-supported monotonic clock; label POSIX clock_gettime as POSIX rather than ISO C. Avoid timer overhead dominating the workload.
3. Ensure results are consumed observably and inspect optimized code for eliminated work. Separate setup from execution unless end-to-end setup is intended.
4. Run independent repeated samples, control warmup/cache conditions and report raw samples plus uncertainty. Measure allocations and process memory with suitable instrumentation.
5. Avoid sanitizers/debug builds for production speed claims; compare identical semantics, build flags and workloads.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
