---
name: develop-c-cli
description: "Develop C command-line applications with explicit argument/configuration parsing, byte/text handling, exit codes, stdout/stderr contracts, terminal behavior and portable deployment. Use for new C tools or improving CLI adapters around an existing C core."
---

# C CLI Applications

1. Inspect the application's command grammar, stdin/stdout format, supported shells/platforms and existing CLI compatibility. Read [application-contract.md](references/application-contract.md).
2. Read [cli-contract.md](references/cli-contract.md); define options, operands, -- handling, precedence, limits and error/exit behavior before implementation.
3. Parse into an immutable validated configuration and call a separate domain core. Keep transport/filesystem policy outside parsing; reject invalid values before side effects.
4. Exercise actual subprocess behavior: help/version, bad options, empty and binary input, boundary values, interrupted/failed output and stderr isolation. Avoid only unit-testing the parser.
5. Deliver commands, output grammar, exit statuses, OS coverage and packaging instructions.
