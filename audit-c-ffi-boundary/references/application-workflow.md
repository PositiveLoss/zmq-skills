# Audit application adapters across runtimes

Trace PHP/Python/UI/native adapters for lifetime, integer width, byte lengths, callbacks and error mapping. Identify worker-fork and runtime shutdown boundaries. Keep handles in owners and prevent a foreign finalizer from freeing a still-live native callback context.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

A foreign request with embedded NUL, cancellation and runtime teardown cannot corrupt native ownership or silently truncate data.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
