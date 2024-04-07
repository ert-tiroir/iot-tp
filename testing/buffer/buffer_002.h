#pragma once 

#include "case.h"

#include "iot-tp/buffer/buffer.h"

USE_NAMESPACE(nordli::iottp::testing)

enum test_result_t test_buffer_002 (const char** message) {
    const int PAGE   = 1024;
    const int AMOUNT = 4;

    unsigned char buf [PAGE * AMOUNT];
    struct iot_buffer_t buffer = create_iot_buffer(PAGE, AMOUNT, buf);

    unsigned char* buf0 = writable_page(&buffer);
    if (buf0 != buf) {
        *message = "Expected first page to be the beginning of the buffer";
        return WRONG_BEHAVIOR;
    }

    free_write(&buffer);
    if (buffer.right != PAGE || buffer.left != 0) {
        *message = "Expected right to move by pag_size and left to stay the same";
        return WRONG_BEHAVIOR;
    }

    buf0 = writable_page(&buffer);
    if (buf0 != buf + PAGE) {
        *message = "Expected the second page to be the beginning of the buffer + PAGE";
        return WRONG_BEHAVIOR;
    }

    free_write(&buffer);
    free_write(&buffer);

    buf0 = writable_page(&buffer);
    if (buf0 != 0) {
        *message = "Expected the fourth page to be zero as the first page needs to be freed for the third to be available";
        return WRONG_BEHAVIOR;
    }

    return OK;
}

struct test_case_t buffer_002 = {
    test_buffer_002,
    "BUFFER_002"
};
