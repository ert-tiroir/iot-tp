#pragma once

#include "iot-tp/iot-tp-macros.h"

START_FULL_NAMESPACE(routing)

#define lan_ip_t uint8_t

#define NO_PATH 255
#define NO_ROAD 0

struct packet_router_t {
    // LAN-IP [NRD-A 001, Section 1.2]
    lan_ip_t local_ip;

    // path_map[i] contains the LAN-IP [NRD-A 001, Section 1.2] of a directly connected
    // device, towards which a packet will be rerouted to go to the destination.
    // if no path exists between local_ip and device i, then path_map[i] = NO_PATH
    lan_ip_t path_map[MAX_ADRESS_COUNT];
    // weight_map[i][j] contains the weight [NRD-A 001, Section 3] of the direct connection
    // from device i to j. If no direct connection exists between i and j, its value is NO_ROAD
    uint8_t weight_map[MAX_ADRESS_COUNT][MAX_ADRESS_COUNT];
};

// route modification query, as defined in NRD-A 001, Section 3.2,
// where weight is an integer between 0 and 127, 0 meaning that the route
// is to be removed (NO_ROAD) and any other integer means that the route will exist
// with the weight
struct route_modification_t {
    lan_ip_t a, b;
    uint8_t weight;
};

// initialize the router with the local LAN-IP
void initialize (struct packet_router_t* router, lan_ip_t local_ip);

// recompute the path map from the weight map
void recompute_path_map (struct packet_router_t* router);

// get the route to the target
lan_ip_t get_route (struct packet_router_t* router, lan_ip_t target);

// modify a route
void modify_route (struct packet_router_t* router, struct route_modification_t *modification);

END_FULL_NAMESPACE(routing)
