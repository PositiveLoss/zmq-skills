# Document the application operational contract

Describe build/install/run, config precedence, process output/exit, endpoints, limits, resource owners, timeouts and durability/recovery. Include supported platforms and exact executed checks. Keep proposed designs distinct from measured/implemented behavior.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

A new operator can reproduce startup, one completed operation, overload handling and safe stop using the documented artifact.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
