---
name: audit-c-undefined-behavior
description: "Audit C Undefined Behavior. Use for find overflow, aliasing and lifetime violations in C applications, services and libraries."
---

# Audit C Undefined Behavior

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Identify selected standard, implementation-defined behavior and platform assumptions before categorizing defects.
2. Audit signed overflow, shifts, division edge cases, invalid pointers/alignment, unsequenced effects, strict aliasing/effective type and object lifetimes.
3. Check conversions, char signedness, variadic arguments and representation assumptions. Do not classify every unsigned wrap or implementation-defined conversion as UB.
4. Use UBSan plus static/compiler analysis and optimized tests as appropriate. Note that the default undefined group does not catch every UB category.
5. Fix the semantic cause rather than merely suppressing checks or changing optimization flags; preserve intended numeric/API behavior.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
