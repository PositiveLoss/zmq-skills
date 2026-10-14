---
name: audit-c-security
description: Audit C source code and project configuration for exploitable security defects, dependency vulnerabilities, unsafe input handling, access-control failures and resource exhaustion. Use for security reviews, vulnerability triage, secure-code checks and requested security repairs; validate findings with evidence and state coverage limits.
---

# C Security Audit

## Workflow
1. Establish the requested revision, scope, language/runtime versions, deployment targets and available tools. Inspect project instructions and build manifests. Audit by default; change code only when requested. Read references/language-checks.md for language-specific checks and sources.
2. Identify assets, actors, entry points and trust boundaries. Cover HTTP/IPC/CLI/files/messages/native interfaces actually present. State assumptions about attacker access and deployment. Prioritize reachable paths and sensitive operations.
3. Trace attacker-controlled input from entry to sink through validation, encoding, authorization and configuration. Review secrets, access control, injection, deserialization, filesystem/network operations, cryptography, availability and dependency risks. Include build/release configuration when in scope.
4. Select tools based on the actual target and current official documentation. Inspect existing project commands before execution. Use isolated local fixtures, bounded inputs and temporary resources; avoid live external targets and production data. Review build hooks before running untrusted projects. Never upload private code to hosted scanners without authorization.
5. Verify dependency advisories using exact resolved versions, ecosystem, features, targets and publication/check dates. Prefer official advisories and primary documentation; browse current sources when available. If network/tool access is blocked, mark freshness/coverage limitations rather than inventing results. Distinguish affected versions, reachable vulnerable functionality and confirmed exploitation.
6. Validate suspected defects with minimal safe local reproductions, data-flow evidence or regression tests. Inspect scanner output manually. Record preconditions and mitigations. A scanner alert alone is not a confirmed vulnerability; a clean scan is not proof of security.
7. When fixes are requested, make minimal changes and explain intentional behavior/API changes needed for security. Add meaningful regression checks for the vulnerable property, rerun relevant tests and confirm the original attack path is blocked. Do not weaken tests or security controls to pass tools.

## Findings contract
For each finding report: identifier and concise title; exact file/symbol/line; affected revision; attacker capability and entry point; evidence and source-to-sink path; security impact; severity with rationale; confidence/status (confirmed, suspected, or hardening); safe reproduction or why reproduction is unavailable; minimal remediation; verification result. Add CWE only when justified; do not invent CVE or CVSS scores. Redact secret values and sensitive payloads.
Report dependency findings separately with advisory URL, affected/resolved version, date and reachability uncertainty. Summarize tools, versions, commands, scope examined, tests, exclusions and environment blockers. State no confirmed findings within the examined scope when appropriate; never certify the project as secure.

## Composition
Invoke installed specialist skills only when relevant, without assuming their availability. Use security impact to distinguish ordinary correctness/style defects from vulnerabilities. Preserve existing API and behavior unless the requested security repair requires an explicit, explained change. Keep audit-only and repair workflows distinct.
