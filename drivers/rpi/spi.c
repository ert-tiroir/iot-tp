
#include "iot-tp/buffer/buffer.h"
#include "iot-tp/physical/drivers.h"
#include "drivers/rpi/spi.h"

#include "wiringPi.h"
#include "wiringPiSPI.h"

USE_NAMESPACE(nordli::iottp::physical);

const int SPI_CLK_SPEED = 16000000;

// The raspberry pi does not support slave mode SPI
void SPI_SLAVE__tick  (struct physical_channel_t* channel) {}

void SPI_MASTER__tick (struct physical_channel_t* channel) {
    int SPI_AVL[2] = { SPI_AVL_0, SPI_AVL_1 };
    struct rpi_spi_channel_parameters_t* params = channel->channel_parameters;

    unsigned char* rxbuf = writable_page( &channel->rxbuf );
    if (!rxbuf) return ;

    int data_master = LOW;
    if (channel->transaction.buffer) {
        unsigned char* txbuf = readable_page( channel->transaction.buffer );

        if (txbuf) {
            for (int idx = 0; idx < channel->transaction.buffer->pag_size; idx ++)
                rxbuf[idx] = txbuf[idx];

            free_read(channel->transaction.buffer);
            data_master = HIGH;
        }
    }

    while (params->SPI_AVL_offset == -1) {
        for (int p = 0; p < SPI_AVL_size; p ++) {
            if (digitalRead(SPI_AVL[p])) {
                params->SPI_AVL_offset = p;
                break ;
            }
        }
    }

    int pin = SPI_AVL[params->SPI_AVL_offset];
    int cnt = 0;
    while (!digitalRead(pin)) cnt ++;

    digitalWrite(DATA_MASTER, data_master);

    int data_slave = digitalRead(DATA_SLAVE);

    wiringPiSPIDataRW(params->SPI_channel, rxbuf, channel->rxbuf.pag_size);

    params->SPI_AVL_offset ++;
    if (params->SPI_AVL_offset == SPI_AVL_size) params->SPI_AVL_offset = 0;

    if (data_slave)
        free_write(&channel->rxbuf);
}

struct physical_channel_t SPI_SLAVE__create  (int SPI_channel) { 
    struct physical_channel_t result;
    return result;
}
struct physical_channel_t SPI_MASTER__create (int SPI_channel) { 
    struct physical_channel_t result;

    result.transaction.buffer = 0;

    result.transaction.size = 0;
    result.transaction.sent = 0;

    struct rpi_spi_channel_parameters_t* params = result.channel_parameters;

    params->SPI_AVL_offset = -1;
    params->SPI_channel = SPI_channel;

    int fd = wiringPiSPISetupMode(SPI_channel, SPI_CLK_SPEED, 0);
    if (fd == -1)
        printf("Failed to init SPI communication.\n");

    return result;
}
