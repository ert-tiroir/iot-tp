#pragma once

#include "iot-tp/physical/transaction.h"

START_FULL_NAMESPACE(physical)

struct iot_context_t;

enum physical_channel_type_e {
    SPI_SLAVE  = 0,
    SPI_MASTER = 1,
    WIFI       = 2
};

enum physical_read_state_e {
    NONE = 0,
    FORWARD = 1,
    PARSE   = 2
};

struct physical_channel_t {
    struct iot_buffer_t rxbuf;
    struct physical_transaction_t transaction;

    enum physical_channel_type_e channel_type;
    unsigned char channel_parameters[16];

    enum physical_read_state_e read_state;
    struct physical_channel_t *forward_channel;
};

int can_start_transaction (struct physical_channel_t* channel);

void start_transaction (
    struct physical_channel_t* channel, 
    struct physical_transaction_t transaction
);

void tick (struct iot_context_t *context, struct physical_channel_t* channel);

int init_channel (struct physical_channel_t* channel, enum physical_channel_type_e channel_type, struct iot_buffer_t buffer);

#include "iot-tp/iot-tp-context.h"

END_FULL_NAMESPACE(physical)
