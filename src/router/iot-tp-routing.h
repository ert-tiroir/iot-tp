
#include "iot-tp-macros.h"

START_FULL_NAMESPACE(routing)

#define lan_ip_t uint8_t

#define NO_PATH 0
#define NO_ROAD 0

struct packet_router_t {
    lan_ip_t local_ip;
    
    lan_ip_t   path_map[MAX_ADRESS_COUNT];
    uint8_t  weight_map[MAX_ADRESS_COUNT][MAX_ADRESS_COUNT];
};

enum route_modification_operand_e {
    ADD = 1,
    DELETE = 2
};

struct route_modification_t {
    lan_ip_t a, b;
    uint8_t weight;

    enum route_modification_operand_e operand;
};

void initialize (struct packet_router_t* router, lan_ip_t local_ip);

void recompute_path_map (struct packet_router_t* router);

lan_ip_t get_route (struct packet_router_t* router, lan_ip_t target);

void modify_route (struct packet_router_t* router, struct route_modification_t *modification);

END_FULL_NAMESPACE(routing)
