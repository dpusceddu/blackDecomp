#ifndef GAME_SOUND_BANK_LOAD_H
#define GAME_SOUND_BANK_LOAD_H
#include "ps2/prelude.h"
#include "rw_audio/bank.h"

/* Accessed bank-load prefix; the complete class identity remains unknown. */
typedef struct {
    void* buffer;
    s32 capacity; // UNVERIFIED: only the unfinished shared loader reads this field.
    u8 unk_08[0x1026];
    u8 loaded;
    u8 unk_102F[9];
    RwaBank* bank;
    s32 state;
} Recovered_SoundBankLoad;

typedef struct {
    RwaStream* stream;
    u8 initialized;
} Recovered_SharedBankStream;

typedef char SoundBankLoadedOffset[(u32) & ((Recovered_SoundBankLoad*)0)->loaded == 0x102E ? 1 : -1];
typedef char SoundBankStateOffset[(u32) & ((Recovered_SoundBankLoad*)0)->state == 0x103C ? 1 : -1];
s32 SoundBankLoad_Initialize(Recovered_SoundBankLoad* self);
s32 SoundBankLoad_Poll(Recovered_SoundBankLoad* self, const char* name, u32 arg2, u32 arg3, u32 data, u32 dataSize,
                       void* context);
#endif
