#ifndef BLACK_MOD_EFFECT_ATTACHMENTS_H
#define BLACK_MOD_EFFECT_ATTACHMENTS_H
#include "ps2/ee_types.h"
/* Source1BEC68 verifies44records/0x130 stride, active124, childrenB0[8],
   child count110. Source1BF720/1BFEA0 verifies pendingA8. Matrix/motion fields
   follow PS2 instructions1BECD0 only; original class identities remain unknown. */
typedef struct BkModEffectChildrenPS2 {
    void *items[8]; EeU8 unknown20[0x40]; EeS32 count;
} BkModEffectChildrenPS2;
typedef struct BkModAttachedEffectPS2 {
    EeS128 world[4], local[4], origin, velocity;
    EeU8 unknowna0[8]; EeS32 pending; EeU8 unknownac[4];
    BkModEffectChildrenPS2 children;
    EeU8 unknown114[0xc]; float lifetime; EeU8 active,compose,unknown126[0xa];
} BkModAttachedEffectPS2;
typedef struct BkModAttachedEffectsPS2 { BkModAttachedEffectPS2 records[44]; } BkModAttachedEffectsPS2;
typedef char AttachedEffectStride130[sizeof(BkModAttachedEffectPS2)==0x130?1:-1];
typedef char AttachedEffectChildrenB0[(unsigned)&((BkModAttachedEffectPS2*)0)->children==0xb0?1:-1];
typedef char AttachedEffectCount110[(unsigned)&((BkModAttachedEffectPS2*)0)->children.count==0x110?1:-1];
typedef char AttachedEffectActive124[(unsigned)&((BkModAttachedEffectPS2*)0)->active==0x124?1:-1];
#endif
