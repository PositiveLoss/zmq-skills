---
name: audit-c-ffi-boundary
description: "Audit C FFI Boundaries. Use for audit python, rust and go bindings to c in C applications, services and libraries."
---

# Audit C FFI Boundaries

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Map binding signatures, C declarations, ABI, widths, alignment, lengths/strides, encoding and ownership.
2. Check allocation/free pairing, borrowed buffer lifetime, pinning/GC requirements of the caller language and retention by asynchronous native work.
3. Audit callbacks, thread/GIL rules, shutdown, late callbacks and error translation. Never allow a foreign exception/panic to cross an incompatible C ABI.
4. Inspect null/zero-length buffers and overlap contracts; copy when lifetime rules require it. Document whether outputs alias inputs.
5. Use available Python/Rust/Go native-boundary skills; test failures and teardown with suitable sanitizers and caller-language checks.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
