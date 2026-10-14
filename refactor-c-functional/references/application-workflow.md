# Separate application state from side effects

Extract pure parsing, codec validation and state transitions. Inject clocks, allocation and I/O adapters where justified; keep explicit application context and caller-owned buffers. Preserve observable ordering of effects and cancellation/commit behavior.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

The pure core reproduces domain behavior with deterministic fixtures while an independent subprocess/integration test verifies unchanged side effects.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
