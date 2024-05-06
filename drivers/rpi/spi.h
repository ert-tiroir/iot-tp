#pragma once

const int SPI_AVL_0 = 4;
const int SPI_AVL_1 = 5;

const int SPI_AVL_size = 2;

const int SPI_DS    = 15;
const int SPI_DM_BS = 16;
const int SPI_DM_AS = 11;

struct rpi_spi_channel_parameters_t {
    int SPI_channel;

    int SPI_AVL_offset;
};
