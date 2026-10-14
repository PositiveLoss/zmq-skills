---
name: maintain-c-ci-release
description: "Maintain C CI and Releases. Use for create selective builds, sanitizer jobs and releases in C applications, services and libraries."
---

# Maintain C CI and Releases

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Inspect supported standards, compilers, platforms, native dependencies and existing build conventions.
2. Filter source/header/build-system/dependency/generator/fixture/workflow changes; ensure skipped workflows cannot leave required checks permanently pending.
3. Build warning-clean release/debug configurations as justified; run tests and separate supported ASan/UBSan, TSan and other sanitizer jobs.
4. Validate install/export/pkg-config or package metadata where applicable. Keep benchmark jobs manual/scheduled or appropriately filtered.
5. Pin external actions/tools per project policy and use least privilege. Validate tag/version consistency; publish only within user authorization.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
