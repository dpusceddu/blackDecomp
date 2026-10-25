#ifndef BLACK_MOD_WEAPON_INVENTORY_H
#define BLACK_MOD_WEAPON_INVENTORY_H
#include "ps2/ee_types.h"
/* Accessed PS2 prefix, not a recovered original class or allocation size.
   Matched functions verify reserve[7], entries+14 and signed count+18.
   The ten-element extent also follows the PS2 reset loop. Actor embedding+280
   is instruction evidence only; the Xbox counterpart embeds this at+278. */
typedef struct BkInventoryPS2 {
    EeU16 reserve[10];
    void *entries;
    EeS8 count;
} BkInventoryPS2;
static inline EeU16 BkInventorySlotPS2(const BkInventoryPS2 *inventory, int index)
{
    return inventory->reserve[index];
}
typedef char BkInventoryEntries14[(unsigned)&((BkInventoryPS2*)0)->entries==0x14?1:-1];
typedef char BkInventoryCount18[(unsigned)&((BkInventoryPS2*)0)->count==0x18?1:-1];
/* ReserveReturn 1551C8 narrows addition to u16 BEFORE comparing against the
   table maximum. Its implementation is still a matching task. */
#endif
