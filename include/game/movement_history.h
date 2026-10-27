#ifndef GAME_MOVEMENT_HISTORY_H
#define GAME_MOVEMENT_HISTORY_H
#include "ps2/prelude.h"

/* Accessed native prefixes; original class identities and allocation sizes are
 * UNVERIFIED. The five samples have a verified 0x20 stride and quadword alignment. */
typedef struct {
    s128 point;
    f32 timestamp;
    s32 id;
    s32 value;
    u8 unk_1C[4];
} Recovered_MovementSample;

typedef struct {
    void* owner;
    u8 unk_04[0x28];
    s32 mask;
    u8 unk_30[0x10];
    f32 amount;
    f32 thresholds[4];
    f32 resetValues[4];
    s32 state;
    s32 requestedState;
    u8 unk_6C[4];
    Recovered_MovementSample samples[5];
    s32 nextSampleId; /* UNVERIFIED: the allocator remains a draft. */
    f32 timer;
} Recovered_MovementHistory;

typedef char MovementSampleStride[sizeof(Recovered_MovementSample) == 0x20 ? 1 : -1];
typedef char MovementHistoryMask[(u32)&((Recovered_MovementHistory*)0)->mask == 0x2C ? 1 : -1];
typedef char MovementHistoryState[(u32)&((Recovered_MovementHistory*)0)->state == 0x64 ? 1 : -1];
typedef char MovementHistorySamples[(u32)&((Recovered_MovementHistory*)0)->samples == 0x70 ? 1 : -1];
typedef char MovementHistoryTimer[(u32)&((Recovered_MovementHistory*)0)->timer == 0x114 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
s32 func_00185B50(Recovered_MovementHistory* self, s32 id);
void func_00185B80(Recovered_MovementHistory* self, s32 id);
s32 func_00185C38(Recovered_MovementHistory* self, s32 id);
#ifdef __cplusplus
}
#endif
#endif
