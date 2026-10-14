---
name: write-c-docs
description: "Write C Documentation. Use for document ownership, errors and executable api examples in C applications, services and libraries."
---

# Write C Documentation

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Read public headers, implementation and build configuration; align documentation with actual API and supported targets.
2. Document parameter lengths/units, ownership, overlap, nullability, error behavior and thread safety. Distinguish ISO C and platform-specific interfaces.
3. Compile and execute examples under supported configurations; verify link flags, dependencies and installation commands.
4. Use the repository documentation format or Doxygen conventions when adopted; do not invent performance or compatibility claims.
5. Report tested snippets and unavailable platform checks; keep user guidance focused on meaningful usage decisions.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
