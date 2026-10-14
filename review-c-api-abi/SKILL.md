---
name: review-c-api-abi
description: "Review C API and ABI. Use for check source and binary compatibility of c libraries in C applications, services and libraries."
---

# Review C API and ABI

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Inventory public headers, exported symbols, calling conventions, struct layout, packing and version baseline.
2. Check ownership, allocator pairing, error semantics, callbacks and thread safety as API contracts.
3. Assess pointer width, integer types, enum representation, alignment, padding and platform ABI differences; separate source compatibility from binary compatibility.
4. Compare symbols/layout using available ABI tools and compile representative downstream callers. Prefer opaque types where suitable without silently breaking existing ABI.
5. Deliver a change matrix with affected consumers, migration/version strategy and platforms actually tested.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
