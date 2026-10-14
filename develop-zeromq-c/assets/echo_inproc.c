/* Minimal same-process C/Python interoperability fixture, not a service API.
 * Build shared library with the platform's normal libzmq development package:
 * cc -std=c11 -fPIC -shared echo_inproc.c -lzmq -o echo_inproc.so
 * Call from the same owner thread; caller owns context and returned socket.
 */
#include <zmq.h>

void *fixture_open_rep(void *context, const char *endpoint) {
    void *socket = zmq_socket(context, ZMQ_REP);
    const int linger = 0, timeout = 1000;
    if (!socket) return NULL;
    if (zmq_setsockopt(socket, ZMQ_LINGER, &linger, sizeof linger) ||
        zmq_setsockopt(socket, ZMQ_RCVTIMEO, &timeout, sizeof timeout) ||
        zmq_setsockopt(socket, ZMQ_SNDTIMEO, &timeout, sizeof timeout) ||
        zmq_bind(socket, endpoint)) {
        zmq_close(socket);
        return NULL;
    }
    return socket;
}

int fixture_echo_once(void *socket) {
    zmq_msg_t message;
    int status = -1;
    if (zmq_msg_init(&message)) return -1;
    if (zmq_msg_recv(&message, socket, 0) >= 0 &&
        !zmq_msg_more(&message) && zmq_msg_size(&message) <= 65536 &&
        zmq_msg_send(&message, socket, 0) >= 0) status = 0;
    /* Single-part fixture only: close/reset the socket after any failure. */
    if (zmq_msg_close(&message)) status = -1;
    return status;
}
