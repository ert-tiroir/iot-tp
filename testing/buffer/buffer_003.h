#pragma once 

#include "case.h"

#include "buffer/buffer.h"

USE_NAMESPACE(nordli::iottp::testing)

enum test_result_t test_buffer_003 (const char** message) {
    const int PAGE   = 1024;
    const int AMOUNT = 4;

    unsigned char buf [PAGE * AMOUNT];
    struct iot_buffer_t buffer = create_iot_buffer(PAGE, AMOUNT, buf);

    if (readable_page(&buffer) != 0) {
        *message = "Expected the first readable page to be zero as there is no data";
        return WRONG_BEHAVIOR;    
    }

    free_write(&buffer);
    free_write(&buffer);
    free_write(&buffer);

    if (readable_page(&buffer) != buf) {
        *message = "Expected the first readable page to be the beginning of the buffer";
        return WRONG_BEHAVIOR;    
    }

    free_read(&buffer);
    if (buffer.left != PAGE || buffer.right != 3 * PAGE) {
        *message = "Expected left to advance by PAGE and right to stay the same";
        return WRONG_BEHAVIOR;
    }
    free_read(&buffer);
    if (buffer.left != 2 * PAGE || buffer.right != 3 * PAGE) {
        *message = "Expected left to advance by PAGE and right to stay the same";
        return WRONG_BEHAVIOR;
    }

    free_write(&buffer);
    if (buffer.left != 2 * PAGE || buffer.right != 0) {
        *message = "Expected left to stay the same and right to loop back";
        return WRONG_BEHAVIOR;
    }
    free_read(&buffer);
    free_read(&buffer);
    if (buffer.left != buffer.right || buffer.right != 0) {
        *message = "Expected to come back at the beginning";
        return WRONG_BEHAVIOR;
    }

    return OK;
}

struct test_case_t buffer_003 = {
    test_buffer_003,
    "BUFFER_003"
};
