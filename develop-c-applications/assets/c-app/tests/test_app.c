#include "app.h"
#include <stdio.h>
#include <string.h>

#define CHECK(expr) do { if (!(expr)) { fprintf(stderr, "failed line %d: %s\n", __LINE__, #expr); return 1; } } while (0)

int main(void) {
    const uint8_t payload[] = {'A', 0, 'B', 255};
    const uint8_t golden[] = {'C','A','P',1, 1,2,3,4,5,6,7,8, 0,0,0,4, 'A',0,'B',255};
    uint8_t output[32], bad[32], empty[16];
    struct app_view view = {99, payload, sizeof payload};
    size_t size = 123, i;
    CHECK(app_encode(UINT64_C(0x0102030405060708), payload, 4, output, sizeof output, &size) == APP_OK);
    CHECK(size == sizeof golden && memcmp(output, golden, size) == 0);
    CHECK(app_decode(golden, sizeof golden, &view) == APP_OK);
    CHECK(view.request_id == UINT64_C(0x0102030405060708) && view.size == 4);
    CHECK(memcmp(view.payload, payload, 4) == 0);
    for (i = 0; i < sizeof golden; ++i) {
        view.request_id = 99;
        CHECK(app_decode(golden, i, &view) == APP_INVALID);
        CHECK(view.request_id == 99);
    }
    memcpy(bad, golden, sizeof golden);
    bad[3] = 2;
    CHECK(app_decode(bad, sizeof golden, &view) == APP_INVALID);
    bad[3] = 1; bad[0] = 0;
    CHECK(app_decode(bad, sizeof golden, &view) == APP_INVALID);
    memcpy(bad, golden, sizeof golden); bad[15] = 5;
    CHECK(app_decode(bad, sizeof golden, &view) == APP_INVALID);
    memcpy(bad, golden, sizeof golden); bad[12] = 255;
    CHECK(app_decode(bad, sizeof golden, &view) == APP_TOO_LARGE);
    CHECK(app_encode(UINT64_MAX, NULL, 0, empty, sizeof empty, &size) == APP_OK);
    CHECK(size == APP_HEADER_SIZE && app_decode(empty, sizeof empty, &view) == APP_OK);
    CHECK(view.request_id == UINT64_MAX && view.size == 0);
    memset(output, 17, sizeof output); size = 123;
    CHECK(app_encode(1, payload, 4, output, 19, &size) == APP_NO_SPACE);
    CHECK(size == 123);
    for (i = 0; i < sizeof output; ++i) CHECK(output[i] == 17);
    CHECK(app_encode(1, payload, APP_MAX_PAYLOAD + 1, output, sizeof output, &size) == APP_TOO_LARGE);
    CHECK(app_encode(1, NULL, 1, output, sizeof output, &size) == APP_INVALID);
    CHECK(app_decode(NULL, 0, &view) == APP_INVALID);
    CHECK(app_decode(golden, sizeof golden, NULL) == APP_INVALID);
    CHECK(puts("codec golden, binary, empty, bounds and failure contracts passed") >= 0);
    return 0;
}
