#ifndef GAME_AI_MOVEMENT_EVENTS_H
#define GAME_AI_MOVEMENT_EVENTS_H

#include "ps2/prelude.h"

/* Serialization prepends the event kind to a copy of the complete object.
 * The 24-byte and 8-byte variants retain their distinct payload sizes. */
typedef struct {
    s32 kind;
    u8 unk_04[20];
} Recovered_MovementEvent24;

typedef struct {
    s32 kind;
    s32 unk_04;
} Recovered_MovementEvent8;

typedef struct {
    s32 kind;
    Recovered_MovementEvent24 payload;
} Recovered_MovementEvent24Output;

typedef struct {
    s32 kind;
    Recovered_MovementEvent8 payload;
} Recovered_MovementEvent8Output;

typedef char MovementEvent24Size[sizeof(Recovered_MovementEvent24) == 24 ? 1 : -1];
typedef char MovementEvent8Size[sizeof(Recovered_MovementEvent8) == 8 ? 1 : -1];

#endif
