#ifndef GAME_AUDIO_RESOURCE_OWNER_H
#define GAME_AUDIO_RESOURCE_OWNER_H
#include "ps2/prelude.h"

/* Native access views confirmed by matched resource and playback consumers.
 * Original identities, unused storage and semantic field names remain UNVERIFIED. */
/* Partial resource owner; object and timestamp meanings are UNVERIFIED. */
typedef struct Recovered_ResourceEntry {
    void* resource;
    u32 unk_04;
    u32 stamp;
} Recovered_ResourceEntry;
typedef struct Recovered_ResourceOwner {
    u8 unk_00[0x5C];
    Recovered_ResourceEntry* entries;
    u32 count;
    u8 unk_64[0x1C];
    u32 stamp;
    u32 state;
    u8 unk_88[0x12C];
    void* playback;
} Recovered_ResourceOwner;

// Partial slot views; original identities and unused fields are UNVERIFIED.

typedef struct Recovered_ResourceSlot {
    void* resource;
    u8 unk_04[0xB];
    u8 active;
} Recovered_ResourceSlot;
typedef struct Recovered_ResourceSlots {
    u8 unk_00[0x20];
    Recovered_ResourceSlot slots[2];
} Recovered_ResourceSlots;

/* Partial controller access view; identities and unused storage are UNVERIFIED. */
typedef struct Recovered_PlaybackSlot {
    u8 unk_00[0x90];
    u8 active;
    u8 unk_91[0x39F];
} Recovered_PlaybackSlot;
typedef struct Recovered_PlaybackSlots {
    u8 unk_00[0x2A8];
    u64 key;
    u64 savedKey;
    u8 unk_2B8[8];
    Recovered_PlaybackSlot slots[6];
    void* current;
    void* saved;
    void* alternate;
    void* field1BEC;
    void* field1BF0;
    u8 unk_1BF4[0x34];
    f32 time;
    u8 unk_1C2C[0x18];
    u8 active;
    u8 savedActive;
    u8 unk_1C46[2];
    f32 gain;
} Recovered_PlaybackSlots;
typedef char PlaybackSlotsOffset[(u32) & ((Recovered_PlaybackSlots*)0)->slots == 0x2C0 ? 1 : -1];
typedef char PlaybackCurrentOffset[(u32) & ((Recovered_PlaybackSlots*)0)->current == 0x1BE0 ? 1 : -1];
typedef char PlaybackTimeOffset[(u32) & ((Recovered_PlaybackSlots*)0)->time == 0x1C28 ? 1 : -1];
typedef char PlaybackActiveOffset[(u32) & ((Recovered_PlaybackSlots*)0)->active == 0x1C44 ? 1 : -1];

typedef struct Recovered_AudioParameters {
    u8 unk_00[0x50];
    void* source;
    f32 gain;
    f32 rate;
    u8 unk_5C[4];
    u32 unk_60;
    u8 unk_64[0x24];
    f32 field88, field8C, field90, field94, field98, field9C;
    u32 unk_A0;
    u32 flags;
    u8 kind;
    u8 unk_A9[2];
    u8 fieldAB;
    u8 unk_AC[4];
} __attribute__((aligned(16))) Recovered_AudioParameters;
typedef char AudioParametersSize[sizeof(Recovered_AudioParameters) == 0xB0 ? 1 : -1];

typedef char ResourceEntrySize[sizeof(Recovered_ResourceEntry) == 12 ? 1 : -1];
typedef char ResourceOwnerEntriesOffset[(u32) & ((Recovered_ResourceOwner*)0)->entries == 0x5C ? 1 : -1];
typedef char ResourceOwnerPlaybackOffset[(u32) & ((Recovered_ResourceOwner*)0)->playback == 0x1B4 ? 1 : -1];
typedef char AudioParametersFlagsOffset[(u32) & ((Recovered_AudioParameters*)0)->flags == 0xA4 ? 1 : -1];
#endif
