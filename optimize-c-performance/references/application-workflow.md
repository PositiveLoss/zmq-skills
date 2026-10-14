# Measure end-to-end application work

Trace parse, queue, I/O, compute and commit costs separately. Record completed operations, p50/p95/p99, CPU, RSS and load/rejection distribution. Optimize the measured bottleneck; compare equivalent work in release builds and preserve failure behavior.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

A sustained representative workload shows the stated metric improvement without changing payload validation, durability or overload policy.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
