#include "include_asm.h"

#include "game/weapons/manager_methods.hpp"

namespace Weapons {

BkWeaponDefinitionPS2 *WeaponManagerMethods::Definition(EeS8 id,int alternate)
{
    if(!alternate)
        return BkWeaponCatalogIndexedPS2((BkWeaponCatalogOwnerPS2*)this,id)->definition;
    return BkWeaponCatalogIndexedPS2((BkWeaponCatalogOwnerPS2*)this,id)->definition->secondary;
}
}
