#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/effects/asset.h"

void func_001AFC78(BkActorTimerPS2 *unused) {}

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

#ifdef NON_MATCHING
// Unmatched: packed maximum and repeat-write scheduling differ.
s32 func_001AFC80(BkActorTimerPS2* timer, BkActorAssetPS2* asset, s32 index) {
    BkActorAssetRecordPS2* record = &asset->records[index];
    timer->index = index;
    timer->remaining = record->duration;
    record = &asset->records[index];
    timer->repeat = record->repeat;
    if (timer->repeat < 1)
        timer->repeat = 1;
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_1af930_1afc78", func_001AFC80);
#endif
#ifdef NON_MATCHING
// Unmatched: record-index register and address operand order differ; return contract is UNVERIFIED.
void func_001AFD18(BkActorTimerPS2* timer, BkActorAssetPS2* asset, s32 stop) {
    s32 firstIndex = timer->index;
    if (firstIndex != -1) {
        s32 nextIndex;
        if (stop != 0)
            timer->index = -1;
        else {
            BkActorAssetRecordPS2* record = (BkActorAssetRecordPS2*)(firstIndex * 0xD0 + (u32)asset->records);
            timer->index = record->next;
        }
        nextIndex = timer->index;
        if (nextIndex != -1) {
            BkActorAssetRecordPS2* record = (BkActorAssetRecordPS2*)(nextIndex * 0xD0 + (u32)asset->records);
            timer->remaining = record->duration;
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_1af930_1afc78", func_001AFD18);
#endif
