
#include <iot-tp/router/iot-tp-routing.h>

USE_NAMESPACE(nordli::iottp::routing)

void initialize (struct packet_router_t* router, lan_ip_t local_ip) {
    for (lan_ip_t ip = 0; ip < MAX_ADRESS_COUNT; ip ++) {
        router->path_map[ip] = NO_PATH;

        for (lan_ip_t jp = 0; jp < MAX_ADRESS_COUNT; jp ++)
            router->weight_map[ip][jp] = NO_ROAD;
    }

    router->local_ip = local_ip;
}

void recompute_path_map (struct packet_router_t* router) {
    // TODO remove all the roads that follow the following property
    //   - the starting point of the road can't be reached from local_ip using Depth First Search
    // TODO compute pathmap from weightmap
}

lan_ip_t get_route (struct packet_router_t* router, lan_ip_t target) {
    return router->path_map[target];
}

void modify_route (struct packet_router_t* router, struct route_modification_t *modification) {
    router->weight_map[modification->a][modification->b] = modification->weight;

    recompute_path_map(router);
}

