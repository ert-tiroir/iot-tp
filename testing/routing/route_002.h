#pragma once

#include "case.h"

#include "router/iot-tp-routing.h"

USE_NAMESPACE(nordli::iottp::routing);
USE_NAMESPACE(nordli::iottp::testing)

enum test_result_t test_route_002 (const char** message) {
    struct packet_router_t router;

    for (uint8_t i = 0; i < MAX_ADRESS_COUNT; i ++)
        router.path_map[i] = i;
    
    for (uint8_t i = 0; i < MAX_ADRESS_COUNT; i ++) {
        if (get_route(&router, i) == i) continue;
    
        *message = "The method get_route(i) does not return path_map[i]";
        return WRONG_BEHAVIOR;
    }

    return OK;
}

struct test_case_t route_002 = {
    test_route_002,
    "ROUTE_002"
};
