---
name: review-c-idioms
description: "Review C Idioms. Use for review pointers, errors, macros and resource cleanup in C applications, services and libraries."
---

# Review C Idioms

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Inspect naming, header boundaries, const qualification, explicit lengths and ownership. Separate portable ISO C from POSIX and platform extensions.
2. Check error propagation, allocation failures, cleanup labels, early-return leaks and partial initialization. Preserve errno/error contracts where applicable.
3. Audit macros for repeated evaluation, precedence and statement safety; use functions where possible. Inspect variadic format/type mismatches and signedness conversions.
4. Check array decay, sizeof mistakes, sentinel assumptions, null/empty semantics and aliasing. Classify correctness defects separately from style preferences.
5. Apply minimal authorized fixes; compile with project warnings and run targeted tests. Avoid mechanical rewrites that change ABI or evaluation order.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
