#ifndef BLACK_MOD_WEAPON_SHOT_H
#define BLACK_MOD_WEAPON_SHOT_H
#include "ps2/ee_types.h"
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
#endif
