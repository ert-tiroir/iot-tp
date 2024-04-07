
#include "iot-tp/physical/drivers.h"

USE_NAMESPACE(nordli::iottp::physical);

int can_start_transaction (struct physical_channel_t* channel) {
    return channel->transaction.buffer == 0;
}

void start_transaction (
    struct physical_channel_t* channel, 
    struct physical_transaction_t transaction
) {
    channel->transaction = transaction;
}

void tick (struct physical_channel_t* channel) {
    switch (channel->channel_type) {
        case (SPI_SLAVE): {
            SPI_SLAVE__tick(channel);
            break ;
        }
        case (SPI_MASTER): {
            SPI_MASTER__tick(channel);
            break ;
        }
        case (WIFI): {
            WIFI__tick(channel);
            break ;
        }
    }
}

int init_channel (struct physical_channel_t* channel, struct iot_buffer_t buffer) {
    
}
