#include "ps2/prelude.h"

s32 func_00275340(const u16* text) {
    s32 count = 0;
    while (*text) {
        text++;
        count++;
    }
    return count;
}

u16* func_00275370(u16* destination, const u16* source) {
    for (;; source++, destination++) {
        *destination = *source;
        if (!*source) break;
    }
    return destination;
}
