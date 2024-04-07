#pragma once

#include "case.h"

#include "iot-tp/router/iot-tp-routing.h"

USE_NAMESPACE(nordli::iottp::routing);
USE_NAMESPACE(nordli::iottp::testing)

enum test_result_t test_route_003 (const char** message) {
    struct packet_router_t router;

    for (uint8_t a = 0; a < MAX_ADRESS_COUNT; a ++) {
        for (uint8_t b = 0; b < MAX_ADRESS_COUNT; b ++) {
            router.weight_map[a][b] = NO_PATH;
        }
    }

    for (uint8_t a = 0; a < MAX_ADRESS_COUNT; a ++) {
        for (uint8_t b = 0; b < MAX_ADRESS_COUNT; b ++) {
            struct route_modification_t modification = {
                .a = a,
                .b = b,

                .weight = a + b
            };

            modify_route(&router, &modification);
            for (uint8_t a0 = 0; a0 < MAX_ADRESS_COUNT; a0 ++) {
                for (uint8_t b0 = 0; b0 < MAX_ADRESS_COUNT; b0 ++) {
                    if (a0 == a && b0 == b) {
                        if (router.weight_map[a0][b0] != a + b) {
                            *message = "modify_route() should set the router's weight_map[a][b] to the weight";
                            return WRONG_BEHAVIOR;
                        }
                    } else {
                        if (router.weight_map[a0][b0] != NO_PATH) {
                            *message = "modify_route() shouldn't set any other value than weight_map[a][b]";
                            return WRONG_BEHAVIOR;
                        }
                    }
                }
            }

            router.weight_map[a][b] = NO_PATH;
        }
    }

    return OK;
}

struct test_case_t route_003 = {
    test_route_003,
    "ROUTE_003"
};
