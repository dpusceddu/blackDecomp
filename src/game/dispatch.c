#include "game/effects/pool.h"
extern int func_001B7A70(BkEffectPoolPS2 *,void *,void *,int);
void func_001B7968(BkEffectPoolPS2 *pool,void *transform,u32 index) {
 BkEffectResourcePS2 *resource=pool->resource;
 if(index<resource->effectCount) {
  void *effect=resource->effects[index];
  if(effect)func_001B7A70(pool,effect,transform,1);
 }
}
