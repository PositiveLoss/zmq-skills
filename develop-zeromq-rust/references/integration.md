# Rust integration

## Runtime and binding decisions

Prefer the `zmq` crate for native libzmq interoperability unless a pure-Rust port has passed the required compatibility matrix. Resolve and lock the crate with Cargo; identify which libzmq gets linked or vendored and whether CURVE is built. Put a blocking socket in a dedicated owner thread with a bounded command channel when integrating Tokio/smol. Poll at finite intervals so the owner can process stop requests. Do not put a non-Sync socket behind a mutex to bypass its thread-safety contract, or use an async mutex around blocking recv. A cancelled `spawn_blocking` future does not automatically stop the native operation; define the owner's shutdown explicitly. Use `Vec<u8>`/`zmq::Message`, retain binary payloads and compare frame counts. Keep serialization outside the socket owner when CPU work would delay all peers. Use a shared reference-counted buffer only after proving the binding's lifetime rules. Treat wrappers such as async adapters as separate dependencies whose socket/options/security coverage must be checked.

## Starting fragment

Adapt to the pinned dependency and the owner's resource scope. This fragment is
not a full service or an interoperability test. The DEALER examples expect a
ROUTER service that strips its routing ID and returns the three body frames.
Use a unique request ID in real applications; example-1 is a fixture only.
Socket timeouts bound individual operations; impose an overall application
deadline as well. Check errors from every option setter and endpoint operation
when turning abbreviated JVM/C++ fragments into an implementation.

```rust
fn request(endpoint: &str, payload: &[u8]) -> Result<Vec<Vec<u8>>, Box<dyn std::error::Error>> {
    let ctx = zmq::Context::new();
    let socket = ctx.socket(zmq::DEALER)?;
    socket.set_linger(0)?;
    socket.set_sndhwm(128)?;
    socket.set_rcvhwm(128)?;
    socket.set_sndtimeo(1000)?;
    socket.set_rcvtimeo(1000)?;
    socket.set_immediate(true)?;
    socket.connect(endpoint)?;
    socket.send_multipart([b"v1".as_slice(), b"example-1".as_slice(), payload], 0)?;
    let reply = socket.recv_multipart(0)?;
    if reply.len() != 3 || reply[0] != b"v1" || reply[1] != b"example-1" {
        return Err("invalid reply envelope".into());
    }
    Ok(reply)
} // socket drops before context; intentional discard linger
```

## Targeted checks

Run cargo fmt, clippy and tests; native-owner stop, option errors, buffer lifetime. Preserve existing project policies and add tests for externally
observable behavior, rather than merely mirroring implementation details.

## Primary sources

- Binding/runtime: https://docs.rs/zmq/latest/zmq/
- Native dependency/build: https://github.com/erickt/rust-zmq

Checked on 2026-10-14. Recheck the deployed version before relying on platform or API support.
