# Java integration

## Runtime and binding decisions

Prefer JeroMQ for a JVM-native implementation; consider jzmq only when native libzmq requirements justify JNI packaging. Pin the Maven coordinate org.zeromq:jeromq and verify the selected release/JDK baseline. Check TCP, IPC, CURVE and option support independently; the checked JeroMQ README describes IPC limitations and warns that Thread.interrupt is unsafe. Do not extrapolate those details to every release: inspect the pinned implementation. Confine a ZMQ.Socket to a dedicated owner thread with a bounded mailbox. Use explicit finite receive/poll deadlines plus an owner stop message; do not cancel by interrupting a thread blocked in JeroMQ. Use byte[] frames through ZMsg or explicit SNDMORE operations; distinguish null receive/error outcomes from a legitimate empty byte array. Close messages/sockets/context deterministically on the owner path; do not rely on GC. Benchmark JeroMQ and libzmq separately with identical wire fixtures. Use tcp:// first for interoperability with Python, Rust and C.

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

```java
// Sketch for a pinned JeroMQ release; use try-with-resources around ZContext.
ZMQ.Socket socket = context.createSocket(SocketType.DEALER);
socket.setLinger(0);
socket.setSndHWM(128);
socket.setRcvHWM(128);
socket.setSendTimeOut(1000);
socket.setReceiveTimeOut(1000);
socket.connect(endpoint);
ZMsg message = new ZMsg();
message.add("v1"); message.add("example-1"); message.add(payload);
if (!message.send(socket)) throw new IllegalStateException("send failed");
// Receive all frames with ZMsg.recvMsg, check null, version, ID and count.
// Keep socket creation, use and close on this same owner thread.
```

## Targeted checks

Run existing Maven/Gradle checks; owner stop without Thread.interrupt, binary fixtures and TCP with native peers. Preserve existing project policies and add tests for externally
observable behavior, rather than merely mirroring implementation details.

## Primary sources

- Binding/runtime: https://github.com/zeromq/jeromq

Checked on 2026-10-14. Recheck the deployed version before relying on platform or API support.
- Pinned API example: https://javadoc.io/static/org.zeromq/jeromq/0.6.0/org/zeromq/ZMQ.Socket.html
