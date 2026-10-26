#include "include_asm.h"
#include "game/audio_command_stream.h"

void func_00286220(s32 arg0, void *arg1, void *arg2, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5) {
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f14;
    f32 temp_f15;
    f32 temp_f16;
    f32 temp_f17;

    temp_f12 = fparg0 / fparg3;
    temp_f13 = fparg1 / fparg3;
    temp_f14 = fparg2 / fparg3;
    temp_f17 = fparg5 / fparg3;
    temp_f16 = fparg4 / fparg3;
    temp_f15 = fparg3 / fparg3;
    M2C_FIELD(arg1, f32 *, 0) = temp_f12;
    M2C_FIELD(arg1, f32 *, 4) = temp_f13;
    M2C_FIELD(arg1, f32 *, 8) = temp_f14;
    M2C_FIELD(arg1, f32 *, 0x14) = temp_f17;
    M2C_FIELD(arg1, f32 *, 0x10) = temp_f16;
    M2C_FIELD(arg1, f32 *, 0xC) = temp_f15;
    M2C_FIELD(arg2, f32 *, 0x14) = temp_f17;
    M2C_FIELD(arg2, f32 *, 0) = temp_f12;
    M2C_FIELD(arg2, f32 *, 4) = temp_f13;
    M2C_FIELD(arg2, f32 *, 8) = temp_f14;
    M2C_FIELD(arg2, f32 *, 0xC) = temp_f15;
    M2C_FIELD(arg2, f32 *, 0x10) = temp_f16;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_286220", func_00286278);
#ifdef NON_MATCHING
// Unmatched: saved-register allocation and payload/call scheduling differ.
void AudioCommandStream_SendPair(Recovered_AudioCommandStream* self, u32 first, u32 second) {
    u32* payload = AudioCommandStream_Append(self, 0x70, 2);

    payload[1] = second;
    payload[0] = first;
    AudioCommandStream_Submit(self, 1);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_286220", func_00286410);
#endif
#ifdef NON_MATCHING
extern void AudioCommandStream_Stop(Recovered_AudioCommandStream* self);

// Unmatched: pair-copy scheduling, wide-mode branch and call setup differ.
s32 AudioCommandStream_ApplyConfiguration(Recovered_AudioCommandStream* self,
                                          Recovered_AudioStreamConfiguration* configuration) {
    s32 previousState = self->state;

    self->firstValues[0] = configuration->pairs[0][0];
    self->secondValues[0] = configuration->pairs[0][1];
    self->firstValues[1] = configuration->pairs[1][0];
    self->secondValues[1] = configuration->pairs[1][1];
    self->firstValues[2] = configuration->pairs[2][0];
    self->secondValues[2] = configuration->pairs[2][1];
    self->firstValues[3] = configuration->pairs[3][0];
    self->secondValues[3] = configuration->pairs[3][1];
    self->firstValues[5] = configuration->pairs[4][0];
    self->secondValues[5] = configuration->pairs[4][1];
    self->firstValues[4] = configuration->pairs[5][0];
    self->secondValues[4] = configuration->pairs[5][1];
    if (previousState == 3) { AudioCommandStream_Stop(self); }
    self->state = 2;
    self->wide = configuration->wide;
    self->chunkSize = configuration->wide ? 0x800 : 0x400;
    AudioCommandStream_SetValues(self, configuration->firstValue, configuration->secondValue, configuration->thirdValue,
                                 configuration->wide);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_286220", func_00286468);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_286220", func_00286550);
