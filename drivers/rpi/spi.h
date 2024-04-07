#pragma once

const int SPI_AVL[2] = { 4, 5 };
const int SPI_AVL_size = 2;

const int DATA_MASTER = 15;
const int DATA_SLAVE  = 16;

struct rpi_spi_channel_parameters_t {
    int SPI_channel;

    int SPI_AVL_offset;
};
