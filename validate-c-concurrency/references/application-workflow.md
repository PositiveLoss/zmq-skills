# Validate application lifecycle races

Draw happens-before edges for startup, enqueue, cancellation, completion, close and free. Check callbacks after cancellation, worker results after parent teardown and requests during partial initialization. Keep TSan separate from ASan and supplement it with deterministic interleavings.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

A job completing concurrently with application/window shutdown cannot access reclaimed state or apply a retired attempt.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
