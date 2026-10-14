# Scala integration

## Runtime and binding decisions

Use JeroMQ through JVM interop and lock the Maven coordinate in the project's sbt/Gradle/Maven dependency policy. Model protocol values and parsing with immutable Scala ADTs, preserving Array[Byte] frame content. Use one dedicated owner thread/executor and a bounded mailbox; scheduling successive operations on a general ExecutionContext does not preserve a single socket owner. In Pekko keep the blocking socket loop off the default actor dispatcher and return immutable results to actors; an actor restarting must explicitly stop the previous owner first. In Cats Effect/ZIO use resource scopes and owner signals; do not assume an interruptible blocking wrapper is safe for JeroMQ. In Spark construct resources per worker process/partition as appropriate; do not capture driver sockets in serialized closures. Prevent speculative/retried tasks from duplicating side effects through the application contract. Use TCP to test with native peers and inspect exact JeroMQ IPC/security limitations. Bound mailboxes and outstanding requests separately from ZeroMQ HWM.

Check the selected JeroMQ API conventions instead of copying numeric libzmq
option meanings. In particular, verify `setImmediate` against a no-peer test;
the 0.6.0 Javadoc describes a boolean convention that differs from the native
ZMQ_IMMEDIATE option. Treat documentation as evidence to test, not proof of
behavior in another release.

## Starting fragment

Adapt to the pinned dependency and the owner's resource scope. This fragment is
not a full service or an interoperability test. The DEALER examples expect a
ROUTER service that strips its routing ID and returns the three body frames.
Use a unique request ID in real applications; example-1 is a fixture only.
Socket timeouts bound individual operations; impose an overall application
deadline as well. Check errors from every option setter and endpoint operation
when turning abbreviated JVM/C++ fragments into an implementation.

```scala
// Owner-thread fragment, not an arbitrary Future/ExecutionContext task.
val context = new org.zeromq.ZContext()
try {
  val socket = context.createSocket(org.zeromq.SocketType.DEALER)
  try {
    socket.setLinger(0)
    socket.setSndHWM(128)
    socket.setRcvHWM(128)
    socket.setSendTimeOut(1000)
    socket.setReceiveTimeOut(1000)
    socket.connect(endpoint)
    val msg = new org.zeromq.ZMsg()
    msg.add("v1"); msg.add("example-1"); msg.add(payload)
    require(msg.send(socket), "send failed")
    // Receive and validate all reply frames; map errors into an application ADT.
  } finally socket.close()
} finally context.close()
```

## Targeted checks

Run sbt test and existing Scala lint; actor restart/resource ownership, Spark retries and binary interoperability. Preserve existing project policies and add tests for externally
observable behavior, rather than merely mirroring implementation details.

## Primary sources

- Binding/runtime: https://github.com/zeromq/jeromq

Checked on 2026-10-14. Recheck the deployed version before relying on platform or API support.
- Pinned API example: https://javadoc.io/static/org.zeromq/jeromq/0.6.0/org/zeromq/ZMQ.Socket.html
