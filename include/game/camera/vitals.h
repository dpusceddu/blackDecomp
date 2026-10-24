#ifndef BLACK_MOD_PLAYER_VITALS_H
#define BLACK_MOD_PLAYER_VITALS_H
#include "ps2/ee_types.h"
/* Partial player access prefix; original class identity/allocation are unknown.
   Source13C9D8/13CD20 verify health2F8 and signed8 medkitCount8A1.
   Presentation32C,state38C and invulnerable8B2 remain instruction-only13C778. */
typedef struct BkModPlayerVitalsPS2 {
    EeU8 unknown00[0x2f8]; float health;
    EeU8 unknown2fc[0x30]; void *presentation;
    EeU8 unknown330[0x5c]; EeS32 state;
    EeU8 unknown390[0x511]; EeS8 medkitCount;
    EeU8 unknown8a2[0x10]; EeU8 invulnerable;
} BkModPlayerVitalsPS2;
typedef char PlayerHealth2F8[(unsigned)&((BkModPlayerVitalsPS2*)0)->health==0x2f8?1:-1];
typedef char PlayerMedkit8A1[(unsigned)&((BkModPlayerVitalsPS2*)0)->medkitCount==0x8a1?1:-1];
typedef char PlayerInvulnerable8B2[(unsigned)&((BkModPlayerVitalsPS2*)0)->invulnerable==0x8b2?1:-1];
#endif
