#include "include_asm.h"
#include "game/frontend_options.h"

extern s32 func_0035E750(const char* value);
extern void func_001EF7B0(void* sink, s32 id);
// This caller retains an unused F13 argument; the matched producer consumes channel and F12.
extern void FrontendOptions_PreviewVibration(Recovered_VibrationControl* self, s32 channel, f32 amount,
                                             f32 unusedTail) __asm__("func_00107788");
extern s32 D_003BE7D8, D_003BE7DC, D_003BE7E0, D_003BE7E4, D_003BE7E8, D_003BE7EC;

extern s32 func_0020DF90();
extern M2C_UNK D_003FB238;
extern M2C_UNK D_003FB250;
extern M2C_UNK D_003FB268;
extern M2C_UNK D_003FB278;
extern M2C_UNK D_003FB288;
extern s32 func_0020E0C8();
extern M2C_UNK D_003FB1D8;
extern M2C_UNK D_003FB1F0;
extern M2C_UNK D_003FB208;
extern M2C_UNK D_003FB218;
extern M2C_UNK D_003FB228;

s32 func_002105F8(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FB238);
    func_0020DF90(arg0, (s32) &D_003FB250);
    func_0020DF90(arg0, (s32) &D_003FB268);
    func_0020DF90(arg0, (s32) &D_003FB278);
    func_0020DF90(arg0, (s32) &D_003FB288);
    func_0020E0C8(arg0, (s32) &D_003FB1D8);
    func_0020E0C8(arg0, (s32) &D_003FB1F0);
    func_0020E0C8(arg0, (s32) &D_003FB208);
    func_0020E0C8(arg0, (s32) &D_003FB218);
    func_0020E0C8(arg0, (s32) &D_003FB228);
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: preference reloads and gain forwarding differ.
void FrontendOptions_SetSfxVolume(const char* value) {
    void** frontendSinkSlot;
    D_003BE7E4 = func_0035E750(value);
    frontendSinkSlot = &AudioRuntime_Global->mixer->frontendSink;
    func_001EF7B0(*frontendSinkSlot, D_003BE7EC);
    FrontendOptions_Preferences->sfxVolume = (f32)D_003BE7E4 / 100.0f;
    AudioRuntime_ApplySfxVolume(AudioRuntime_Global, FrontendOptions_Preferences->sfxVolume);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2105f8", func_002106B8);
#endif
#ifdef NON_MATCHING
// Unmatched: preference reloads and gain forwarding differ.
void FrontendOptions_SetMusicVolume(const char* value) {
    void** frontendSinkSlot;
    D_003BE7E8 = func_0035E750(value);
    frontendSinkSlot = &AudioRuntime_Global->mixer->frontendSink;
    func_001EF7B0(*frontendSinkSlot, D_003BE7EC);
    FrontendOptions_Preferences->musicVolume = (f32)D_003BE7E8 / 100.0f;
    AudioRuntime_ApplyMusicVolume(AudioRuntime_Global, FrontendOptions_Preferences->musicVolume);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2105f8", func_00210748);
#endif
void FrontendOptions_SetInvertLook(const char* value) {
    void** frontendSinkSlot;
    s32 enabled = func_0035E750(value);
    D_003BE7D8 = enabled;
    enabled = enabled != 0;
    FrontendOptions_Input->invertLook = enabled;
    frontendSinkSlot = &AudioRuntime_Global->mixer->frontendSink;
    func_001EF7B0(*frontendSinkSlot, D_003BE7EC);
    FrontendOptions_Preferences->invertLook = enabled;
}
void FrontendOptions_SetToggleCrouch(const char* value) {
    void** frontendSinkSlot;
    s32 enabled = func_0035E750(value);
    D_003BE7DC = enabled;
    enabled = enabled != 0;
    FrontendOptions_Input->toggleCrouch = enabled;
    frontendSinkSlot = &AudioRuntime_Global->mixer->frontendSink;
    func_001EF7B0(*frontendSinkSlot, D_003BE7EC);
    FrontendOptions_Preferences->toggleCrouch = enabled;
}
#ifdef NON_MATCHING
// Unmatched: predicate lowering and conditional-flag lifetimes differ.
void FrontendOptions_SetVibration(const char* value) {
    s32 enable = 0;
    s32 disable = 0;
    s32 setting = func_0035E750(value);
    D_003BE7E0 = setting;
    if (setting == 1) enable = FrontendOptions_Preferences->vibration == 0;
    if (setting == 0) disable = FrontendOptions_Preferences->vibration != 0;
    func_001EF7B0(AudioRuntime_Global->mixer->frontendSink, D_003BE7EC);
    if (enable) {
        FrontendOptions_Preferences->vibration = 1;
        FrontendOptions_Vibration->vibration = 1;
        FrontendOptions_PreviewVibration(FrontendOptions_Vibration, 0, 0.5f, 0.0f);
    } else if (disable) {
        FrontendOptions_Preferences->vibration = 0;
        FrontendOptions_Vibration->vibration = 0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2105f8", func_002108C8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2105f8", func_002109E0);
