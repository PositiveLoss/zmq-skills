#ifndef CAPP_APP_H
#define CAPP_APP_H
#include <stddef.h>
#include <stdint.h>

#define APP_HEADER_SIZE ((size_t)16)
#define APP_MAX_PAYLOAD ((size_t)65536)

enum app_status { APP_OK = 0, APP_INVALID, APP_TOO_LARGE, APP_NO_SPACE };
struct app_view {
    uint64_t request_id;
    const uint8_t *payload; /* Borrowed from input frame; caller retains frame. */
    size_t size;
};

/* Wire: 'C','A','P',1, request ID u64be, payload size u32be, payload bytes.
 * Output arguments/buffers remain unchanged on error.
 * Payload and output frame must not overlap for encode. */
enum app_status app_encode(uint64_t id, const uint8_t *payload, size_t size,
                           uint8_t *out, size_t capacity, size_t *written);
enum app_status app_decode(const uint8_t *frame, size_t size, struct app_view *out);
#endif
