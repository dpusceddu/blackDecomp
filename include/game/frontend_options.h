#ifndef GAME_FRONTEND_OPTIONS_H
#define GAME_FRONTEND_OPTIONS_H
#include "game/audio_runtime.h"

/* Native frontend command registration identifies these options. These are
 * partial access views, not complete original classes; all unaccessed storage,
 * original identities and full extents remain UNVERIFIED.
 * UNVERIFIED: named frontend/input/vibration access fields await matched option
 * consumers; their command names come from the native registration. */
typedef struct {
    u8 unk_00[0x2015C];
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
