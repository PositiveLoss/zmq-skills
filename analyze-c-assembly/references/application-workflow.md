# Connect assembly to the application bottleneck

Select a profiled parser, codec, DSP or allocation hot path. Preserve input domain/alias/alignment contracts and compiler flags. Verify the production translation unit, inlining/LTO context and target ISA; do not extrapolate a micro-kernel instruction count into end-to-end speed.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

A suspected code-generation change is confirmed in the intended build and checked with semantic tests and the relevant application metric.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
