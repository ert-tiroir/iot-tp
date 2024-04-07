
#include "buffer/buffer.h"
#include "physical/drivers.h"
#include "drivers/rpi/spi.h"

#include "wiringPi.h"
#include "wiringPiSPI.h"

// The raspberry pi does not support slave mode SPI
void SPI_SLAVE__tick  (struct physical_channel_t* channel) {}

void SPI_MASTER__tick (struct physical_channel_t* channel) {
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

