# Test applications through observable contracts

Add subprocess/install and native integration cases for CLI output/exit, fragmented input, full admission, failed allocation, uncertain commit, cancellation and restart. Use independent golden frames and differential parsers; keep fuzz resets and corpus limits explicit.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

A crash after durable commit but before response yields one recovered result and one effect when the storage contract promises deduplication.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
