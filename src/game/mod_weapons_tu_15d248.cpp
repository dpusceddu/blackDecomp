#include "game/weapons/manager_methods.hpp"

namespace ModWeapons {
BkModWeaponDefinitionPS2 *WeaponManagerMethods::Definition(EeS8 id,int alternate)
{
    if(!alternate)
        return BkModWeaponCatalogIndexedPS2((BkModWeaponCatalogOwnerPS2*)this,id)->definition;
    return BkModWeaponCatalogIndexedPS2((BkModWeaponCatalogOwnerPS2*)this,id)->definition->secondary;
}
}
