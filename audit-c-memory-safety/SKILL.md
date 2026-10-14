---
name: audit-c-memory-safety
description: "Audit C Memory Safety. Use for audit bounds, initialization and allocation lifetimes in C applications, services and libraries."
---

# Audit C Memory Safety

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Inventory allocations, buffers and ownership transitions; establish size/capacity/lifetime contracts.
2. Check out-of-bounds access, one-past dereferences, integer overflow in allocation sizes, use-after-free, double-free and partial-initialization cleanup.
3. Inspect realloc, interior pointers, callbacks, shared ownership and buffer retention across FFI/concurrency boundaries.
4. Run AddressSanitizer/LeakSanitizer where supported; use MemorySanitizer only with an appropriately instrumented dependency environment. Instrumentation is incomplete evidence.
5. Repair concrete defects, exercise failure paths and document any remaining assumptions. Prefer explicit ownership over blanket null checks.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
