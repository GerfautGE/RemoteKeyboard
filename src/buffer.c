#include "../include/buffer.h"

void queue_in_buffer(KbBuffer* buf, char c) {
    buf->str[buf->index++] = c;
}

char queue_out_buffer(KbBuffer* buf) {
    return buf->str[--(buf->index)];
}

int is_buf_empty(KbBuffer* buf) {
    return buf->index == 0;
}