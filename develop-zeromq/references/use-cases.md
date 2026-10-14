# Application choices

Treat these as proposed designs, not claims that these projects already use ZeroMQ.

| Application | Candidate topology | Contract to implement |
| --- | --- | --- |
| Ukrainian telephony ASR | PUSH/PULL audio preprocessing workers plus separate results | Stream ID, sequence, sample rate, channels, sample format, bounded audio buffering and gap policy |
| GPU inference service | DEALER/ROUTER dispatcher to model workers | Request ID, admission budget, deadline, model version, cancellation and deduplication |
| Large-scale crawler | PUSH/PULL local worker distribution | Persist URL leases/results externally, cap concurrency and recover abandoned leases |
| IMU/drone telemetry | PUB/SUB live measurements plus snapshot/control channel | Sensor units, sequence, timestamp clock, latest-state policy and reconnect resync |
| Local C/C++ DSP with Python | inproc only within a shared native context, otherwise TCP/verified IPC | Binary sample format, buffer ownership, process boundary, acknowledgement of completed work |
| JVM service with Python/Rust worker | DEALER/ROUTER over TCP | Shared framing and codec fixtures; verify JeroMQ/native libzmq feature parity |
| Lean verified application | C adapter or sidecar | Prove codec/state properties; test the foreign implementation separately |

Keep durable work queues and audit logs in a system with explicit persistence
when the requirements demand them. Choose ZeroMQ for controlled message flows
only after checking the deployment, service discovery and recovery requirements.
