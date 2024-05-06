
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

void dfs (struct packet_router_t* router, int* reachable, int node) {
    if (reachable[node]) return ;
    reachable[node] = 1;

    for (int next = 0; next < MAX_ADRESS_COUNT; next ++)
        if (router->weight_map[node][next] != NO_PATH)
            dfs(router, reachable, next);
}

void recompute_path_map (struct packet_router_t* router) {
    int reach_map[MAX_ADRESS_COUNT];
    for (int i = 0; i < MAX_ADRESS_COUNT; i ++) reach_map[i] = 0;

    dfs(router, reach_map, router->local_ip);

    for (int i = 0; i < MAX_ADRESS_COUNT; i ++) {
        if (reach_map[i]) continue ;

        for (int j = 0; j < MAX_ADRESS_COUNT; j ++)
            router->weight_map[i][j] = NO_PATH;
    }

    const int MAX_DIST = 1e9;

    // TODO maybe implement dijkstra with priority queue
    int   distances[MAX_ADRESS_COUNT];
    lan_ip_t parent[MAX_ADRESS_COUNT];
    for (int i = 0; i < MAX_ADRESS_COUNT; i ++) {
        distances[i] = MAX_DIST;
        parent   [i] = NO_ROAD;
    }
    
    distances[router->local_ip] = - 1;
    for (int i = 0; i < MAX_ADRESS_COUNT; i ++) {
        if (router->weight_map[router->local_ip][i] != NO_PATH) {
            distances[i] = router->weight_map[router->local_ip][i];
            parent   [i] = i;
        }
    }

    for (int e = 0; e < MAX_ADRESS_COUNT; e ++) {
        int mini = -1;
        for (int i = 0; i < MAX_ADRESS_COUNT; i ++)
            if (distances[i] != -1 && distances[i] != MAX_DIST && (mini == -1 || distances[i] < distances[mini]))
                mini = i;
        if (mini == -1) break ;

        for (int j = 0; j < MAX_ADRESS_COUNT; j ++) {
            int next_dist = distances[mini] + router->weight_map[mini][j];
            if (router->weight_map[mini][j] == NO_PATH) continue ;
            if (next_dist >= distances[j]) continue ;

            distances[j] = next_dist;
            parent   [j] = parent[mini];
        }
        distances[mini] = -1;
    }

    for (int i = 0; i < MAX_ADRESS_COUNT; i ++)
        router->path_map[i] = parent[i];
}

lan_ip_t get_route (struct packet_router_t* router, lan_ip_t target) {
    return router->path_map[target];
}

void modify_route (struct packet_router_t* router, struct route_modification_t *modification) {
    router->weight_map[modification->a][modification->b] = modification->weight;

    recompute_path_map(router);
}

