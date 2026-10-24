/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BKMODINVENTORYPS2_H
#define RECOVERED_BKMODINVENTORYPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_BkModInventoryPS2 {
    u8 opaque_0[14];
    u16 field_E; /* PS2 +0xE */
    u8 opaque_10[4];
    u32 field_14; /* PS2 +0x14 */
    u8 field_18; /* PS2 +0x18 */
} Recovered_BkModInventoryPS2;
typedef char assert_Recovered_BkModInventoryPS2_E[(((int)&((Recovered_BkModInventoryPS2 *)0)->field_E) == 14) ? 1 : -1];
typedef char assert_Recovered_BkModInventoryPS2_14[(((int)&((Recovered_BkModInventoryPS2 *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_BkModInventoryPS2_18[(((int)&((Recovered_BkModInventoryPS2 *)0)->field_18) == 24) ? 1 : -1];
#endif
