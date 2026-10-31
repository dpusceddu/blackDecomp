#ifndef GAME_FRONTEND_OPTIONS_H
#define GAME_FRONTEND_OPTIONS_H
#include "game/audio_runtime.h"

/* Native frontend command registration identifies these options. These are
 * partial access views, not complete original classes; all unaccessed storage,
 * original identities and full extents remain UNVERIFIED.
 * Matched option consumers confirm invert-look, crouch and both volume fields.
 * The vibration field remains UNVERIFIED until its draft consumer matches. */
/* The matched runtime update addresses both gains through this common
 * subobject. Original setting names, units, unaccessed storage and full extents
 * remain UNVERIFIED. */
typedef struct {
    u8 unk_00[0x1C];
    f32 unk_1C, unk_20;
} Recovered_AudioMixPreferences;

typedef struct {
    u8 unk_00[0x20120];
    Recovered_AudioMixPreferences audioMix;
    u8 unk_20144[0x18];
    f32 sfxVolume;
    f32 musicVolume;
    u8 unk_20164;
    u8 toggleCrouch;
    u8 unk_20166;
    u8 invertLook;
    u8 vibration;
} Recovered_FrontendPreferences;

typedef struct {
    u8 unk_00[0x611];
    u8 invertLook;
    u8 toggleCrouch;
} Recovered_InputPreferences;

typedef struct {
    u8 unk_00[0x77C];
    u8 vibration;
} Recovered_VibrationControl;

typedef char FrontendSfxVolumeOffset[(u32) & ((Recovered_FrontendPreferences*)0)->sfxVolume == 0x2015C ? 1 : -1];
typedef char FrontendCrouchOffset[(u32) & ((Recovered_FrontendPreferences*)0)->toggleCrouch == 0x20165 ? 1 : -1];
typedef char FrontendInvertOffset[(u32) & ((Recovered_FrontendPreferences*)0)->invertLook == 0x20167 ? 1 : -1];
typedef char FrontendVibrationOffset[(u32) & ((Recovered_FrontendPreferences*)0)->vibration == 0x20168 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
extern Recovered_FrontendPreferences* FrontendOptions_Preferences __asm__("D_0040F0E0");
extern Recovered_InputPreferences* FrontendOptions_Input __asm__("D_0040F4D0");
extern Recovered_VibrationControl* FrontendOptions_Vibration __asm__("D_0040F0E8");
void FrontendOptions_SetSfxVolume(const char* value);
void FrontendOptions_SetMusicVolume(const char* value);
void FrontendOptions_SetInvertLook(const char* value);
void FrontendOptions_SetToggleCrouch(const char* value);
void FrontendOptions_SetVibration(const char* value);
#ifdef __cplusplus
}
#endif
#endif
