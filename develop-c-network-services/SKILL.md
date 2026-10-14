---
name: develop-c-network-services
description: "Develop network services primarily in C. Use for binary or HTTP transport selection, incremental parsing, connection state, native TLS/client libraries, admission limits, deadlines, worker pools, overload handling, ZeroMQ services and operational recovery."
---

# C Network Services

1. Inspect endpoints, protocol, threat model, peers, payload distribution and deployment. Read [application-contract.md](references/application-contract.md).
2. Read [service-contract.md](references/service-contract.md); specify wire format, parser bounds, lifecycle, authentication and overload policy.
3. Implement a minimal complete service path with a nonblocking owner, explicit partial I/O and typed outcomes. Keep domain work outside transport callbacks when it can block.
4. Add bounded admission, timeout/cancellation, graceful stop and recovery. If ZeroMQ is selected, apply develop-zeromq-c and preserve its routing/framing contract.
5. Verify fragmented/coalesced input, disconnects, oversize/malformed requests, slow clients, restarts and actual completion metrics. Deliver build/run and deployment assumptions.
