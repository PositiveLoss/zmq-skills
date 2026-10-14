# Optimize native application interoperation

Measure batching and conversion at the actual runtime boundary. Start with explicit copying; only introduce zero-copy/pinning when both runtimes lifetime and thread rules are documented. Bound retained bytes and keep release callbacks compatible with allocator/runtime restrictions.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

A zero-copy candidate proves buffer retention/release timing, passes cancellation/restart checks and improves a measured boundary metric.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
