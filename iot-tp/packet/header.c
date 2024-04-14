
#include "iot-tp/packet/header.h"

struct packet_header_t get_header (unsigned char* buffer) {
    return *((struct packet_header_t*) buffer);
}

uint32_t write_header (unsigned char* buffer, struct packet_header_t header) {
    struct packet_header_t* header_buffer = buffer;

    *header_buffer = header;

    return (uint32_t) sizeof(struct packet_header_t);
}
