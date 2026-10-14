# Lean 4 integration

## Runtime and binding decisions

Do not invent a maintained Lean ZeroMQ package. Inspect the repository for an existing adapter first; otherwise choose a small libzmq C bridge or a Python/Rust/C sidecar. Put network effects in IO and keep codec, envelope validation and state transitions pure. Represent outcomes as typed values covering timeout, protocol error, shutdown and transport failure. For FFI match the exact pinned Lean ABI and Lake toolchain: inspect generated C for extern signatures, borrowed versus owned arguments and IO result layout. Use an external-object handle with an explicit close operation and guarded lifecycle rather than exposing raw pointers as Nat/UInt64. Prevent finalizers from closing live sockets on the wrong thread; have them signal an owner or clean up only already-detached state. Keep callbacks into Lean out of libzmq arbitrary-thread buffer deallocators unless that thread is initialized and ownership is correct. Prefer copying buffers for the initial bridge. Use a sidecar for deployment isolation when native FFI cost/complexity is unjustified. Sidecar stdio framing needs lengths, byte limits, request IDs, stderr-only logs and exit/restart handling; test the ZeroMQ leg separately. State precisely that proofs cover modeled properties, not delivery/liveness of an unverified foreign runtime.

## Starting fragment

Adapt to the pinned dependency and the owner's resource scope. This fragment is
not a full service or an interoperability test. The DEALER examples expect a
ROUTER service that strips its routing ID and returns the three body frames.
Use a unique request ID in real applications; example-1 is a fixture only.
Socket timeouts bound individual operations; impose an overall application
deadline as well. Check errors from every option setter and endpoint operation
when turning abbreviated JVM/C++ fragments into an implementation.

```lean
-- Pure application contract; not a claim of a ready-made ZeroMQ binding.
inductive TransportOutcome where
  | reply (requestId : String) (payload : ByteArray)
  | timeout
  | stopped
  | protocolError (detail : String)
  | transportError (detail : String)

structure Envelope where
  version : UInt8
  requestId : String
  payload : ByteArray

-- Define and prove decode(encode(e)) = some e under explicit size bounds.
-- Implement IO transport separately through a tested owner-thread C adapter
-- or a versioned sidecar protocol. Inspect generated extern C signatures.
```

## Targeted checks

Run lake build, proof checking without sorry, native sanitizers and ABI/sidecar integration tests. Preserve existing project policies and add tests for externally
observable behavior, rather than merely mirroring implementation details.

## Primary sources

- Binding/runtime: https://lean-lang.org/doc/reference/latest/Run-Time-Code/Foreign-Function-Interface/

Checked on 2026-10-14. Recheck the deployed version before relying on platform or API support.
