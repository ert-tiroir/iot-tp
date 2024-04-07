#pragma once

#include "iot-tp-macros.h"

START_FULL_NAMESPACE(testing);

enum test_result_t {
    OK = 0,
    WRONG_BEHAVIOR = 1,
    TIME_LIMIT_EXCEEDED = 2
};

struct test_case_t {
    enum test_result_t (*test) (const char** message);
    const char* name;
};

struct test_section_t {
    const char* name;

    struct test_case_t** tests;
    unsigned int test_count;
};

END_FULL_NAMESPACE(testing);
