#ifndef BLACK_EFFECTS_RANDOM_H
#define BLACK_EFFECTS_RANDOM_H
#include "auto/prelude.h"
extern u32 D_00418590[2];
static inline f32 BkEffectRandomPS2(void) {
 u32 value=D_00418590[0];
 value=(value<<16)+((s32)value>>16)+D_00418590[1];
 D_00418590[1]+=value;D_00418590[0]=value;
 return (f32)value*2.3283064e-10f;
}
#endif
