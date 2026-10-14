---
name: verify-c-formal
description: "Verify C Formally. Use for specify and verify c properties with explicit bounds in C applications, services and libraries."
---

# Verify C Formally

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Choose concrete properties and supported semantics before selecting CBMC or Frama-C. Record tool/version, target widths, memory/environment model and entry points.
2. Create harnesses/contracts with explicit valid domains and nondeterministic inputs. Check assumptions are satisfiable and do not hide the bug or property.
3. For CBMC specify pointer/bounds/overflow properties and loop/recursion handling. Use unwinding assertions and inspect whether bounds are sufficient; bounded success alone is not unbounded proof.
4. For Frama-C specify ACSL pre/postconditions, assigns clauses and loop invariants/variants. Separate proved goals, assumptions, unknown goals and runtime annotation checking.
5. Inspect counterexamples and prove correspondence to real code. Report exactly verified properties and residual model/solver/tool limitations; never label timeout a proof.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
