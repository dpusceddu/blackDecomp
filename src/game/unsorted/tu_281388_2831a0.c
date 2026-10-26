#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/audio_runtime.h"

#include "ps2/recovered_types.h"
extern s32 D_0040E14C;
extern s32 func_00312EE0(void *, s32);
extern s32 func_003130A0();
extern s32 func_003250D8();
extern s32 func_0031B530(s32, void *);
extern s32 func_002832A0(void *, void *, void *, void *, void *);

s32 func_002831A0(void *arg0, void *arg1) {
    D_0040E14C = func_00312EE0(arg1, 1);
    func_003130A0();
    func_003250D8();
    func_0031B530((s32) func_002832A0, arg0);
    M2C_FIELD(arg0, s8 *, 0xCBB4) = 1;
    return 0x8000;
}

#ifdef NON_MATCHING
// Unmatched: size optimization merges the native distinct mode-update paths (29 differences).
void AudioRuntime_SetMode(Recovered_AudioRuntime* self, s32 mode) {
    switch (mode) {
        case 0:
            if (self->mode == 2) return;
            self->mode = 2;
            break;
        case 1:
            if (self->mode == 1) return;
            self->mode = 1;
            break;
        case 3:
            if (self->mode == 4) return;
            self->mode = 4;
            break;
    }
    self->driver->mode = self->mode;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2831a0", func_00283200);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2831a0", func_002832A0);
#ifdef NON_MATCHING
// Unmatched: operation selection remains a branch instead of native MOVZ (12 differences).
extern f32 func_00281198(void* self);
extern s32 func_00327F20(s32 driver, s32* operation, s32 arg2, s32 arg3, s32 arg4);
void AudioVoice_Initialize(Recovered_AudioVoice* self, void* unused1, s32 driver, s32 alternate,
                           void* unused4, void* unused5, s32 kind) {
    s32 operation;
    func_00281198(self);
    operation = alternate ? 0x16 : 0x15;
    self->kind = kind;
    self->unk_34 = 0;
    self->handle = func_00327F20(driver, &operation, 0, 0, 0);
    self->unk_35 = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2831a0", func_002835C8);
#endif
