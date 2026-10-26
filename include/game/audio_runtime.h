#ifndef GAME_AUDIO_RUNTIME_H
#define GAME_AUDIO_RUNTIME_H
#include "ps2/prelude.h"
#include "game/resource_pool.hpp"

/* Partial driver view. Only the mode word is confirmed by the game-side
 * accessor; all unaccessed storage, total extents and original type identity
 * are UNVERIFIED. */
typedef struct {
    u8 unk_00[0x6A4];
    s32 mode;
} Recovered_AudioDriverState;

/* The object-exact music setter confirms its gain/mixer access fields.
 * Gain-interface method records are native signed-this adjustments followed by
 * a callback. Original interface identities, unaccessed storage and full extents
 * remain UNVERIFIED. */
typedef struct {
    s16 thisAdjustment;
    u16 unk_02;
    void (*function)(void* self, f32 gain);
} Recovered_AudioGainMethod;

typedef struct {
    u8 unk_00[0x30];
    Recovered_AudioGainMethod setGain;
} Recovered_AudioGainVtable;

typedef struct {
    u8 unk_00[0x2C];
    const Recovered_AudioGainVtable* vtable;
} Recovered_AudioGainTarget;

/* UNVERIFIED: these state and stage interfaces are accessed by pending runtime
 * update/control drafts. Native method records establish the signed adjustment
 * and callback ABI, but original interface identities and slot meanings remain unknown. */
typedef struct {
    s16 thisAdjustment;
    u16 unk_02;
    void (*function)(void* self, s32 state);
} Recovered_AudioStateMethod;
typedef struct {
    u8 unk_00[0x30];
    Recovered_AudioStateMethod setState;
} Recovered_AudioStateVtable;
typedef struct {
    u8 unk_00[0x50];
    const Recovered_AudioStateVtable* vtable;
} Recovered_AudioStateTarget;
typedef struct {
    u8 unk_00[0x10];
    Recovered_AudioStateTarget* target;
} Recovered_AudioStateLink;
typedef struct {
    s16 thisAdjustment;
    u16 unk_02;
    void (*function)(void* self);
} Recovered_AudioStageMethod;
typedef struct {
    u8 unk_00[0x20];
    Recovered_AudioStageMethod unk_20;
    Recovered_AudioStageMethod unk_28;
} Recovered_AudioRuntimeVtable;

typedef struct {
    u8 unk_00[0x2C];
    Recovered_AudioStateLink* stateLink;
    u32 unk_30;
    void* music;
    void* frontendSink;
    Recovered_AudioGainTarget* gainTarget;
    void* unk_40;
} Recovered_AudioMixer;

/* Partial runtime tail shared by initialization and mode selection. The
 * unaccessed storage (including unk_CBB0), total extents and
 * configuration-field semantics remain UNVERIFIED. New bank/stage/component
 * accesses at B308/CBA0/CBD4/CBDC/CBE0 await matched update/control consumers. */
typedef struct {
    u8 unk_00[0xB308];
    Recovered_FloatPairBank pairBank;
    u8 unk_CACC[0xD1];
    u8 unk_CB9D;
    u8 unk_CB9E[2];
    const Recovered_AudioRuntimeVtable* vtable;
    u32 unk_CBA4;
    Recovered_AudioDriverState* driver;
    s32 mode;
    u32 unk_CBB0;
    u8 initialized;
    u8 unk_CBB5[3];
    s32 unk_CBB8;
    u8 unk_CBBC[8];
    // Music and SFX gain fields are confirmed by the matched setters.
    f32 sfxMixGain;
    f32 unk_CBC8; // UNVERIFIED: gain input used by the update draft.
    f32 sfxGain;
    f32 musicGain;
    void* unk_CBD4;
    Recovered_AudioMixer* mixer;
    void* unk_CBDC;
    void* unk_CBE0;
} Recovered_AudioRuntime;

typedef struct {
    s32 operation;
    s32 unk_04;
    s32 enabled;
    s32 unk_0C, unk_10, unk_14;
} Recovered_AudioSetupCommand;

typedef char AudioRuntimeBankOffset[(u32) & ((Recovered_AudioRuntime*)0)->pairBank == 0xB308 ? 1 : -1];
typedef char AudioRuntimeVtableOffset[(u32) & ((Recovered_AudioRuntime*)0)->vtable == 0xCBA0 ? 1 : -1];
typedef char AudioRuntimeStreamOffset[(u32) & ((Recovered_AudioRuntime*)0)->unk_CBE0 == 0xCBE0 ? 1 : -1];
typedef char AudioStateTargetVtableOffset[(u32) & ((Recovered_AudioStateTarget*)0)->vtable == 0x50 ? 1 : -1];
typedef char AudioRuntimeDriverOffset[(u32)&((Recovered_AudioRuntime*)0)->driver == 0xCBA8 ? 1 : -1];
typedef char AudioRuntimeInitializedOffset[(u32)&((Recovered_AudioRuntime*)0)->initialized == 0xCBB4 ? 1 : -1];
typedef char AudioRuntimeSfxGainOffset[(u32) & ((Recovered_AudioRuntime*)0)->sfxGain == 0xCBCC ? 1 : -1];
typedef char AudioRuntimeMusicGainOffset[(u32) & ((Recovered_AudioRuntime*)0)->musicGain == 0xCBD0 ? 1 : -1];
typedef char AudioRuntimeMixerOffset[(u32) & ((Recovered_AudioRuntime*)0)->mixer == 0xCBD8 ? 1 : -1];
typedef char AudioGainVtableOffset[(u32) & ((Recovered_AudioGainTarget*)0)->vtable == 0x2C ? 1 : -1];
typedef char AudioGainMethodOffset[(u32) & ((Recovered_AudioGainVtable*)0)->setGain == 0x30 ? 1 : -1];
typedef char AudioSetupCommandSize[sizeof(Recovered_AudioSetupCommand) == 24 ? 1 : -1];

/* Partial voice view. The initializer confirms byte accesses and the driver
 * handle word; unaccessed storage, original identity and total extents are
 * UNVERIFIED. */
typedef struct {
    u8 unk_00[0x32];
    u8 kind, unk_33, unk_34, unk_35;
    u16 unk_36;
    s32 handle;
} Recovered_AudioVoice;
typedef char AudioVoiceHandleOffset[(u32)&((Recovered_AudioVoice*)0)->handle == 0x38 ? 1 : -1];

void AudioVoice_Initialize(Recovered_AudioVoice* self, void* unused1, s32 driver, s32 alternate,
                           void* unused4, void* unused5, s32 kind);
void AudioRuntime_Configure(Recovered_AudioRuntime* self, s32 firstValue, s32 secondValue, s32 thirdValue, void* bank);
void AudioRuntime_SetMode(Recovered_AudioRuntime* self, s32 mode);

#ifdef __cplusplus
extern "C" {
#endif
extern Recovered_AudioRuntime* AudioRuntime_Global __asm__("D_0040F510");
f32 AudioVolumeCurve(f32 volume) __asm__("func_001D5CD8");
void AudioRuntime_ApplySfxVolume(Recovered_AudioRuntime* self, f32 volume);
void AudioRuntime_ApplyMusicVolume(Recovered_AudioRuntime* self, f32 volume);
void AudioRuntime_Update(Recovered_AudioRuntime* self);
// UNVERIFIED: state semantics; the native call forwards the same integer to several components.
void AudioRuntime_SetControlState(Recovered_AudioRuntime* self, s32 state);
#ifdef __cplusplus
}
#endif
#endif
