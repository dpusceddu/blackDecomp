/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_INVENTORY_H
#define RECOVERED_INVENTORY_H
#include "ps2/prelude.h"

typedef struct Recovered_Inventory {
    u8 opaque_0[28];
    void * field_1C; /* PS2 +0x1C */
    void * field_20; /* PS2 +0x20 */
    void * field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    u8 opaque_2C[12];
    s32 field_38; /* PS2 +0x38 */
    u32 field_3C; /* PS2 +0x3C */
    u8 opaque_40[2];
    s8 field_42; /* PS2 +0x42 */
    s8 field_43; /* PS2 +0x43 */
    u8 opaque_44[1];
    u8 field_45; /* PS2 +0x45 */
    u8 field_46; /* PS2 +0x46 */
} Recovered_Inventory;
typedef char assert_Recovered_Inventory_1C[(((int)&((Recovered_Inventory *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_Inventory_20[(((int)&((Recovered_Inventory *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Inventory_24[(((int)&((Recovered_Inventory *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_Inventory_28[(((int)&((Recovered_Inventory *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_Inventory_38[(((int)&((Recovered_Inventory *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_Inventory_3C[(((int)&((Recovered_Inventory *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_Inventory_42[(((int)&((Recovered_Inventory *)0)->field_42) == 66) ? 1 : -1];
typedef char assert_Recovered_Inventory_43[(((int)&((Recovered_Inventory *)0)->field_43) == 67) ? 1 : -1];
typedef char assert_Recovered_Inventory_45[(((int)&((Recovered_Inventory *)0)->field_45) == 69) ? 1 : -1];
typedef char assert_Recovered_Inventory_46[(((int)&((Recovered_Inventory *)0)->field_46) == 70) ? 1 : -1];
#endif
