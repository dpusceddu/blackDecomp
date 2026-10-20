#ifndef BLACK_MOD_EFFECT_DAMAGE_WINDOW_H
#define BLACK_MOD_EFFECT_DAMAGE_WINDOW_H
#include "ps2/ee_types.h"
/* Instruction-only1BE960/1BEB50:32 timed entries,0x14 stride. The effect pointer
   is checked at+60; actor bounds250/260 and rangeSquared28C are descriptive
   access leads.1BE960 calls player damage13C778. No exact source control yet. */
typedef struct BkModEffectDamageWindowPS2 {
    void *effect,*actor; float begin,end,damage;
} BkModEffectDamageWindowPS2;
typedef struct BkModEffectDamageWindowsPS2 { BkModEffectDamageWindowPS2 records[32]; } BkModEffectDamageWindowsPS2;
typedef char EffectDamageWindow14[sizeof(BkModEffectDamageWindowPS2)==0x14?1:-1];
#endif
