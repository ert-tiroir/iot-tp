
#include "iot-tp/physical/drivers.h"

// No raspberry pi driver enabled yet
void WIFI__tick (struct physical_channel_t* channel) {}
struct physical_channel_t WIFI__create () { 
    struct physical_channel_t result;
    return result;
}
