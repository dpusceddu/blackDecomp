// Unmatched: random-state return register allocation.
#ifdef NONMATCHING
#include "game/effects/random.h"
typedef struct { u8 unknown[0x4c];f32 rotationRange;u8 fixedRotation; } BkEffectRotationConfigPS2;
typedef struct { u8 unknown[0x10]; BkEffectRotationConfigPS2 *config; } BkEffectRotationResourcePS2;
typedef struct { u8 unknown[0xc0]; f32 rotation; BkEffectRotationResourcePS2 *resource;u8 unknownc8;u8 phase; } BkEffectRotationPS2;
void func_001BCDF8(BkEffectRotationPS2 *effect) {
 if((s8)effect->phase<3) {
  if(!effect->resource->config->fixedRotation) {
   effect->rotation=effect->resource->config->rotationRange*BkEffectRandomPS2();
   if(BkEffectRandomPS2()<0.5f)effect->rotation=-effect->rotation;
  }
  effect->phase++;
 }
}

#endif // NONMATCHING
