#pragma once

#include "iot-tp/physical/channel.h"

START_FULL_NAMESPACE(physical);

void SPI_SLAVE__tick  (struct physical_channel_t* channel);
void SPI_MASTER__tick (struct physical_channel_t* channel);

void WIFI__tick (struct physical_channel_t* channel);

struct physical_channel_t SPI_SLAVE__create  (int SPI_channel);
struct physical_channel_t SPI_MASTER__create (int SPI_channel);
struct physical_channel_t WIFI__create ();

END_FULL_NAMESPACE(physical);
