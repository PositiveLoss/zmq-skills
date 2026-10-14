# Kotlin integration

## Runtime and binding decisions

Use JeroMQ from Kotlin/JVM and pin its Maven dependency with Gradle. State the target: JVM/Android, Kotlin/Native or multiplatform. Do not imply a JVM dependency works on all targets; for Native create a versioned libzmq cinterop adapter or use a sidecar. Use a dedicated single-thread executor or single-thread coroutine dispatcher whose owner creates and closes the socket. Dispatchers.IO alone does not guarantee owner-thread affinity across suspension. Bridge callers with a bounded Channel and an owner receive/poll loop, not with concurrent socket calls. Avoid runInterruptible for JeroMQ because the checked implementation warns about Thread.interrupt. Cancellation should set an owner stop signal and finite polling should observe it; a cancelled coroutine cannot retract a delivered command. Do not run I/O on the Android main thread. Start/stop according to the service lifecycle and test background restrictions separately. Use ByteArray frames and explicit UTF-8 only for declared text fields. Verify native/JVM transport and security compatibility on actual targets.

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

```kotlin
// Design skeleton: use an application-owned single-thread executor dispatcher.
withContext(ownerDispatcher) {
    ZContext().use { context ->
        val socket = context.createSocket(SocketType.DEALER)
        try {
            socket.setLinger(0)
            socket.setSndHWM(128)
            socket.setRcvHWM(128)
            socket.setSendTimeOut(1000)
            socket.setReceiveTimeOut(1000)
            socket.connect(endpoint)
            val message = ZMsg()
            message.add("v1"); message.add("example-1"); message.add(payload)
            check(message.send(socket))
            // Receive a complete ZMsg; validate null, frame count, version and ID.
        } finally { socket.close() }
    }
}
// Adapt to a persistent owner loop; close the dispatcher after joining it.
```

## Targeted checks

Run Gradle, existing detekt/format checks; cancellation, dispatcher affinity and Android lifecycle. Preserve existing project policies and add tests for externally
observable behavior, rather than merely mirroring implementation details.

## Primary sources

- Binding/runtime: https://github.com/zeromq/jeromq

Checked on 2026-10-14. Recheck the deployed version before relying on platform or API support.
- Pinned API example: https://javadoc.io/static/org.zeromq/jeromq/0.6.0/org/zeromq/ZMQ.Socket.html
