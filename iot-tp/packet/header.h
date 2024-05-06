
#include "iot-tp/iot-tp-macros.h"
#include "iot-tp/router/iot-tp-routing.h"

struct packet_header_t {
    lan_ip_t sender;
    lan_ip_t receiver;

    uint16_t priority;

    uint32_t size;
    uint32_t packet_id;
};

struct packet_header_t get_header (unsigned char* buffer);
uint32_t write_header (unsigned char* buffer, struct packet_header_t header);

int is_syscall_header (struct packet_header_t header);
