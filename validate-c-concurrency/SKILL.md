---
name: validate-c-concurrency
description: "Validate C Concurrency. Use for find races, deadlocks and invalid atomic ordering in C applications, services and libraries."
---

# Validate C Concurrency

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Define ownership and happens-before relations for shared objects; inspect atomics, mutexes, condition variables and lifetime/reclamation.
2. Check condition-variable predicate loops, lock ordering, thread joins, cancellation and teardown. Separate ISO C atomics from POSIX guarantees.
3. Assess memory-order choices, publication and reclamation explicitly. Do not assume an atomic pointer makes pointee access or freeing safe.
4. Run ThreadSanitizer where supported in a separate compatible build; use deterministic barriers and bounded stress tests.
5. Report unsupported instrumentation and executed-path limits. Fix minimal counterexamples and retain regression coverage.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
