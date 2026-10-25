#ifndef BLACK_MOD_WEAPON_CATALOG_H
#define BLACK_MOD_WEAPON_CATALOG_H
#include "game/weapons/state.h"
/* Storage access view, not an assertion of historical C++ class identity.
   Exact15D210/228/288/2A8/2C8 prove rows4, signed8 indices,0x20 stride,
   definition8 and words10/14/18. Count1 is still instruction-only15D2E8. */
typedef struct BkWeaponCatalogRowPS2 {
    EeU64 identity;
    BkWeaponDefinitionPS2 *definition;
    EeU32 unknown0c;
    EeS32 word10,word14,word18,kind;
} BkWeaponCatalogRowPS2;
typedef struct BkWeaponCatalogPS2 {
    EeU8 unknown00,count,unknown02[2]; BkWeaponCatalogRowPS2 *rows;
} BkWeaponCatalogPS2;
typedef struct BkWeaponCatalogOwnerPS2 { BkWeaponCatalogPS2 *catalog; } BkWeaponCatalogOwnerPS2;
static inline BkWeaponCatalogRowPS2 *BkWeaponCatalogAtPS2(BkWeaponCatalogOwnerPS2 *owner,EeS32 id)
{ return owner->catalog->rows + (EeS8)id; }
/* Value-getter recipe keeps the signed byte offset on the left of addition. */
static inline BkWeaponCatalogRowPS2 *BkWeaponCatalogIndexedPS2(BkWeaponCatalogOwnerPS2 *owner,EeS32 id)
{ return (BkWeaponCatalogRowPS2 *)(((EeS32)(id<<24)>>19)+(EeS32)owner->catalog->rows); }
typedef char WeaponCatalogRow20[sizeof(BkWeaponCatalogRowPS2)==0x20?1:-1];
typedef char WeaponCatalogDefinition8[(unsigned)&((BkWeaponCatalogRowPS2*)0)->definition==8?1:-1];
#endif
