/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_WEAPONMANAGERMETHODS_H
#define RECOVERED_WEAPONMANAGERMETHODS_H
#include "ps2/prelude.h"

typedef struct Recovered_WeaponManagerMethods {
    void * field_0; /* PS2 +0x0 */
    u8 opaque_4[8];
    s32 field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    u8 opaque_14[56];
    u8 field_4C; /* PS2 +0x4C */
    u8 opaque_4D[47];
    u8 field_7C; /* PS2 +0x7C */
    u8 opaque_7D[47];
    u8 field_AC; /* PS2 +0xAC */
    u8 opaque_AD[47];
    u8 field_DC; /* PS2 +0xDC */
    u8 opaque_DD[47];
    u8 field_10C; /* PS2 +0x10C */
    u8 opaque_10D[47];
    u8 field_13C; /* PS2 +0x13C */
    u8 opaque_13D[47];
    u8 field_16C; /* PS2 +0x16C */
    u8 opaque_16D[47];
    u8 field_19C; /* PS2 +0x19C */
} Recovered_WeaponManagerMethods;
typedef char assert_Recovered_WeaponManagerMethods_0[(((int)&((Recovered_WeaponManagerMethods *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_WeaponManagerMethods_C[(((int)&((Recovered_WeaponManagerMethods *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_WeaponManagerMethods_10[(((int)&((Recovered_WeaponManagerMethods *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_WeaponManagerMethods_4C[(((int)&((Recovered_WeaponManagerMethods *)0)->field_4C) == 76) ? 1 : -1];
typedef char assert_Recovered_WeaponManagerMethods_7C[(((int)&((Recovered_WeaponManagerMethods *)0)->field_7C) == 124) ? 1 : -1];
typedef char assert_Recovered_WeaponManagerMethods_AC[(((int)&((Recovered_WeaponManagerMethods *)0)->field_AC) == 172) ? 1 : -1];
typedef char assert_Recovered_WeaponManagerMethods_DC[(((int)&((Recovered_WeaponManagerMethods *)0)->field_DC) == 220) ? 1 : -1];
typedef char assert_Recovered_WeaponManagerMethods_10C[(((int)&((Recovered_WeaponManagerMethods *)0)->field_10C) == 268) ? 1 : -1];
typedef char assert_Recovered_WeaponManagerMethods_13C[(((int)&((Recovered_WeaponManagerMethods *)0)->field_13C) == 316) ? 1 : -1];
typedef char assert_Recovered_WeaponManagerMethods_16C[(((int)&((Recovered_WeaponManagerMethods *)0)->field_16C) == 364) ? 1 : -1];
typedef char assert_Recovered_WeaponManagerMethods_19C[(((int)&((Recovered_WeaponManagerMethods *)0)->field_19C) == 412) ? 1 : -1];
#endif
