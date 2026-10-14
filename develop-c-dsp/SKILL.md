---
name: develop-c-dsp
description: "Develop C DSP. Use for build bounded streaming audio and signal kernels in C applications, services and libraries."
---

# Develop C DSP

## Working discipline
Inspect AGENTS.md, build configuration, public headers and existing tests. Record selected C standard, compiler versions, ABI/architecture and platforms. Keep ISO C, POSIX and platform extensions distinct. Preserve API/ABI and observable behavior unless change is authorized. Verify version-sensitive standard/compiler/tool/library details through primary documentation; do not hard-code latest versions.
Read [sources and evidence checklist](references/evidence.md) before selecting tools or reporting guarantees. Run only applicable checks and label unavailable tools/platforms. Separate static findings, executed tests, sanitizer observations, mathematical proofs and measured performance. Do not claim universal safety, zero-allocation or speed improvements without evidence. Follow the authorized scope for external writes and applicable artifact storage rules.

## Workflow
1. Specify sampling rate, amplitude/units, channel layout, frame/hop sizes, state and latency budget.
2. Derive discrete filters/resampling with anti-aliasing, gain/phase and stable coefficient conventions. Separate mathematical validity from float/fixed-point implementation.
3. For fixed-point define scaling, saturation, rounding and accumulator widths; prevent signed-overflow UB and implementation-dependent shifts from silently changing outputs.
4. Keep real-time processing bounded with preallocated state when required; define startup, chunk boundaries, flush, reset and ownership.
5. Test impulse/sinusoid/sweep/DC/noise, long-run state and independent references. Measure buffering/lookahead plus compute latency and quality at intended sample rates.


## C application extension

Read [application-workflow.md](references/application-workflow.md) when applying this
skill to a complete CLI, service, worker or desktop application. Use its task-specific
checks together with the existing workflow; keep the application primarily in C
when that is the project requirement.

## Deliverable
Report findings or completed changes with source/code evidence, executed verification and material limitations. Keep detailed measurements or proof obligations in reviewable project artifacts where needed.
