#include "app.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    uint8_t *frame;
    size_t length, written = 0, i;
    int operand = 1, status = 0;
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        return puts("Usage: capp [--] text\nEncode text bytes as a CAPP v1 frame in hex.") < 0 ? 1 : 0;
    }
    if (argc > 1 && strcmp(argv[1], "--") == 0) operand = 2;
    if (argc != operand + 1 || (operand == 1 && argv[1][0] == '-')) {
        fputs("Usage: capp [--] text\n", stderr);
        return 2;
    }
    length = strlen(argv[operand]); /* argv text only, never binary input. */
    if (length > APP_MAX_PAYLOAD) {
        fputs("Payload exceeds 65536 bytes\n", stderr);
        return 2;
    }
    frame = malloc(APP_HEADER_SIZE + length);
    if (!frame) { fputs("Allocation failed\n", stderr); return 1; }
    if (app_encode(1, (const uint8_t *)argv[operand], length, frame,
                   APP_HEADER_SIZE + length, &written) != APP_OK) {
        fputs("Encode failed\n", stderr);
        free(frame);
        return 1;
    }
    for (i = 0; i < written; ++i) {
        if (printf("%02x", (unsigned int)frame[i]) < 0) { status = 1; break; }
    }
    if (!status && putchar('\n') == EOF) status = 1;
    if (fflush(stdout) == EOF) status = 1;
    free(frame);
    return status;
}
