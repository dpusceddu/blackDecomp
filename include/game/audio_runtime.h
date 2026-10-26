#ifndef GAME_AUDIO_RUNTIME_H
#define GAME_AUDIO_RUNTIME_H
#include "ps2/prelude.h"

/* Partial driver view. Only the mode word is confirmed by the game-side
 * accessor; the unused prefix and original type identity are UNVERIFIED. */
typedef struct {
    u8 unk_00[0x6A4];
    s32 mode;
} Recovered_AudioDriverState;

/* Partial runtime tail shared by initialization and mode selection. The
 * unused prefixes and configuration-field semantics remain UNVERIFIED. */
typedef struct {
    u8 unk_00[0xCB9D];
    u8 unk_CB9D;
    u8 unk_CB9E[10];
    Recovered_AudioDriverState* driver;
    s32 mode;
    u32 unk_CBB0;
    u8 initialized;
    u8 unk_CBB5[3];
    s32 unk_CBB8;
} Recovered_AudioRuntime;

typedef struct {
    s32 operation;
    s32 unk_04;
    s32 enabled;
    s32 unk_0C, unk_10, unk_14;
} Recovered_AudioSetupCommand;

typedef char AudioRuntimeDriverOffset[(u32)&((Recovered_AudioRuntime*)0)->driver == 0xCBA8 ? 1 : -1];
typedef char AudioRuntimeInitializedOffset[(u32)&((Recovered_AudioRuntime*)0)->initialized == 0xCBB4 ? 1 : -1];
typedef char AudioSetupCommandSize[sizeof(Recovered_AudioSetupCommand) == 24 ? 1 : -1];

void AudioRuntime_Configure(Recovered_AudioRuntime* self, s32 firstValue, s32 secondValue, s32 thirdValue, void* bank);
void AudioRuntime_SetMode(Recovered_AudioRuntime* self, s32 mode);
#endif
