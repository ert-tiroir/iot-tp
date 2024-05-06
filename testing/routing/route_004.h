#pragma once

#include "case.h"

#include "iot-tp/router/iot-tp-routing.h"
#include <stdio.h>

USE_NAMESPACE(nordli::iottp::routing);
USE_NAMESPACE(nordli::iottp::testing)

enum test_result_t test_route_004 (const char** message) {
    struct packet_router_t router;
    router.local_ip = 1;

    for (uint8_t a = 0; a < MAX_ADRESS_COUNT; a ++) {
        for (uint8_t b = 0; b < MAX_ADRESS_COUNT; b ++) {
            router.weight_map[a][b] = NO_PATH;
        }
    }

    router.weight_map [1][2] = 1;
    router.weight_map [1][3] = 3;
    router.weight_map [2][3] = 1;

    recompute_path_map(&router);

    int pmap[4] = { NO_ROAD, NO_ROAD, 2, 2 };
    for (int i = 0; i < MAX_ADRESS_COUNT; i ++) {
        if (router.path_map[i] != get_route(&router, i) || router.path_map[i] != pmap[i]) {
            *message = "Unexpected route computed by router";
            return WRONG_BEHAVIOR;
        }
    }

    return OK;
}

struct test_case_t route_004 = {
    test_route_004,
    "ROUTE_004"
};
