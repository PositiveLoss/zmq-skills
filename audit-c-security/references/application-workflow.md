# Audit complete application ingress and persistence

Map untrusted CLI/config/files/wire frames, authorization, dependency parsers, logs and storage. Enforce per-frame/aggregate/queue/resource limits, parameterized queries and secret redaction. Inspect path/process invocation, TLS/CURVE verification, replay and shutdown resource exhaustion.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

Malformed/oversized/unprivileged input is rejected with bounded work and no unauthorized effect or leaked credential.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
