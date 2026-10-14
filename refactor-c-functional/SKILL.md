---
name: refactor-c-functional
description: "Refactor C Functionally. Use for separate pure computations from explicit state and i/o in C applications, services and libraries."
---

# Refactor C Functionally

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Map mutation, aliasing, ownership, error and concurrency contracts before refactoring.
2. Extract deterministic computations with explicit context/input/output parameters. Keep buffers caller-owned when useful and document overlap rules.
3. Separate allocation, I/O and global state from core algorithms without introducing unnecessary heap objects or callbacks.
4. Preserve evaluation order, integer/float behavior and ABI. Avoid functional abstractions that hide cleanup or length bounds.
5. Run independent regression checks; measure allocations and latency only if performance is a stated benefit.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
