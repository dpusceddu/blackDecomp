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
extern f32 func_00281198(void*);
extern s32 func_00327F20(s32, s32, s32, s32, s32);
void AudioVoice_Initialize(Recovered_AudioVoice*, void*, s32, s32, void*, void*, s32) __asm__("func_002835C8");
void AudioVoice_Initialize(Recovered_AudioVoice* self, void* unused1, s32 driver, s32 alternate, void* unused4,
                           void* unused5, s32 kind) {
    s32 operation;
    s32 handle;
    func_00281198(self);
    M2C_FIELD(self, u8*, 0x32) = kind;
    M2C_FIELD(self, u8*, 0x34) = 0;
    M2C_FIELD(&operation, s32*, 0) = (alternate == 0) ? 0x15 : 0x16;
    handle = func_00327F20(driver, (s32)&operation, 0, 0, 0);
    M2C_FIELD(self, s32*, 0x38) = handle;
    M2C_FIELD(self, u8*, 0x35) = 0;
}
