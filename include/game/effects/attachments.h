#ifndef BLACK_MOD_EFFECT_ATTACHMENTS_H
#define BLACK_MOD_EFFECT_ATTACHMENTS_H
#include "ps2/ee_types.h"
/* Source1BEC68 verifies44records/0x130 stride, active124, childrenB0[8],
   zero word110. Entry Release1B1518 and the1BECD0 call chain identify
   resource110 through the embedded entry atB0. Matrix/motion/offset fields
   follow PS2 instructions1BECD0 only; original class identities remain unknown. */
typedef struct BkEffectChildrenPS2 {
    void *items[8]; EeU8 unknown20[0x40]; void *resource;
} BkEffectChildrenPS2;
typedef struct BkAttachedEffectPS2 {
    EeS128 world[4], local[4], origin, velocity;
    EeS128 localOffset;
    BkEffectChildrenPS2 children;
    EeU8 unknown114[0xc]; float lifetime; EeU8 active,compose,unknown126[0xa];
} BkAttachedEffectPS2;
typedef struct BkAttachedEffectsPS2 { BkAttachedEffectPS2 records[44]; } BkAttachedEffectsPS2;
typedef char AttachedEffectStride130[sizeof(BkAttachedEffectPS2)==0x130?1:-1];
typedef char AttachedEffectChildrenB0[(unsigned)&((BkAttachedEffectPS2*)0)->children==0xb0?1:-1];
typedef char AttachedEffectResource110[(unsigned)&((BkAttachedEffectPS2*)0)->children.resource==0x110?1:-1];
typedef char AttachedEffectActive124[(unsigned)&((BkAttachedEffectPS2*)0)->active==0x124?1:-1];
#endif
