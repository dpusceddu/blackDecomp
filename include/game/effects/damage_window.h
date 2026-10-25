#ifndef BLACK_MOD_EFFECT_DAMAGE_WINDOW_H
#define BLACK_MOD_EFFECT_DAMAGE_WINDOW_H
#include "ps2/ee_types.h"
/* Source1BEB50 verifies32 rows/0x14 stride, zero stores at0/4/C/10 and
   float sentinel1e9 at8. Those stores alone do not prove semantic pointers
   or interval/damage meanings. Instruction-only1BE960: the effect pointer
   is checked at+60; actor bounds250/260 and rangeSquared28C are descriptive
   access leads.1BE960 calls player damage13C778. Original class unknown. */
typedef struct BkEffectDamageWindowPS2 {
    void *effect,*actor; float begin,end,damage;
} BkEffectDamageWindowPS2;
typedef struct BkEffectDamageWindowsPS2 { BkEffectDamageWindowPS2 records[32]; } BkEffectDamageWindowsPS2;
typedef char EffectDamageWindow14[sizeof(BkEffectDamageWindowPS2)==0x14?1:-1];
#endif
