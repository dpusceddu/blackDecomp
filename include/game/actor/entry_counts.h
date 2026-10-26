#ifndef GAME_ACTOR_ENTRY_COUNTS_H
#define GAME_ACTOR_ENTRY_COUNTS_H

#include "ps2/prelude.h"

/* Partial views: class identities, remaining fields and total extents are UNVERIFIED. */
typedef struct Recovered_ActorCountSourceEntry {
    u8 unk_00[0xCE];
    u8 count;
    u8 unk_CF;
} Recovered_ActorCountSourceEntry;

typedef struct Recovered_ActorCountSource {
    u8 unk_00[0x48];
    Recovered_ActorCountSourceEntry *entries;
} Recovered_ActorCountSource;

typedef struct Recovered_ActorCountEntry {
    u8 unk_00[8];
    u8 count;
    u8 unk_09[3];
} Recovered_ActorCountEntry;

typedef struct Recovered_ActorCountView {
    u8 unk_000[0x118];
    Recovered_ActorCountSource *source;
    u8 unk_11C[0x84];
    Recovered_ActorCountEntry *entries;
    u8 unk_1A4[0x52];
    u8 entryCount;
} Recovered_ActorCountView;

#endif
