# Define stable application extension boundaries

Review public plugin/FFI APIs separately from internal domain modules. Specify version negotiation, allocator pairs, opaque handles, callback ownership and thread affinity. Keep wire format and settings schema versioning independent of C object layout.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

A representative prior consumer either remains source/binary compatible on a tested target or gets an explicit migration/version change.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
