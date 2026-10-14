# Audit parser and platform representations

Inspect unaligned wire loads, signed shifts/overflow, size_t conversion, pointer arithmetic, format strings and struct-overlay parsing. Validate clocks/counts and byte-order conversions. Keep platform-defined behavior distinct from ISO C UB.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

Truncated/misaligned frames, boundary integer fields and optimized builds preserve the codec/error contract under supported instrumentation.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
