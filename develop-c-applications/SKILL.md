---
name: develop-c-applications
description: "Coordinate complete C application development: CLI tools, services, desktop apps and workers. Use for project architecture, module and ownership design, error contracts, platform adapters, native dependencies, lifecycle, testing and packaging when C is the main language."
---

# C Applications

1. Inspect the project and establish application type, supported OS/architecture, latency/memory budgets, interfaces and deployment requirements. Preserve existing project conventions.
2. Read [application-contract.md](references/application-contract.md). Write a compact module/ownership/error map, state model and dependency rationale. Keep domain logic and codec tests independent of transport/UI.
3. Use [starter.md](references/starter.md) to adapt the bundled C11 codec/CLI project in assets/c-app. Copy it to the target project only when appropriate; rename targets and replace the fixture codec with the actual product contract.
4. Route CLI work to develop-c-cli, event ownership to develop-c-event-loops, services to develop-c-network-services, persistence to develop-c-storage, desktop UI to develop-c-desktop-apps, and distribution to package-c-applications when installed. Each route is optional and independently usable.
5. Apply existing C build, security, memory, concurrency, ABI and testing skills according to the changed behavior. Verify failure paths and complete install/run behavior before reporting readiness.
6. Deliver working code, dependency/version choices, build/run commands, ownership contracts, executed tests and remaining platform gaps.
