#include <furi_hal.h>
#include <furi/furi.h>
#include "../include/usb.h"
#include "../remote_keyboard.h"

int32_t usb_process(void* p) {
    RemoteKbApp* app = p;

    //init USB mode interface (HID)
    FuriHalUsbInterface* usb_prev_mode = furi_hal_usb_get_config();
    if(furi_hal_usb_is_locked()) {
        furi_hal_usb_unlock();
    }
    furi_check(furi_hal_usb_set_config(&usb_hid, NULL) == true);

    uint32_t events;
    while(true) {
        events = furi_thread_flags_wait(ThreadEventAll, FuriFlagWaitAny, FuriFlagWaitAll);

        if(furi_hal_hid_is_connected()) {
            app->state.usb_connected = true;
        } else {
            app->state.usb_connected = false;
        }
        if(!is_buf_empty(app->kb_buffer)) {
            char c = queue_out_buffer(app->kb_buffer);
            furi_hal_hid_kb_press(HID_ASCII_TO_KEY(c));
            furi_hal_hid_kb_release(HID_ASCII_TO_KEY(c));
        }
        if(events & ThreadStop) {
            break;
        }
    }

    // reset USB Mode
    furi_hal_usb_set_config(usb_prev_mode, NULL);

    return 0;
}