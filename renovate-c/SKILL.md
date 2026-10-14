---
name: renovate-c
description: "Renovate C. Use for modernize c while preserving compiler portability in C applications, services and libraries."
---

# Renovate C

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Identify selected C standard, supported compiler versions, platforms, feature-test macros and dependency constraints.
2. Verify current WG14 material and compiler release/support documentation. Distinguish published standards from draft features and actual compiler support.
3. Map applicable language/library/tool changes to source locations and compatibility risks. Do not raise the minimum standard silently.
4. Upgrade dependencies and build flags selectively; distinguish portability fixes from compiler-specific improvements.
5. Build supported configurations and test behavior. Document remaining legacy requirements and do not infer speedups from modernization alone.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
