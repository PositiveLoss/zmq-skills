# Validate application artifacts

Build core tests and full application targets separately; include install/run from an empty staging prefix. Select realistic compiler/OS/library baselines and separate sanitizer jobs. Track resources, config/database migrations and runtime dependency discovery; keep release publishing within authorization.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

The staged artifact starts with supported config/data and resolves its runtime dependencies outside the source tree.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
