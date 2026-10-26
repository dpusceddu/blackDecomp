#ifndef GAME_WEAPONS_TRACE_VIEWS_H
#define GAME_WEAPONS_TRACE_VIEWS_H

#include "ps2/prelude.h"

/* Partial layouts. Extents, names and fields used only by drafts are UNVERIFIED. */

typedef struct Recovered_WeaponAimCandidate {
    s128 point;
    f32 projection;
    f32 perpendicularSquared;
    void* actor;
} Recovered_WeaponAimCandidate;

typedef struct Recovered_WeaponAimResult {
    u8 unk_00[4];
    void* actor;
    u8 unk_08[0x18];
    s128 point;
    u8 unk_30[4];
    f32 projection;
    f32 perpendicularSquared;
    u8 changed;
} Recovered_WeaponAimResult;

typedef struct Recovered_WeaponHit {
    s128 point;
    s128 normal;
    f32 fraction;
    void* actor;
    u32 mask;
    u8 component;
    u8 unk_2D[3];
    s128 unk_30;
} Recovered_WeaponHit;

typedef struct Recovered_WeaponTrace {
    s128 start;
    s128 end;
    u32 flags;
    void* ignoredActor;
    u8 unk_28;
    u8 kind;
    u8 unk_2A[6];
    s128 hit[4];
} Recovered_WeaponTrace;

typedef struct Recovered_ShotClock {
    u8 unk_00[0x20];
    f32 time;
} Recovered_ShotClock;

#endif
