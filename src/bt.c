#include <furi/furi.h>
#include "../include/bt.h"
#include "../remote_keyboard.h"

int32_t bt_process(void* p) {
    UNUSED(p);

    uint32_t events;
    while(true) {
        events = furi_thread_flags_wait(ThreadEventAll, FuriFlagWaitAny, FuriFlagWaitAll);
        if(events & ThreadStop) break;
    }
    return 0;
}