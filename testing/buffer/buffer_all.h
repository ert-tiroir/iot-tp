#pragma once
#include "buffer/buffer_001.h"
#include "buffer/buffer_002.h"
#include "buffer/buffer_003.h"

USE_NAMESPACE(nordli::iottp::testing)

struct test_case_t* buffer_tests[3] = { &buffer_001, &buffer_002, &buffer_003 };

struct test_section_t buffer_section = {
    "Buffer Tests",
    buffer_tests,
    3
};
