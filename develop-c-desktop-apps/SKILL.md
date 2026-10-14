---
name: develop-c-desktop-apps
description: "Develop desktop applications mainly in C with GTK or an existing native C UI stack. Use for main-thread UI ownership, GObject resources, model/view separation, background I/O, callback cancellation, packaging and accessibility."
---

# C Desktop Applications

1. Inspect actual platforms, UI framework and native-distribution expectations. Read [application-contract.md](references/application-contract.md).
2. Read [desktop-contract.md](references/desktop-contract.md); define a pure application model and owner-thread view adapters.
3. Implement user-visible flows with bounded background jobs, explicit cancellation and callback/resource ownership. Keep blocking work off the UI loop.
4. Verify close/reopen while a job completes, error states, keyboard/accessibility behavior and real target installation. Separate headless core tests from executed UI tests.
5. Deliver screenshots/flows only when requested, build/package commands, library/runtime dependencies and actual platform coverage.
