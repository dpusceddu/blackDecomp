/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BKMODWEAPONINSTANCEPS2_H
#define RECOVERED_BKMODWEAPONINSTANCEPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_BkModWeaponInstancePS2 {
    u8 opaque_0[12];
    void * field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    u8 opaque_14[12];
    s8 field_20; /* PS2 +0x20 */
} Recovered_BkModWeaponInstancePS2;
typedef char assert_Recovered_BkModWeaponInstancePS2_C[(((int)&((Recovered_BkModWeaponInstancePS2 *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_BkModWeaponInstancePS2_10[(((int)&((Recovered_BkModWeaponInstancePS2 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_BkModWeaponInstancePS2_20[(((int)&((Recovered_BkModWeaponInstancePS2 *)0)->field_20) == 32) ? 1 : -1];
#endif
