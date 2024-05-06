
#include "iot-tp/buffer/buffer.h"
#include "iot-tp/physical/drivers.h"
#include <stdio.h>

#include "driver/spi_slave.h"

const int PAGE_SIZE = 1024;

const int SPI_DS    = 6;
const int SPI_DM_BS = 5;
const int SPI_DM_AS = 4;

const int SPI_AVL0 = 17;
const int SPI_AVL1 = 18;

int SPI_AVL[2] = {SPI_AVL0, SPI_AVL1};
int SPI_AVL_offset = 0;

const int SPI_AVL_SIZE = 2;

DMA_ATTR uint8_t rxbuf[PAGE_SIZE];
DMA_ATTR uint8_t txbuf[PAGE_SIZE];

int spi_slave_has_data  = 0;
int spi_master_has_data = 0;

void spi_slave_post_setup_cb(spi_slave_transaction_t *trans)
{
    digitalWrite(SPI_AVL[SPI_AVL_offset], HIGH);
    digitalWrite(SPI_DS, spi_slave_has_data);
}

void spi_slave_post_trans_cb(spi_slave_transaction_t *trans)
{
    digitalWrite(SPI_AVL[SPI_AVL_offset], LOW);
    SPI_AVL_offset++;
    if (SPI_AVL_offset == SPI_AVL_SIZE)
        SPI_AVL_offset = 0;
}

void SPI_SLAVE__tick  (struct physical_channel_t* channel) {
    unsigned char* write_page = writable_page(&channel->rxbuf);
    if (!write_page) return ;

    spi_slave_has_data  = LOW;
    spi_master_has_data = 0;

    if (channel->transaction.buffer) {
        unsigned char* page = readable_page(&channel->transaction.buffer);

        if (page) {
            for (int i = 0; i < PAGE_SIZE; i ++)
                txbuf[i] = page[i];

            spi_slave_has_data = HIGH;

            free_read(&channel->transaction.buffer);
        }
    }

    if (digitalRead(SPI_DM_BS)) spi_master_has_data = 1; 

    if (!(spi_slave_has_data || spi_master_has_data)) return ;

    spi_slave_transaction_t t;
    memset(&t, 0, sizeof(t));

    t.length    = PAGE_SIZE * 8;
    t.trans_len = PAGE_SIZE * 8;
    t.rx_buffer = rxbuf;
    t.tx_buffer = txbuf;
    esp_err_t ret = spi_slave_transmit(SPI2_HOST, &t, portMAX_DELAY);
    
    if (digitalRead(SPI_DM_AS)) spi_master_has_data = 1; 

    for (int i = 0; i < PAGE_SIZE; i ++)
        write_page[i] = rxbuf[i];
    free_write(&channel->rxbuf);
}

// ESP32::IOT-TP does not support master mode SPI yet
void SPI_MASTER__tick (struct physical_channel_t* channel) {}

struct physical_channel_t SPI_SLAVE__create  (int SPI_channel) { 
    struct physical_channel_t result;
    result.

    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .mosi_io_num = MOSI,
        .miso_io_num = MISO,
        .sclk_io_num = SCK,
        .data2_io_num = -1,
        .data3_io_num = -1,
        .data4_io_num = -1,
        .data5_io_num = -1,
        .data6_io_num = -1,
        .data7_io_num = -1,
        .max_transfer_sz = 4096,
        .flags = SPICOMMON_BUSFLAG_SLAVE,
        .intr_flags = 0};
    spi_slave_interface_config_t slvcfg = {
        .spics_io_num = SS,
        .flags = 0,
        .queue_size = 1,
        .mode = SPI_MODE0,
        .post_setup_cb = spi_slave_post_setup_cb,
        .post_trans_cb = spi_slave_post_trans_cb,
    };
    ret = spi_slave_initialize(SPI2_HOST, &buscfg, &slvcfg, SPI_DMA_CH_AUTO);

    if (ret != ESP_OK)
    {
        Serial.println("\n==========\nINIT ERROR\n==========\n");
        return result;
    }

    result.transaction.buffer = 0;
    result.transaction.size   = 0;
    result.transaction.sent   = 0;

    return result;
}
struct physical_channel_t SPI_MASTER__create (int SPI_channel) { 
    struct physical_channel_t result;
    return result;
}
