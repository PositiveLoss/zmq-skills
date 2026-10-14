# Go integration

## Runtime and binding decisions

Use `github.com/pebbe/zmq4` when native libzmq behavior is required; resolve a tagged module in go.mod/go.sum and document cgo and libzmq prerequisites. Check the binding's explicit thread-safety warning and deployed implementation. Assign socket creation/use/close to one dedicated owner goroutine; never access the same socket concurrently from different goroutines. Keep the context lifecycle separate from per-socket ownership. Do not assume every cgo wrapper requires LockOSThread; inspect the binding and use OS-thread affinity only when required by its contract. Receive `[][]byte` with RecvMessageBytes and send binary frames, avoiding implicit text conversion. Bridge context.Context cancellation through a bounded owner command channel and finite polling intervals. Cancellation does not interrupt an arbitrary blocking cgo recv. Check every setter/send/receive/close result; map zmq4.AsErrno values and deadlines distinctly. A pure-Go port is a different implementation: test framing, reconnection, CURVE and HWM rather than promising native feature parity. Cross-compilation requires an appropriate native toolchain/library.

## Starting fragment

Adapt to the pinned dependency and the owner's resource scope. This fragment is
not a full service or an interoperability test. The DEALER examples expect a
ROUTER service that strips its routing ID and returns the three body frames.
Use a unique request ID in real applications; example-1 is a fixture only.
Socket timeouts bound individual operations; impose an overall application
deadline as well. Check errors from every option setter and endpoint operation
when turning abbreviated JVM/C++ fragments into an implementation.

```go
package worker

import (
    "bytes"
    "fmt"
    "time"
    zmq "github.com/pebbe/zmq4"
)

func Request(endpoint string, payload []byte) ([][]byte, error) {
    ctx, err := zmq.NewContext()
    if err != nil { return nil, err }
    defer ctx.Term()
    s, err := ctx.NewSocket(zmq.DEALER)
    if err != nil { return nil, err }
    defer s.Close()
    setters := []func() error{
        func() error { return s.SetLinger(0) },
        func() error { return s.SetSndhwm(128) },
        func() error { return s.SetRcvhwm(128) },
        func() error { return s.SetSndtimeo(time.Second) },
        func() error { return s.SetRcvtimeo(time.Second) },
        func() error { return s.SetImmediate(true) },
    }
    for _, set := range setters { if err = set(); err != nil { return nil, err } }
    if err = s.Connect(endpoint); err != nil { return nil, err }
    if _, err = s.SendMessage([]byte("v1"), []byte("example-1"), payload); err != nil { return nil, err }
    reply, err := s.RecvMessageBytes(0)
    if err != nil { return nil, err }
    if len(reply) != 3 || !bytes.Equal(reply[0], []byte("v1")) || !bytes.Equal(reply[1], []byte("example-1")) {
        return nil, fmt.Errorf("invalid reply envelope")
    }
    return reply, nil
}
```

## Targeted checks

Run gofmt, go vet, go test -race; cgo tests on each supported OS (race cannot certify C). Preserve existing project policies and add tests for externally
observable behavior, rather than merely mirroring implementation details.

## Primary sources

- Binding/runtime: https://pkg.go.dev/github.com/pebbe/zmq4
- Binding prerequisites and concurrency warning: https://github.com/pebbe/zmq4

Checked on 2026-10-14. Recheck the deployed version before relying on platform or API support.
