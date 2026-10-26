#ifndef GAME_AI_ACTION_VIEWS_H
#define GAME_AI_ACTION_VIEWS_H

#include "ps2/prelude.h"

/* Partial layouts. Class identities, extents and draft-only fields are UNVERIFIED. */

typedef struct Recovered_ActionTimerPair {
    f32 unk_00; /* UNVERIFIED: only the initializer draft uses this field. */
    f32 unk_04;
    f32 unk_08;
} Recovered_ActionTimerPair;

typedef struct Recovered_ActionState {
    void* owner;
    u8 unk_04[4];
    s32 unk_08;
    f32 unk_0c;
    f32 unk_10;
    f32 unk_14;
} Recovered_ActionState;

typedef struct Recovered_ActionMove {
    u8* owner;
    u8 unk_04[12];
    s128 position;
    u8 moving;
} Recovered_ActionMove;

typedef struct Recovered_ActionTimers {
    u8* owner;
    u8 unk_04[12];
    s128 unk_10;
    f32 unk_20;
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    void* unk_38;
    u8 unk_3C;
} Recovered_ActionTimers;

typedef struct Recovered_ActionPeer {
    u8* owner;
    u8 unk_04[4];
    void* unk_08;
} Recovered_ActionPeer;

typedef struct Recovered_AIAction {
    u8* owner;
    u8 unk_04[4];
    u8 unk_08;
} Recovered_AIAction;

#endif
