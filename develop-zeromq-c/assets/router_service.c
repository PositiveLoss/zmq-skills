/* Bounded owner-loop echo fixture, not a durable or authenticated service.
 * Body from DEALER: ["v1", request_id (1..64 bytes), payload (0..65536 bytes)].
 * ROUTER prepends a routing ID. Invalid input or send failure is fail-stop.
 * Build with a real libzmq dev package; use --self-test for local inproc checks.
 */
#include <zmq.h>
#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static volatile sig_atomic_t stopping = 0;
static void on_signal(int number) { (void)number; stopping = 1; }

static void *open_socket(void *context, int kind) {
    void *socket = zmq_socket(context, kind);
    const int linger = 0, timeout = 500, hwm = 128, mandatory = 1;
    const int64_t max_size = 65536;
    if (!socket) return NULL;
    if (zmq_setsockopt(socket, ZMQ_LINGER, &linger, sizeof linger) ||
        zmq_setsockopt(socket, ZMQ_RCVTIMEO, &timeout, sizeof timeout) ||
        zmq_setsockopt(socket, ZMQ_SNDTIMEO, &timeout, sizeof timeout) ||
        zmq_setsockopt(socket, ZMQ_SNDHWM, &hwm, sizeof hwm) ||
        zmq_setsockopt(socket, ZMQ_RCVHWM, &hwm, sizeof hwm) ||
        zmq_setsockopt(socket, ZMQ_MAXMSGSIZE, &max_size, sizeof max_size) ||
        (kind == ZMQ_ROUTER && zmq_setsockopt(socket, ZMQ_ROUTER_MANDATORY, &mandatory, sizeof mandatory))) {
        fprintf(stderr, "socket configuration: %s\n", zmq_strerror(zmq_errno()));
        zmq_close(socket);
        return NULL;
    }
    return socket;
}

/* Return 0 after echo, 1 for invalid framing, -1 for transport/resource errors.
 * Caller must close/reset socket on any nonzero result. */
static int echo_one(void *socket) {
    zmq_msg_t frames[4];
    size_t initialized = 0, count = 0, i;
    int status = -1;
    for (i = 0; i < 4; ++i) {
        if (zmq_msg_init(&frames[i])) goto cleanup;
        ++initialized;
    }
    while (count < 4) {
        if (zmq_msg_recv(&frames[count], socket, 0) < 0) goto cleanup;
        ++count;
        if (zmq_msg_size(&frames[count - 1]) > 65536) { status = 1; goto cleanup; }
        if (!zmq_msg_more(&frames[count - 1])) break;
    }
    if (count != 4 || zmq_msg_more(&frames[3]) ||
        zmq_msg_size(&frames[0]) == 0 || zmq_msg_size(&frames[0]) > 255 ||
        zmq_msg_size(&frames[1]) != 2 || memcmp(zmq_msg_data(&frames[1]), "v1", 2) ||
        zmq_msg_size(&frames[2]) == 0 || zmq_msg_size(&frames[2]) > 64) {
        status = 1;
        goto cleanup;
    }
    for (i = 0; i < 4; ++i) {
        if (zmq_msg_send(&frames[i], socket, (i < 3 ? ZMQ_SNDMORE : 0) | ZMQ_DONTWAIT) < 0) goto cleanup;
    }
    status = 0;
cleanup:
    if (status < 0) fprintf(stderr, "message error: %s\n", zmq_strerror(zmq_errno()));
    for (i = 0; i < initialized; ++i) if (zmq_msg_close(&frames[i])) status = -1;
    return status;
}

static int recv_equals(void *socket, const void *data, size_t length, int more) {
    zmq_msg_t message;
    int result;
    if (zmq_msg_init(&message)) return -1;
    result = zmq_msg_recv(&message, socket, 0);
    if (result >= 0 && (zmq_msg_size(&message) != length ||
        (length && memcmp(zmq_msg_data(&message), data, length)) ||
        !!zmq_msg_more(&message) != !!more)) result = -1;
    if (zmq_msg_close(&message)) result = -1;
    return result < 0 ? -1 : 0;
}

static int self_test(void *context, void *router) {
    void *dealer = open_socket(context, ZMQ_DEALER);
    const unsigned char payload[] = {'A', 0, 'B', 255};
    int status = 1;
    if (!dealer) return 1;
    if (zmq_bind(router, "inproc://router-test") || zmq_connect(dealer, "inproc://router-test")) goto done;
    if (zmq_send(dealer, "v1", 2, ZMQ_SNDMORE) < 0 ||
        zmq_send(dealer, "id-1", 4, ZMQ_SNDMORE) < 0 ||
        zmq_send(dealer, payload, sizeof payload, 0) < 0 || echo_one(router)) goto done;
    if (recv_equals(dealer, "v1", 2, 1) || recv_equals(dealer, "id-1", 4, 1) ||
        recv_equals(dealer, payload, sizeof payload, 0)) goto done;
    if (zmq_send(dealer, "v1", 2, ZMQ_SNDMORE) < 0 ||
        zmq_send(dealer, "id-2", 4, ZMQ_SNDMORE) < 0 ||
        zmq_send(dealer, "", 0, 0) < 0 || echo_one(router)) goto done;
    if (recv_equals(dealer, "v1", 2, 1) || recv_equals(dealer, "id-2", 4, 1) ||
        recv_equals(dealer, "", 0, 0)) goto done;
    /* Complete bad-version message is rejected; then socket is closed at exit. */
    if (zmq_send(dealer, "v2", 2, ZMQ_SNDMORE) < 0 ||
        zmq_send(dealer, "bad", 3, ZMQ_SNDMORE) < 0 ||
        zmq_send(dealer, "", 0, 0) < 0 || echo_one(router) != 1) goto done;
    if (puts("ROUTER binary/empty correlation and invalid-version checks passed") < 0) goto done;
    status = 0;
done:
    if (zmq_close(dealer)) status = 1;
    return status;
}

int main(int argc, char **argv) {
    void *context = NULL, *router = NULL;
    int status = 1;
    if (argc != 2) { fputs("usage: router_service --self-test|tcp://127.0.0.1:PORT\n", stderr); return 2; }
    context = zmq_ctx_new();
    if (!context) goto done;
    router = open_socket(context, ZMQ_ROUTER);
    if (!router) goto done;
    if (strcmp(argv[1], "--self-test") == 0) { status = self_test(context, router); goto done; }
    if (strncmp(argv[1], "tcp://127.0.0.1:", 16) != 0) {
        fputs("fixture requires a loopback TCP endpoint\n", stderr);
        goto done;
    }
    if (signal(SIGINT, on_signal) == SIG_ERR || signal(SIGTERM, on_signal) == SIG_ERR) goto done;
    if (zmq_bind(router, argv[1])) {
        fprintf(stderr, "bind: %s\n", zmq_strerror(zmq_errno()));
        goto done;
    }
    status = 0;
    while (!stopping) {
        zmq_pollitem_t item = {router, 0, ZMQ_POLLIN, 0};
        const int ready = zmq_poll(&item, 1, 100);
        if (ready < 0) {
            if (zmq_errno() == EINTR) continue;
            status = 1;
            break;
        }
        if (item.revents & ZMQ_POLLIN) {
            const int result = echo_one(router);
            if (result) { fprintf(stderr, "fail-stop after message error (%d)\n", result); status = 1; break; }
        }
    }
done:
    if (router && zmq_close(router)) status = 1;
    if (context) {
        int result;
        do { result = zmq_ctx_term(context); } while (result < 0 && zmq_errno() == EINTR);
        if (result) status = 1;
    }
    return status;
}
