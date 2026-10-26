#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

extern s32 D_003C0E04;
extern s32 D_0040EBA8;
extern f32 D_0040EBAC;

typedef struct {
    s32 unk_00[5];
    s32 unk_14;
    s32 unk_18;
    f32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 unk_28;
} Recovered_FrameState; /* Field meanings UNVERIFIED. */

s32 func_0027F6D8(void *arg0) {
    void *temp_2;

    temp_2 = (void *) (((u32) arg0) + ((u32) M2C_FIELD(arg0, void **, 0)));
    M2C_FIELD(arg0, void **, 0) = temp_2;
    M2C_FIELD(arg0, void **, 4) = (void *) ((void *) (((u32) arg0) + ((u32) M2C_FIELD(arg0, void **, 4))));
    return (s32) temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8_27f6d8", func_0027F6F8);

#include "ps2/recovered_types.h"

s32 func_0027F708(void *arg0) {
    void *temp_2;

    temp_2 = (void *) (((u32) arg0) + ((u32) M2C_FIELD(arg0, void **, 0)));
    M2C_FIELD(arg0, void **, 0) = temp_2;
    M2C_FIELD(arg0, void **, 4) = (void *) ((void *) (((u32) arg0) + ((u32) M2C_FIELD(arg0, void **, 4))));
    return (s32) temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8_27f6d8", func_0027F728);
#ifdef NON_MATCHING
// Unmatched: division guard and instruction scheduling differ.
s32 func_0027F730(s32 rate) {
    s32 milliseconds = 1000 / rate;
    f32 seconds = 1.0f / (f32) rate;
    D_003C0E04 = 0;
    D_0040EBAC = seconds;
    D_0040EBA8 = milliseconds;
    return 1;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8_27f6d8", func_0027F730);
#ifdef NON_MATCHING
// Unmatched: field initialization scheduling differs.
s32 func_0027F790(Recovered_FrameState *state) {
    s32 frame;
    state->unk_00[0] = 0;
    state->unk_00[1] = 0;
    state->unk_00[2] = 0;
    state->unk_00[3] = 0;
    state->unk_00[4] = 0;
    frame = D_003C0E04;
    state->unk_24 = 1;
    state->unk_14 = frame;
    state->unk_20 = 0;
    state->unk_18 = 1;
    state->unk_28 = 0;
    state->unk_1C = 0;
    return frame;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8_27f6d8", func_0027F790);
#ifdef NON_MATCHING
// Unmatched: field initialization scheduling differs.
s32 func_0027F7D0(Recovered_FrameState *state) {
    state->unk_24 = 1;
    state->unk_14 = D_003C0E04;
    state->unk_00[0] = 0;
    state->unk_00[1] = 0;
    state->unk_00[2] = 0;
    state->unk_00[3] = 0;
    state->unk_00[4] = 0;
    state->unk_18 = 1;
    state->unk_28 = 0;
    state->unk_20 = 0;
    state->unk_1C = D_0040EBAC;
    return 1;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8_27f6d8", func_0027F7D0);
