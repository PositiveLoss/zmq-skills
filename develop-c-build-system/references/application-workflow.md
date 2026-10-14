# Build complete applications with portable targets

Separate domain library, CLI/service/UI adapters and tests. Set standard/required/extensions at target scope; discover native dependencies with compatible package/toolchain support. Keep generated sources, host tools, resources and install destinations explicit.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

A clean out-of-tree configure/build/test/install succeeds on the stated toolchain without relying on source-directory paths.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
