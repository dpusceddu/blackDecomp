#include "game/effects/slot.h"
int func_001B3CF8(BkEffectSlotPS2 *slot,BkEffectSlottedObjectPS2 *object,u16 start,u16 count,u8 mode) {
 slot->object=object;
 slot->mode=mode;
 slot->active=1;
 slot->start=start;
 slot->count=count;
 return 1;
}
