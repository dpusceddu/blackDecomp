#ifndef BLACK_MOD_WEAPON_SHOT_H
#define BLACK_MOD_WEAPON_SHOT_H
#include "game/weapons/state.h"
/* 15D3D8 is an exact control only for active+88. The remaining offsets/0x90
   pool stride are PS2 instruction evidence (15D370/15D440/15CBA0), not verified
   C++ object identities. Hit/query payload semantics remain unverified here. */
typedef struct BkMovingShotPS2 {
    EeU8 query[0x40];
    EeS128 endpoint, origin, direction;
    void *weapon;
    float distance, remaining, speed;
    EeU8 flags80, unknown81[3];
    float launchTime;
    EeU8 active, flags89, flags8a, flags8b, flags8c, unknown8d[3];
} BkMovingShotPS2;
static inline void BkShotDeactivatePS2(BkMovingShotPS2 *shot) { shot->active=0; }
typedef char BkShotActive88[(unsigned)&((BkMovingShotPS2*)0)->active==0x88?1:-1];
typedef char BkShotStride90[sizeof(BkMovingShotPS2)==0x90?1:-1];
/* Delayed-hit prefix: existing source controls 1632E0/1632F8 verify these
   stores. 163328 reads the timer and runs the query/impact when it expires.
   Its complete query/impact helper signatures remain instruction leads. */
typedef struct BkDelayedShotPS2 {
    EeS128 point, direction;
    BkWeaponInstancePS2 *weapon;
    float remaining, distance;
    EeU8 active;
    EeS8 flags;
    EeU8 unknown2e[2];
} BkDelayedShotPS2;
typedef char BkDelayedActive2C[(unsigned)&((BkDelayedShotPS2*)0)->active==0x2c?1:-1];
typedef char BkDelayedStride30[sizeof(BkDelayedShotPS2)==0x30?1:-1];
#endif
