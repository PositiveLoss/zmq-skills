# Keep vectorized application input contracts

Vectorize a profiled codec/DSP/scan path with explicit alignment, tail, alias and ISA rules. Dispatch only on supported CPUs; preserve scalar fallback and byte-order/numeric semantics. Include tiny, unaligned and adversarial-length inputs.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

The vector path matches the independent scalar result at every boundary/tail tested and improves the representative application workload.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
