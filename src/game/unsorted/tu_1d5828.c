#include "include_asm.h"
#include "game/audio_runtime.h"

extern f32 func_0029E688(f32 base, f32 exponent);
extern void func_00384700(void* music, f32 gain);

extern s32 func_001EFBA0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5828);

s32 func_001D59C8(void) {
    func_001EFBA0();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D59E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5B78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5C28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5C30);
#ifdef NON_MATCHING
// Unmatched: shared constants retain an extra saved floating-point register across powf.
f32 AudioVolumeCurve(f32 volume) {
    f32 normalized = __ee_min_s(__ee_max_s(volume, 0.0f), 1.0f);
    f32 gain = func_0029E688(10.0f, normalized);
    gain = __ee_min_s(__ee_max_s(gain, 0.0f), 10.0f);
    return (gain / 10.0f) * normalized;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5CD8);
#endif
void AudioRuntime_ApplyMusicVolume(Recovered_AudioRuntime* self, f32 volume) {
    self->musicGain = AudioVolumeCurve(volume);
    func_00384700(self->mixer->music, self->musicGain);
    {
        Recovered_AudioGainTarget* target = self->mixer->gainTarget;
        target->vtable->setGain.function((u8*)target + target->vtable->setGain.thisAdjustment,
                                         __ee_max_s(self->musicGain, self->sfxGain));
    }
}
void AudioRuntime_ApplySfxVolume(Recovered_AudioRuntime* self, f32 volume) {
    self->sfxGain = AudioVolumeCurve(volume);
    {
        Recovered_AudioRuntime** runtimeSlot = &AudioRuntime_Global;
        (*runtimeSlot)->sfxMixGain = self->sfxGain;
    }
    {
        Recovered_AudioGainTarget* target = self->mixer->gainTarget;
        target->vtable->setGain.function((u8*)target + target->vtable->setGain.thisAdjustment,
                                         __ee_max_s(self->musicGain, self->sfxGain));
    }
}

#include "ps2/recovered_types.h"
extern void* D_003BD284;
extern void* D_003BD280;

s32 func_001D5E10(s32 arg0) {
    s32 temp_2;
    u32 temp_4;

    temp_2 = (s32) (D_003BD284 + 0xF) & ~0xF;
    temp_4 = temp_2 + arg0;
    D_003BD284 = (void *) temp_4;
    return ((u32) D_003BD280 < temp_4) ? 0 : temp_2;
}
