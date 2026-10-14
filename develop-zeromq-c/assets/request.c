/* One binary echo and synchronization ACK, compatible with echo_rep.c.
 * Build: cc -std=c11 request.c -lzmq -o request
 * Run: ./request tcp://127.0.0.1:PORT
 */
#include <zmq.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    void *context = NULL, *socket = NULL;
    zmq_msg_t reply;
    int initialized = 0, status = 1;
    const int linger = 1000, timeout = 2000, immediate = 1, hwm = 16;
    const unsigned char payload[] = {'A', 0, 'B', 255};
    if (argc != 2) { fprintf(stderr, "usage: request endpoint\n"); return 2; }
    context = zmq_ctx_new();
    if (!context) goto fail;
    socket = zmq_socket(context, ZMQ_REQ);
    if (!socket) goto fail;
    if (zmq_setsockopt(socket, ZMQ_LINGER, &linger, sizeof linger) ||
        zmq_setsockopt(socket, ZMQ_RCVTIMEO, &timeout, sizeof timeout) ||
        zmq_setsockopt(socket, ZMQ_SNDTIMEO, &timeout, sizeof timeout) ||
        zmq_setsockopt(socket, ZMQ_SNDHWM, &hwm, sizeof hwm) ||
        zmq_setsockopt(socket, ZMQ_RCVHWM, &hwm, sizeof hwm) ||
        zmq_setsockopt(socket, ZMQ_IMMEDIATE, &immediate, sizeof immediate)) goto fail;
    if (zmq_connect(socket, argv[1])) goto fail;
    if (zmq_send(socket, payload, sizeof payload, 0) < 0) goto fail;
    if (zmq_msg_init(&reply)) goto fail;
    initialized = 1;
    if (zmq_msg_recv(&reply, socket, 0) < 0) goto fail;
    if (zmq_msg_more(&reply) || zmq_msg_size(&reply) != sizeof payload ||
        memcmp(zmq_msg_data(&reply), payload, sizeof payload)) {
        fprintf(stderr, "invalid binary echo\n");
        goto cleanup;
    }
    if (zmq_send(socket, "ACK", 3, 0) < 0) goto fail;
    /* No reply expected to the fixture ACK. Finite linger allows its transfer;
       the test harness waits for server exit to verify this ACK was observed. */
    status = 0;
    goto cleanup;
fail:
    fprintf(stderr, "ZeroMQ: %s\n", zmq_strerror(zmq_errno()));
cleanup:
    if (initialized && zmq_msg_close(&reply)) status = 1;
    if (socket && zmq_close(socket)) status = 1;
    if (context) {
        int result;
        do { result = zmq_ctx_term(context); } while (result < 0 && zmq_errno() == EINTR);
        if (result) status = 1;
    }
    return status;
}
