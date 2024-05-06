#pragma once

#include "iot-tp-macros.h"

#include "iot-tp/router/iot-tp-routing.h"
#include "iot-tp/physical/channel.h"

struct iot_context_t {
    struct packet_router_t router;
    struct physical_channel_t channels[MAX_ADRESS_COUNT];
};
