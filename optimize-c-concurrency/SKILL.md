---
name: optimize-c-concurrency
description: "Optimize C Concurrency. Use for tune locks, queues and cache contention from evidence in C applications, services and libraries."
---

# Optimize C Concurrency

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Map thread lifetimes, queues, shared data and synchronization using the actual C11/POSIX/platform primitives.
2. Measure blocking, lock contention, queue delay and false sharing; distinguish CPU saturation from waiting.
3. Bound workers and queues; define backpressure, fairness, cancellation and shutdown behavior.
4. Evaluate sharding, batching and layout changes while preserving ordering and memory-model guarantees. Volatile is not a general synchronization mechanism.
5. Validate races and lifetime correctness before benchmarking; exercise overload and slow consumers as well as steady load.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
