#include "game/effects/slot.h"
extern void func_001B3D18(BkEffectSlotPS2 *);
void func_001B37C8(BkEffectSlotPS2 *slots,u16 index) {
 BkEffectSlotPS2 *slot=slots+index;BkEffectSlottedObjectPS2 *object=slot->object;
 BkEffectSlotCallbackPS2 *callback=&object->callbacks->release;
 callback->call((char *)object+callback->adjustment,slot->mode);
 func_001B3D18(slot);
}
