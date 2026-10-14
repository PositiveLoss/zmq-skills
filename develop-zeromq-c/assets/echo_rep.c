/* One-request binary REP fixture. Build: cc -std=c11 echo_rep.c -lzmq -o echo_rep
 * Run without arguments to bind a loopback TCP port selected by the OS.
 * stdout contains only the selected endpoint; no production guarantees implied.
 */
#include <zmq.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    void *context = NULL, *socket = NULL;
    zmq_msg_t message;
    int initialized = 0, status = 1;
    const int linger = 0, timeout = 2000, hwm = 16;
    const long long max_size = 65536;
    char endpoint[256];
    size_t endpoint_size = sizeof endpoint;
    if (argc > 2) { fprintf(stderr, "usage: echo_rep [endpoint]\n"); return 2; }
    context = zmq_ctx_new();
    if (!context) goto fail;
    socket = zmq_socket(context, ZMQ_REP);
    if (!socket) goto fail;
    if (zmq_setsockopt(socket, ZMQ_LINGER, &linger, sizeof linger) ||
        zmq_setsockopt(socket, ZMQ_RCVTIMEO, &timeout, sizeof timeout) ||
        zmq_setsockopt(socket, ZMQ_SNDTIMEO, &timeout, sizeof timeout) ||
        zmq_setsockopt(socket, ZMQ_RCVHWM, &hwm, sizeof hwm) ||
        zmq_setsockopt(socket, ZMQ_SNDHWM, &hwm, sizeof hwm) ||
        zmq_setsockopt(socket, ZMQ_MAXMSGSIZE, &max_size, sizeof max_size)) goto fail;
    if (zmq_bind(socket, argc == 2 ? argv[1] : "tcp://127.0.0.1:*")) goto fail;
    if (zmq_getsockopt(socket, ZMQ_LAST_ENDPOINT, endpoint, &endpoint_size)) goto fail;
    if (puts(endpoint) == EOF || fflush(stdout)) goto fail;
    if (zmq_msg_init(&message)) goto fail;
    initialized = 1;
    if (zmq_msg_recv(&message, socket, 0) < 0) goto fail;
    /* This fixture accepts one application frame only and closes on mismatch. */
    if (zmq_msg_more(&message) || zmq_msg_size(&message) > 65536) {
        fprintf(stderr, "invalid single-frame contract\n");
        goto cleanup;
    }
    if (zmq_msg_send(&message, socket, 0) < 0) goto fail;
    /* Await a separate acknowledgement so linger=0 cannot discard an unobserved
       echo at process exit. This is fixture synchronization, not business ACK. */
    if (zmq_msg_recv(&message, socket, 0) < 0) goto fail;
    if (zmq_msg_more(&message) || zmq_msg_size(&message) != 3 ||
        memcmp(zmq_msg_data(&message), "ACK", 3) != 0) {
        fprintf(stderr, "invalid echo acknowledgement\n");
        goto cleanup;
    }
    status = 0;
    goto cleanup;
fail:
    fprintf(stderr, "ZeroMQ: %s\n", zmq_strerror(zmq_errno()));
cleanup:
    if (initialized && zmq_msg_close(&message)) status = 1;
    if (socket && zmq_close(socket)) status = 1;
    if (context) {
        int result;
        do { result = zmq_ctx_term(context); } while (result < 0 && zmq_errno() == EINTR);
        if (result) status = 1;
    }
    return status;
}
