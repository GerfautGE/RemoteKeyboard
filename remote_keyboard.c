#include <furi.h>

#include "include/bt.h"
#include "include/gui.h"
#include "include/usb.h"

#include "remote_keyboard.h"

void remote_app_get_state(RemoteKbApp* app, RemoteKbState* state) {
    *state = app->state;
}

void thread_send_stop(FuriThread* thread) {
    furi_thread_flags_set(furi_thread_get_id(thread), ThreadStop);
}

RemoteKbApp* remotekb_app_alloc() {
    RemoteKbApp* app = malloc(sizeof(RemoteKbApp));
    app->gui_thread = furi_thread_alloc_ex("RemoteKbGui", 1024, gui_process, app);
    app->usb_thread = furi_thread_alloc_ex("RemoteKbUsb", 1024, usb_process, app);
    app->bt_thread = furi_thread_alloc_ex("RemoteKbBt", 1024, bt_process, app);

    app->kb_buffer = malloc(sizeof(KbBuffer));

    app->kb_buffer->index = 0;
    app->kb_buffer->str[app->kb_buffer->index] = 0;

    return app;
}

static void remotekb_app_free(RemoteKbApp* app) {
    furi_assert(app);
    furi_thread_free(app->gui_thread);
    furi_thread_free(app->usb_thread);
    furi_thread_free(app->bt_thread);
    free(app->kb_buffer);
    free(app);
}

static RemoteKbApp* app_handle = NULL;

int32_t remote_keyboard_app(void* p) {
    UNUSED(p);

    //alloc app
    RemoteKbApp* app = remotekb_app_alloc();
    app_handle = app;

    //start threads
    furi_thread_start(app->usb_thread);
    furi_thread_start(app->bt_thread);
    furi_thread_start(app->gui_thread);

    //wait for gui thread to finish
    furi_thread_join(app->gui_thread);

    //send stop to other threads
    thread_send_stop(app->usb_thread);
    thread_send_stop(app->bt_thread);

    //wait for them to finish
    furi_thread_join(app->usb_thread);
    furi_thread_join(app->bt_thread);

    //free app
    remotekb_app_free(app);

    return 0;
}
