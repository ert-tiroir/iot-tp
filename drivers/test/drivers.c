
#include "iot-tp/physical/drivers.h"

USE_NAMESPACE(nordli::iottp::physical);

void SPI_SLAVE__tick  (struct physical_channel_t* channel) {}
void SPI_MASTER__tick (struct physical_channel_t* channel) {}

void WIFI__tick (struct physical_channel_t* channel) {}

struct physical_channel_t SPI_SLAVE__create  (int SPI_channel) { 
    struct physical_channel_t result;
    return result;
}
struct physical_channel_t SPI_MASTER__create (int SPI_channel) { 
    struct physical_channel_t result;
    return result;
}
struct physical_channel_t WIFI__create () { 
    struct physical_channel_t result;
    return result;
}
