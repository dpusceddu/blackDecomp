#ifndef BLACK_MOD_WEAPON_CATALOG_H
#define BLACK_MOD_WEAPON_CATALOG_H
#include "game/weapons/state.h"
/* Storage access view, not an assertion of historical C++ class identity.
   Exact15D210/228/288/2A8/2C8 prove rows4, signed8 indices,0x20 stride,
   definition8 and words10/14/18. Count1 is still instruction-only15D2E8. */
typedef struct BkModWeaponCatalogRowPS2 {
    EeU64 identity;
    BkModWeaponDefinitionPS2 *definition;
    EeU32 unknown0c;
    EeS32 word10,word14,word18,kind;
} BkModWeaponCatalogRowPS2;
typedef struct BkModWeaponCatalogPS2 {
    EeU8 unknown00,count,unknown02[2]; BkModWeaponCatalogRowPS2 *rows;
} BkModWeaponCatalogPS2;
typedef struct BkModWeaponCatalogOwnerPS2 { BkModWeaponCatalogPS2 *catalog; } BkModWeaponCatalogOwnerPS2;
static inline BkModWeaponCatalogRowPS2 *BkModWeaponCatalogAtPS2(BkModWeaponCatalogOwnerPS2 *owner,EeS32 id)
{ return owner->catalog->rows + (EeS8)id; }
/* Value-getter recipe keeps the signed byte offset on the left of addition. */
static inline BkModWeaponCatalogRowPS2 *BkModWeaponCatalogIndexedPS2(BkModWeaponCatalogOwnerPS2 *owner,EeS32 id)
{ return (BkModWeaponCatalogRowPS2 *)(((EeS32)(id<<24)>>19)+(EeS32)owner->catalog->rows); }
typedef char WeaponCatalogRow20[sizeof(BkModWeaponCatalogRowPS2)==0x20?1:-1];
typedef char WeaponCatalogDefinition8[(unsigned)&((BkModWeaponCatalogRowPS2*)0)->definition==8?1:-1];
#endif
