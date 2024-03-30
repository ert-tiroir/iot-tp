
#include <router/iot-tp-routing.h>

USE_NAMESPACE(nordli::iottp::routing)

void initialize (struct packet_router_t* router, lan_ip_t local_ip) {
    // TODO initialize the values inside pathmap and weightmap to NO_PATH and NO_ROAD
}

void recompute_path_map (struct packet_router_t* router) {
    // TODO remove all the roads that follow the following property
    //   - the starting point of the road can't be reached from local_ip using Depth First Search
    // TODO compute pathmap from weightmap
}

lan_ip_t get_route (struct packet_router_t* router, lan_ip_t target) {
    // TODO get the route from pathmap
}

void modify_route (struct packet_router_t* router, struct route_modification_t *modification) {
    // TODO modify weightmap using the route modification data
    // TODO recompute the path map
}

