#ifndef BUFFER
#define BUFFER

#define BUFFER_SIZE 256

typedef struct KbBuffer {
    char str[BUFFER_SIZE];
    unsigned char index;
} KbBuffer;

void queue_in_buffer(KbBuffer*, char);
char queue_out_buffer(KbBuffer*);
int is_buf_empty(KbBuffer*);

#endif