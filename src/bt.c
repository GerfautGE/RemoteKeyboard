#include <furi/furi.h>
#include <furi_hal_bt.h>
#include <furi_hal_bt_serial.h>
#include "../include/bt.h"
#include "../remote_keyboard.h"


static void bt_hid_connection_status_changed_callback(BtStatus Bt, void* p) {
    furi_assert(p);
    RemoteKbApp* app = p;
    app->state.bt_connected = Bt;
}

int32_t bt_process(void* p) {
    RemoteKbApp* app = p;
    bt_disconnect(app->bt);

    //wait 2nd core
    furi_delay_ms(200);

    if(!bt_set_profile(app->bt, BtProfileSerial)) {
        return -1;
    }

    furi_hal_bt_start_advertising();
    bt_set_status_changed_callback(app->bt, bt_hid_connection_status_changed_callback, app);

    uint32_t events;
    while(true) {
        events = furi_thread_flags_wait(ThreadEventAll, FuriFlagWaitAny, FuriFlagWaitAll);
        if(events & ThreadStop) break;
    }
    return 0;
}