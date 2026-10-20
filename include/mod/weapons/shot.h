#ifndef BLACK_MOD_WEAPON_SHOT_H
#define BLACK_MOD_WEAPON_SHOT_H
#include "mod/weapons/state.h"
/* 15D3D8 is an exact control only for active+88. The remaining offsets/0x90
   pool stride are PS2 instruction evidence (15D370/15D440/15CBA0), not verified
   C++ object identities. Hit/query payload semantics remain unverified here. */
typedef struct BkModMovingShotPS2 {
    EeU8 query[0x40];
    EeS128 endpoint, origin, direction;
    void *weapon;
    float distance, remaining, speed;
    EeU8 flags80, unknown81[3];
    float launchTime;
    EeU8 active, flags89, flags8a, flags8b, flags8c, unknown8d[3];
} BkModMovingShotPS2;
static inline void BkModShotDeactivatePS2(BkModMovingShotPS2 *shot) { shot->active=0; }
typedef char BkModShotActive88[(unsigned)&((BkModMovingShotPS2*)0)->active==0x88?1:-1];
typedef char BkModShotStride90[sizeof(BkModMovingShotPS2)==0x90?1:-1];
/* Delayed-hit prefix: existing source controls 1632E0/1632F8 verify these
   stores. 163328 reads the timer and runs the query/impact when it expires.
   Its complete query/impact helper signatures remain instruction leads. */
typedef struct BkModDelayedShotPS2 {
    EeS128 point, direction;
    BkModWeaponInstancePS2 *weapon;
    float remaining, distance;
    EeU8 active;
    EeS8 flags;
    EeU8 unknown2e[2];
} BkModDelayedShotPS2;
typedef char BkModDelayedActive2C[(unsigned)&((BkModDelayedShotPS2*)0)->active==0x2c?1:-1];
typedef char BkModDelayedStride30[sizeof(BkModDelayedShotPS2)==0x30?1:-1];
#endif
