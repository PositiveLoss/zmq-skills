#include "app.h"
#include <string.h>

enum app_status app_encode(uint64_t id, const uint8_t *payload, size_t size,
                           uint8_t *out, size_t capacity, size_t *written) {
    size_t i;
    uint32_t length;
    if (!out || !written || (!payload && size != 0)) return APP_INVALID;
    if (size > APP_MAX_PAYLOAD) return APP_TOO_LARGE;
    if (capacity < APP_HEADER_SIZE + size) return APP_NO_SPACE;
    out[0] = 'C'; out[1] = 'A'; out[2] = 'P'; out[3] = 1;
    for (i = 0; i < 8; ++i) out[4 + i] = (uint8_t)(id >> (56 - 8 * i));
    length = (uint32_t)size;
    for (i = 0; i < 4; ++i) out[12 + i] = (uint8_t)(length >> (24 - 8 * i));
    if (size) memcpy(out + APP_HEADER_SIZE, payload, size);
    *written = APP_HEADER_SIZE + size;
    return APP_OK;
}

enum app_status app_decode(const uint8_t *frame, size_t size, struct app_view *out) {
    struct app_view view;
    uint32_t length = 0;
    uint64_t id = 0;
    size_t i;
    if (!frame || !out || size < APP_HEADER_SIZE) return APP_INVALID;
    if (frame[0] != 'C' || frame[1] != 'A' || frame[2] != 'P' || frame[3] != 1) return APP_INVALID;
    for (i = 0; i < 8; ++i) id = (id << 8) | frame[4 + i];
    for (i = 0; i < 4; ++i) length = (length << 8) | frame[12 + i];
    if (length > APP_MAX_PAYLOAD) return APP_TOO_LARGE;
    if (size - APP_HEADER_SIZE != length) return APP_INVALID;
    view.request_id = id;
    view.payload = frame + APP_HEADER_SIZE;
    view.size = length;
    *out = view;
    return APP_OK;
}
