#pragma once

#include "physical/channel.h"

void SPI_SLAVE__tick  (struct physical_channel_t* channel);
void SPI_MASTER__tick (struct physical_channel_t* channel);

void WIFI__tick (struct physical_channel_t* channel);
