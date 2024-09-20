#ifndef INC_RING_BUFFER_H
#define INC_RING_BUFFER_H

#include "common_defines.h"
/*
    create a ring buffer (circular buffer)
*/
typedef struct
{
    // head -> READ
    // tail -> WRITE
    uint8_t *buffer;
    int head;
    int tail;
    int size;
} ring_buffer_t;

bool ring_buffer_initialize(ring_buffer_t *rb, uint8_t *buffer, int MAX_LEN);
bool ring_buffer_write(ring_buffer_t *rb, uint8_t data);
bool ring_buffer_read(ring_buffer_t *rb, uint8_t *data_read);
#endif