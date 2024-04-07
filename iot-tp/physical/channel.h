#pragma once

#include "iot-tp/physical/transaction.h"

START_FULL_NAMESPACE(physical)

enum physical_channel_type_e {
    SPI_SLAVE  = 0,
    SPI_MASTER = 1,
    WIFI       = 2
};

struct physical_channel_t {
    struct iot_buffer_t rxbuf;
    struct physical_transaction_t transaction;

    enum physical_channel_type_e channel_type;
    unsigned char channel_parameters[16];
};

int can_start_transaction (struct physical_channel_t* channel);

void start_transaction (
    struct physical_channel_t* channel, 
    struct physical_transaction_t transaction
);

void tick (struct physical_channel_t* channel);

int init_channel (struct physical_channel_t* channel, enum physical_channel_type_e channel_type, struct iot_buffer_t buffer);

END_FULL_NAMESPACE(physical)
