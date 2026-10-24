/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BKMODWEAPONDEFINITIONPS2_H
#define RECOVERED_BKMODWEAPONDEFINITIONPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_BkModWeaponDefinitionPS2 {
    u8 opaque_0[100];
    s32 field_64; /* PS2 +0x64 */
    u8 opaque_68[40];
    s32 field_90; /* PS2 +0x90 */
    u8 opaque_94[4];
    s32 field_98; /* PS2 +0x98 */
} Recovered_BkModWeaponDefinitionPS2;
typedef char assert_Recovered_BkModWeaponDefinitionPS2_64[(((int)&((Recovered_BkModWeaponDefinitionPS2 *)0)->field_64) == 100) ? 1 : -1];
typedef char assert_Recovered_BkModWeaponDefinitionPS2_90[(((int)&((Recovered_BkModWeaponDefinitionPS2 *)0)->field_90) == 144) ? 1 : -1];
typedef char assert_Recovered_BkModWeaponDefinitionPS2_98[(((int)&((Recovered_BkModWeaponDefinitionPS2 *)0)->field_98) == 152) ? 1 : -1];
#endif
