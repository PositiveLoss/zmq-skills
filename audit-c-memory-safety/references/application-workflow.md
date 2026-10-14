# Audit retained application resources

Track buffers, messages, handles, GUI closures, database statements and jobs from acquire to completion/close. Include buffer growth, aggregate limits and allocation-size arithmetic. Check late callbacks and failure cleanup; define borrowed views and allocator pairing at interfaces.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

Cancel/restart/repeated start-stop scenarios release resources without double-free, stale interior pointers or unbounded retained payloads.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
