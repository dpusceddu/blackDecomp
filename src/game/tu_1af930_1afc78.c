#include "auto/prelude.h"
#include "game/actor/asset.h"

void func_001AFC78(void) {}

s32 func_001AFCC8(void) {
    return 1;
}

void func_001AFCD0(void) {}

s32 func_001AFCD8(BkActorTimerPS2 *timer, float elapsed) {
    float remaining;
    if (timer->index != -1) {
        remaining = timer->remaining - elapsed;
        timer->remaining = remaining;
        if (remaining <= 0.0f) {
            timer->remaining = 0.0f;
            return 1;
        }
    }
    return 0;
}

s32 func_001AFDA8(BkActorTimerPS2 *timer) {
    return timer->index;
}

float func_001AFDB0(BkActorTimerPS2 *timer) {
    return timer->remaining;
}

s32 func_001AFDB8(s32 mode) {
    if (mode == 0) goto quarter;
    if (mode == 1) goto half;
    return 1;
quarter:
    return 4;
half:
    return 2;
}

void *func_001AFF88(s32 context_address, s32 kind) {
    int entry_address = context_address + kind * 4;
    return M2C_FIELD(entry_address, void **, 0x214);
}
