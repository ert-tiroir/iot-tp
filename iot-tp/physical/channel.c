
#include "iot-tp/physical/drivers.h"
#include "iot-tp/packet/header.h"

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

void tick (struct iot_context_t* context, struct physical_channel_t* channel) {
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

    unsigned char* page = readable_page(&channel->rxbuf);
    if (channel->read_state == NONE && page) {
        struct packet_header_t header = get_header(page);

        if (header.receiver == context->router.local_ip) {
            int syscall = is_syscall_header(header);
            unsigned char* page_data = (unsigned char*) ( ((struct packet_header_t*) page) + 1 );
            if (syscall) {
                switch (syscall) {
                    case 1:
                        // TODO
                        break ;
                    case 2:
                        lan_ip_t a = page_data[0];
                        lan_ip_t b = page_data[1];
                        lan_ip_t w = page_data[2];

                        w &= 127;
                        struct route_modification_t modification;
                        modification.a = a;
                        modification.b = b;
                        modification.weight = w;
                        modify_route( &context->router, &modification );

                        if (page_data[2] & 128) {
                            modification.a = b;
                            modification.b = a;
                            modification.weight = w;
                            modify_route( &context->router, &modification );
                        }
                        break ;
                    case 3:
                        unsigned char  uri_size = page_data[0];
                        unsigned char* uri      = page_data + 1;

                        // TODO
                        break ;
                    case 4:
                        break ;
                }

                free_read(&channel->rxbuf);
            } else {
                // TODO use parse
            }
        } else {
            lan_ip_t target_lan_ip = get_route( &context->router, header.receiver );

            struct physical_channel_t* target_channel = context->channels + target_lan_ip;

            if (can_start_transaction(target_channel)) {
                struct physical_transaction_t transaction;
                transaction.buffer = &channel->rxbuf;
                transaction.sent   = 0;
                transaction.size   = header.size;

                start_transaction(target_channel, transaction);
                channel->read_state = FORWARD;
                channel->forward_channel = target_channel;
            }
        }
    }

    if (channel->read_state == PARSE) {

    } else if (channel->read_state == FORWARD) {
        if (channel->forward_channel->transaction.sent >= channel->forward_channel->transaction.size) {
            struct physical_transaction_t transaction;
            transaction.size = 0;
            transaction.sent = 0;
            transaction.buffer = 0;
            start_transaction(channel->forward_channel, transaction);
            channel->read_state = NONE;
        }
    }
}

int init_channel (struct physical_channel_t* channel, enum physical_channel_type_e channel_type, struct iot_buffer_t buffer) {
    channel->channel_type = channel_type;

    channel->rxbuf = buffer;   

    channel->read_state = NONE;
}
