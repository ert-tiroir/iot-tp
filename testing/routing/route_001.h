#pragma once

#include "case.h"

#include "iot-tp/router/iot-tp-routing.h"

USE_NAMESPACE(nordli::iottp::routing);
USE_NAMESPACE(nordli::iottp::testing);

enum test_result_t test_route_001 (const char** message) {
    for (lan_ip_t local_ip = 0; local_ip < MAX_ADRESS_COUNT; local_ip ++) {
        struct packet_router_t router;

        // generate false data
        for (lan_ip_t a = 0; a < MAX_ADRESS_COUNT; a ++) {
            router.path_map[a] = a;

            for (lan_ip_t b = 0; b < MAX_ADRESS_COUNT; b ++)
                router.weight_map[a][b] = a + b;
        }

        initialize(&router, local_ip);

        for (lan_ip_t target = 0; target < MAX_ADRESS_COUNT; target ++) {
            if (router.path_map[target] != NO_PATH) {
                *message = "All values inside path_map after initalize should be NO_PATH";

                return WRONG_BEHAVIOR;
            }
        }

        for (lan_ip_t a = 0; a < MAX_ADRESS_COUNT; a ++) {
            for (lan_ip_t b = 0; b < MAX_ADRESS_COUNT; b ++) {
                if (router.weight_map[a][b] == NO_ROAD) continue ;

                *message = "All values inside weight_map after initialize should be NO_ROAD";
                return WRONG_BEHAVIOR;
            }
        }

        if (router.local_ip != local_ip) {
            *message = "The local ip of the packet router should be equal to the local ip inside the arguments of the initialize method.";
            return WRONG_BEHAVIOR;
        }
    }

    return OK;
}

struct test_case_t route_001 = {
    test_route_001,
    "ROUTE_001"
};
