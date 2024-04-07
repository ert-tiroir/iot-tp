#pragma once

#include "routing/route_001.h"
#include "routing/route_002.h"
#include "routing/route_003.h"

USE_NAMESPACE(nordli::iottp::testing)

struct test_case_t* route_tests[3] = { &route_001, &route_002, &route_003 };

struct test_section_t route_section = {
    "Routing Tests",
    route_tests,
    3
};
