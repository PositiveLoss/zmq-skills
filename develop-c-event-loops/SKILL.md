---
name: develop-c-event-loops
description: "Develop C event-driven applications using existing libuv, libevent, GLib or platform polling. Use for handle ownership, callback lifetimes, timers, worker offload, cancellation, backpressure, graceful stop and ZeroMQ event-loop integration."
---

# C Event Loops

1. Inspect the existing loop framework and platform targets. Read [application-contract.md](references/application-contract.md).
2. Read [loop-contract.md](references/loop-contract.md). Assign each handle/request/timer an owner and a lifecycle; map all completion and close callbacks before implementation.
3. Bound callback work and mailboxes. Offload blocking database/DSP work to bounded workers, and marshal results to the owner loop.
4. Implement a monotonic deadline policy, cancellation state and explicit shutdown that waits for safe resource reclamation.
5. Verify callback-after-cancel, partial initialization, full queues, repeated start/stop and close ordering. Report observed liveness bounds and framework-specific gaps.
