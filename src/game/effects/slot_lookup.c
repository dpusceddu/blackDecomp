#include "include_asm.h"

#include "game/effects/slot.h"
extern BkEffectSlotTargetPS2 *func_001B1848(s128);
extern void func_001B3A10(BkEffectSlotPS2 *,BkEffectSlotTargetPS2 *);


BkEffectSlotPS2 *func_001B33B8(BkEffectSlotPS2 *slots,const s128 *key) {
 BkEffectSlotTargetPS2 *object=func_001B1848(*key);
 if(!object)return 0;
 if(object->slot==0xffff)func_001B3A10(slots,object);
 return slots+object->slot;
}

