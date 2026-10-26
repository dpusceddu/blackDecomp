#ifndef GAME_AI_MOVEMENT_VIEWS_H
#define GAME_AI_MOVEMENT_VIEWS_H

#include "ps2/prelude.h"

/* Partial layouts. Class identities, extents and draft-only fields are UNVERIFIED. */

typedef struct Recovered_MovementChildTable {
    u8 unk_00[0x28];
    s16 unk_28;
    u16 unk_2A;
    void (*unk_2C)(void*);
    s16 unk_30;
    u16 unk_32;
    s32 (*unk_34)(void*);
} Recovered_MovementChildTable;

typedef struct Recovered_MovementChild {
    u8 unk_00[4];
    Recovered_MovementChildTable* table;
} Recovered_MovementChild;

typedef struct Recovered_MovementSelection {
    u8 unk_00[0xF0];
    Recovered_MovementChild* children[2];
    s32 unk_F8;
    u8 unk_FC[4];
    u32 unk_100;
} Recovered_MovementSelection;

typedef struct Recovered_MovementRequest {
    s32 unk_00;
    u8 unk_04[12];
    u8 data[1];
} Recovered_MovementRequest;

typedef struct Recovered_MovementObserver {
    void* unk_00;
    void* unk_04;
    u8 unk_08[12];
    void* unk_14;
    u8 unk_18;
} Recovered_MovementObserver;

typedef struct Recovered_MovementGoal {
    u32 unk_00;
    f32 x;
    f32 y;
    f32 z;
} Recovered_MovementGoal;

typedef struct Recovered_MovementControl {
    void* unk_00;
    void* unk_04;
    u8 unk_08[12];
    u8 unk_14;
    u8 unk_15;
    u8 unk_16[10];
    s128 unk_20;
} Recovered_MovementControl;

typedef union Recovered_MovementVector {
    s128 native;
    f32 lane[4];
} Recovered_MovementVector;

#endif
