---
name: test-c-correctness
description: "Test C Correctness. Use for test boundaries, properties and fuzzed inputs in C applications, services and libraries."
---

# Test C Correctness

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Derive API contracts for lengths, ownership, errors, overlap, integer ranges and float accuracy.
2. Use analytic small cases, independent differential references and justified metamorphic properties.
3. Cover empty/null, malformed, extreme sizes, truncation, allocation failures and partial I/O without constructing invalid test harnesses.
4. Build bounded fuzz harnesses with deterministic reset/cleanup. Select libFuzzer or another supported engine from official docs; preserve minimized failing inputs.
5. Run tests with appropriate warnings and separate compatible sanitizer configurations. Report executed checks without equating coverage or sanitizer silence to proof.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
