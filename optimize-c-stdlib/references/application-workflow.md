# Bound streaming application I/O

Profile conversion, allocation, buffering and file/network adapters with representative input sizes. Preserve binary lengths, EOF/partial-write distinctions, encoding policy and limits. Batch only inside a documented memory/latency budget; measure before replacing libc routines.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

Empty, embedded-NUL, truncated and large inputs preserve output/error semantics with bounded RSS and no silent truncation.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
