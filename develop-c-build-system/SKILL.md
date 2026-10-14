---
name: develop-c-build-system
description: "Develop C Build Systems. Use for maintain portable cmake, meson and make builds in C applications, services and libraries."
---

# Develop C Build Systems

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Inspect existing CMake/Meson/Make layout, dependency policy, targets and minimum tool versions; avoid unrequested migrations.
2. Express standard/warnings/includes/dependencies at target scope. Separate host tools from target binaries and generated-source dependencies.
3. Use toolchain/cross files and feature checks appropriately; do not run target executables during cross compilation without a supported runner.
4. Validate static/shared variants, PIC needs, symbol exports, install layout, package discovery and downstream consumption.
5. Test clean out-of-tree builds and configuration variants. Verify tool-specific APIs against current official documentation.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
