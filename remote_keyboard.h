#ifndef REMOTE_KEYBOARD_H
#define REMOTE_KEYBOARD_H


typedef enum { INIT, OK, KO, WAITING, READY} Conn_status;

typedef struct Status_Ctx {
    Conn_status usb_status;
} Status_Ctx;

typedef struct GuiConStatus {
    char* str;
    int offset;
} GuiConStatus;

static GuiConStatus stat_conn = {"Connected", 10};
static GuiConStatus stat_no_conn = {"No Conn", 18};

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


#endif // REMOTE_KEYBOARD_H