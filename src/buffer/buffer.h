
#pragma once
#include "iot-tp-macros.h"

struct iot_buffer_t {
    size_t left;
    size_t right;

    size_t max_size; // max_size must be a power of 2 times pag_size
    size_t max_mask; // max_size - 1 precomputed
    size_t pag_size; // pag_size must be a power of 2

    unsigned char* target;    
};

size_t size     (struct iot_buffer_t* buffer);
size_t max_size (struct iot_buffer_t* buffer);
size_t pag_size (struct iot_buffer_t* buffer);

unsigned char* writable_page (struct iot_buffer_t* buffer);
unsigned char* readable_page (struct iot_buffer_t* buffer);

void free_write (struct iot_buffer_t* buffer);
void free_read  (struct iot_buffer_t* buffer);

struct iot_buffer_t create_iot_buffer (size_t page, size_t size, unsigned char* target);
