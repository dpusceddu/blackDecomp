#include "include_asm.h"

#include "game/weapons/manager_methods.hpp"

namespace Weapons {

BkWeaponCatalogRowPS2 *WeaponManagerMethods::Row(int id)
{
    return BkWeaponCatalogAtPS2((BkWeaponCatalogOwnerPS2*)this,id);
}
BkWeaponDefinitionPS2 *WeaponManagerMethods::PrimaryDefinition(int id)
{
    return BkWeaponCatalogIndexedPS2((BkWeaponCatalogOwnerPS2*)this,id)->definition;
}
int WeaponManagerMethods::Word10(int id)
{
    return BkWeaponCatalogIndexedPS2((BkWeaponCatalogOwnerPS2*)this,id)->word10;
}
int WeaponManagerMethods::Word14(int id)
{
    return BkWeaponCatalogIndexedPS2((BkWeaponCatalogOwnerPS2*)this,id)->word14;
}
int WeaponManagerMethods::Word18(int id)
{
    return BkWeaponCatalogIndexedPS2((BkWeaponCatalogOwnerPS2*)this,id)->word18;
}
}

