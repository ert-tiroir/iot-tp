#pragma once 

#include "case.h"

#include "iot-tp/buffer/buffer.h"

USE_NAMESPACE(nordli::iottp::testing)

enum test_result_t test_buffer_001 (const char** message) {
    const int PAGE   = 1024;
    const int AMOUNT = 16;

    unsigned char buf [PAGE * AMOUNT];
    struct iot_buffer_t buffer = create_iot_buffer(PAGE, AMOUNT, buf);

    if (buffer.left != buffer.right
     || buffer.left != 0) {
        *message = "Expected both left and right pointers to be 0 when buffer is created";
        return WRONG_BEHAVIOR;
    }

    if (buffer.max_size != PAGE * AMOUNT
     || buffer.max_mask != PAGE * AMOUNT - 1
     || buffer.pag_size != PAGE) {
        *message = "Expected specific values for max size, page size and max mask";
        return WRONG_BEHAVIOR;
    }

    if (buffer.target != buf) {
        *message = "Expected the target of iot_buffer_t to be the input array";
        return WRONG_BEHAVIOR;
    }

    return OK;
}

struct test_case_t buffer_001 = {
    test_buffer_001,
    "BUFFER_001"
};
