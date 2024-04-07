#pragma once

#include "iot-tp-macros.h"
#include "buffer/buffer.h"

START_FULL_NAMESPACE(physical)

struct physical_transaction_t {
    struct iot_buffer_t* buffer;

    size_t size;
    size_t sent;
};

END_FULL_NAMESPACE(physical)
