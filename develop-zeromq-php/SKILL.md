---
name: develop-zeromq-php
description: Build, debug and validate ZeroMQ integrations in PHP with ext-zmq and C/libzmq workers. Use for binary or multipart messaging, CLI/FPM lifecycle, persistent contexts, deadlines, extension ABI/deployment, native-service interoperability and restart/cancellation handling.
---

# Develop ZeroMQ in PHP

1. Inspect PHP version, SAPI, NTS/ZTS build, architecture, dependency management and whether ext-zmq is actually loaded. Separate native extension installation from Composer package resolution.
2. Read [core.md](references/core.md) for message semantics and [integration.md](references/integration.md) for extension/API/lifecycle decisions. Verify supported APIs/options against the pinned build rather than assuming current PHP compatibility.
3. Define a shared framing contract with the C worker. Use PHP byte strings, unique correlation IDs, explicit limits and a deadline covering send and receive.
4. Start with the bounded CLI client in [request.php](assets/request.php). Use nonpersistent resources for the fixture; design persistent FPM or long-lived worker reuse separately.
5. Read [verification.md](references/verification.md); verify PHP-to-C byte fixtures, false/EAGAIN paths, unavailable peer, late reply, restart, overload, SAPI lifecycle and native library resolution.
6. Deliver code, PHP/ext-zmq/libzmq versions, deployment commands, observed checks and unavailable-runtime gaps. Do not claim PHP compatibility from a C-only smoke test.
