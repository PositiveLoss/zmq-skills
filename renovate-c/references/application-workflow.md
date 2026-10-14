# Modernize an application without erasing its platform contract

Inventory executables, resources, install locations, native dependencies and compiler/OS baselines. Use the required standard and feature probes; do not assume adopting C23 replaces all portability adapters. Upgrade dependencies incrementally and verify installed artifacts and config/schema migrations.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

An upgraded binary reads the supported prior configuration/database and starts outside the build tree on each claimed platform.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
