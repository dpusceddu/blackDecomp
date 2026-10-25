#ifndef BLACK_WEAPON_MANAGER_METHODS_HPP
#define BLACK_WEAPON_MANAGER_METHODS_HPP
#include "game/weapons/inventory_methods.hpp"
#include "game/weapons/catalog.h"
namespace Weapons {
// Descriptive native methods over the canonical PS2 pool; original names unknown.
struct WeaponManagerMethods : InventoryManager {
    void BindInstances(Weapon*,EeU64);
    void ReleaseInstance(Instance*);
    BkWeaponDefinitionPS2 *Definition(EeS8,int);
    int Valid(EeS8);
    void QueueDelayed(float,float,Instance*,int,Vec,Vec,EeS8);
    BkWeaponCatalogRowPS2 *Row(int);
    BkWeaponDefinitionPS2 *PrimaryDefinition(int);
    int Word10(int); int Word14(int); int Word18(int);
};
}
#endif
