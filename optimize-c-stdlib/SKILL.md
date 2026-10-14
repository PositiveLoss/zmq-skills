---
name: optimize-c-stdlib
description: "Optimize C Standard Library. Use for improve buffers, strings and i/o with correct contracts in C applications, services and libraries."
---

# Optimize C Standard Library

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Profile hot standard-library calls and inspect actual input distributions before replacing them.
2. Check memcpy overlap versus memmove, string termination/capacity, snprintf truncation, fread/fwrite partial results and ferror/EOF handling.
3. Validate allocation-size arithmetic, realloc failure behavior and zero-size rules for the supported standard. Avoid losing the original allocation on realloc failure.
4. Assess buffering, batching, conversion and sorting costs; avoid overflow in comparator subtraction and respect comparator consistency.
5. Benchmark realistic workloads with identical semantics and report portability and memory tradeoffs.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
