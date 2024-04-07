
#include "buffer/buffer.h"

size_t next (size_t value, struct iot_buffer_t buffer) {
    return (value + buffer.pag_size) & buffer.max_mask;
}

size_t max_size (struct iot_buffer_t* buffer) {
    return buffer->max_size;
}
size_t pag_size (struct iot_buffer_t* buffer) {
    return buffer->pag_size;
}

size_t size (struct iot_buffer_t* buffer) {
    size_t max_page_mask = buffer->max_size - 1;
    
    return (buffer->right + buffer->max_size - buffer->left) & max_page_mask;
}

unsigned char* writable_page (struct iot_buffer_t* buffer) {
    if (next(buffer->right, *buffer) == buffer->left) return 0;

    return buffer->target + buffer->right;
}
unsigned char* readable_page (struct iot_buffer_t* buffer) {
    if (buffer->left == buffer->right) return 0;

    return buffer->target + buffer->left;
}

void free_write (struct iot_buffer_t* buffer) {
    buffer->right = next(buffer->right, *buffer);
}
void free_read (struct iot_buffer_t* buffer) {
    buffer->left = next(buffer->left, *buffer);
}

struct iot_buffer_t create_iot_buffer (size_t page, size_t page_count, unsigned char* target) {
    size_t size = page * page_count;
    struct iot_buffer_t result = {
        .left  = 0,
        .right = 0,

        .max_size = size,
        .max_mask = size - 1,
        .pag_size = page,

        .target = target
    };

    return result;
}
