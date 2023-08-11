#ifndef REMOTE_KEYBOARD_H
#define REMOTE_KEYBOARD_H

#include <stdbool.h>

#define BUFFER_SIZE 256

typedef enum { INIT, OK, KO, WAITING, READY } Conn_status;

typedef struct Status_Ctx {
    Conn_status usb_status;
} Status_Ctx;

typedef struct GuiConStatus {
    char* str;
    int offset;
} GuiConStatus;

typedef struct {
    bool usb_connected;
} RemoteKbState;

typedef enum {
    ThreadStop = (1 << 0),
    ThreadEventUsbConnect = (1 << 1),
    ThreadEventUsbDisconnect = (1 << 2),
    ThreadEventAll = ThreadStop | ThreadEventUsbConnect | ThreadEventUsbDisconnect,
} RemoteKbThreadEvent;

typedef struct RemoteKbApp RemoteKbApp;

typedef struct KbBuffer {
    char str[BUFFER_SIZE];
    unsigned char index;
} KbBuffer;

void queue_in_buffer(KbBuffer* buf, char c) {
    buf->str[buf->index++] = c;
}

char queue_out_buffer(KbBuffer* buf) {
    return buf->str[--(buf->index)];
}

bool is_buf_empty(KbBuffer* buf) {
    return buf->index == 0;
}

#endif // REMOTE_KEYBOARD_H