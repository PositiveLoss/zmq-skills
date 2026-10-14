# Integrate DSP into a bounded C application

Specify sample rate, channels, numeric format, frame size, latency and state-reset behavior. Isolate stateful DSP from transport/UI and move work to bounded owners. Define drops/gaps, overlap and buffer lifetimes; avoid allocation/blocking in paths designated real-time.

## Execution contract

Inspect the composition root and follow one operation across actual adapters.
State input/output, ownership, errors, platform assumptions and the limits relevant
to this skill. Preserve working behavior while expanding app coverage; do not
rewrite unrelated modules. Apply only tests appropriate to the task's changed
contract and distinguish static findings from native execution.

## Application acceptance case

8 kHz telephony frames, discontinuities, reset and stream teardown preserve documented numerical behavior and measured latency; no hard real-time guarantee is inferred from an average.

Retain concrete source/log/test evidence and unresolved limitations. Route broader
implementation to develop-c-applications, develop-c-cli, develop-c-event-loops,
develop-c-network-services, develop-c-storage, develop-c-desktop-apps or
package-c-applications when those optional skills are installed. No sibling skill
is required to carry out this workflow.
