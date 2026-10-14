# Benchmark complete application contracts

Use realistic payload distributions and external completion acknowledgements. Report compiler/flags/OS, clock, sample count, input mix, tail latency, rejected requests and process memory. Separate startup/queueing/commit timing and retain raw samples; do not infer production speed from sanitizer runs.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

The benchmark records equal completed work and overload policy for baseline and candidate, including large/malformed-input effects.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
