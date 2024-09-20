#include "ring_buffer.h"
bool ring_buffer_initialize(ring_buffer_t *rb, uint8_t *buffer, int MAX_LEN)
{
    rb->buffer = buffer;
    rb->head = 0;
    rb->tail = 0;
    rb->size = MAX_LEN;
    return SUCCESS;
}
bool ring_buffer_write(ring_buffer_t *rb, uint8_t data)
{

    int current_write_index = rb->tail;
    int current_read_index = rb->head;

    int next_write_index = current_write_index + 1;
    // if next write index >= size -> go to index 0
    if (next_write_index >= rb->size)
    {
        next_write_index = 0;
    }
    if (next_write_index == current_read_index)
    {
        return FAILED;
    }
    rb->buffer[current_write_index] = data;
    rb->tail = next_write_index;
    return SUCCESS;
}
bool ring_buffer_read(ring_buffer_t *rb, uint8_t *data_read)
{

    int current_write_index = rb->tail;
    int current_read_index = rb->head;
    int next_read_index = current_read_index + 1;
    if (next_read_index >= rb->size)
    {
        next_read_index = 0;
    }

    if (current_write_index == current_read_index)
    {
        return FAILED;
    }
    *data_read = rb->buffer[current_read_index];
    rb->head = next_read_index;
    return SUCCESS;
}