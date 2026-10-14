# Model application state and parser contracts

Choose pure codec/parser/state properties whose modeled behavior matches the production code. State environmental assumptions, memory bounds and loop coverage. Model resource transitions and idempotency only to the extent the actual adapter/storage behavior is included; do not prove network delivery by proving a parser.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

An independent golden frame and satisfiable malformed-input harness exercise both success and rejection; bounded solver success is reported with its exact bounds.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
