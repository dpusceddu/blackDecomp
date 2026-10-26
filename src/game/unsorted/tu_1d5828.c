#include "include_asm.h"
#include "game/frontend_options.h"

// These two native call sites forward A0 to matched no-op producers.
extern void func_001E8798_WithContext(void*) __asm__("func_001E8798");
extern void func_001D96F0_WithContext(void*) __asm__("func_001D96F0");
extern void func_001D7EE0(void*);
extern void func_002807B0(Recovered_AudioRuntime*, f32, f32, f32, f32, f32);
extern void func_00285C20(void*);
extern void func_001E8250(void*);
extern void func_00281948(Recovered_FloatPairBank*, s32);
// This native caller also forwards a state value unused by the matched producer.
extern void func_001D8D70_WithState(void*, s32) __asm__("func_001D8D70");

extern f32 func_0029E688(f32 base, f32 exponent);
extern void func_00384700(void* music, f32 gain);

extern s32 func_001EFBA0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5828);

s32 func_001D59C8(void) {
    func_001EFBA0();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D59E8);
void AudioRuntime_Update(Recovered_AudioRuntime* self) {
    func_001E8798_WithContext(self->mixer);
    func_001D7EE0(self->unk_CBD4);
    func_001D96F0_WithContext(self->unk_CBDC);
    {
        Recovered_AudioMixPreferences* settings = &FrontendOptions_Preferences->audioMix;
        func_002807B0(self, self->sfxMixGain, self->unk_CBC8, settings->unk_20, settings->unk_1C, 1.0f);
    }
    func_00285C20(self->unk_CBE0);
    self->vtable->unk_20.function((u8*)self + self->vtable->unk_20.thisAdjustment);
    self->vtable->unk_28.function((u8*)self + self->vtable->unk_28.thisAdjustment);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5C28);
void AudioRuntime_SetControlState(Recovered_AudioRuntime* self, s32 state) {
    if (state == 1) {
        if (self->mixer->unk_40) func_001E8250(self->mixer->unk_40);
    }
    func_00281948(&self->pairBank, state);
    {
        Recovered_AudioStateTarget* target = self->mixer->stateLink->target;
        if (target) target->vtable->setState.function((u8*)target + target->vtable->setState.thisAdjustment, state);
    }
    func_001D8D70_WithState(self->mixer->music, state);
}
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
