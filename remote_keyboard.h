#ifndef REMOTE_KEYBOARD_H
#define REMOTE_KEYBOARD_H

#include <bt/bt_service/bt.h>
#include "include/buffer.h"

typedef enum { INIT, OK, KO, WAITING, READY } Conn_status;

typedef struct Status_Ctx {
    Conn_status usb_status;
} Status_Ctx;

typedef struct {
    bool usb_connected;
    BtStatus bt_connected;
} RemoteKbState;

typedef enum {
    ThreadStop = (1 << 0),
    ThreadEventUsbConnect = (1 << 1),
    ThreadEventUsbDisconnect = (1 << 2),
    ThreadEventAll = ThreadStop | ThreadEventUsbConnect | ThreadEventUsbDisconnect,
} RemoteKbThreadEvent;

typedef struct RemoteKbApp {
    FuriThread* gui_thread;
    FuriThread* usb_thread;
    FuriThread* bt_thread;

    Bt* bt;

    KbBuffer* kb_buffer;
    RemoteKbState state;
} RemoteKbApp;

#endif // REMOTE_KEYBOARD_H