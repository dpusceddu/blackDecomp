#include "include_asm.h"

#include "game/weapons/manager_methods.hpp"

namespace ModWeapons {

BkModWeaponCatalogRowPS2 *WeaponManagerMethods::Row(int id)
{
    return BkModWeaponCatalogAtPS2((BkModWeaponCatalogOwnerPS2*)this,id);
}
BkModWeaponDefinitionPS2 *WeaponManagerMethods::PrimaryDefinition(int id)
{
    return BkModWeaponCatalogIndexedPS2((BkModWeaponCatalogOwnerPS2*)this,id)->definition;
}
int WeaponManagerMethods::Word10(int id)
{
    return BkModWeaponCatalogIndexedPS2((BkModWeaponCatalogOwnerPS2*)this,id)->word10;
}
int WeaponManagerMethods::Word14(int id)
{
    return BkModWeaponCatalogIndexedPS2((BkModWeaponCatalogOwnerPS2*)this,id)->word14;
}
int WeaponManagerMethods::Word18(int id)
{
    return BkModWeaponCatalogIndexedPS2((BkModWeaponCatalogOwnerPS2*)this,id)->word18;
}
}

