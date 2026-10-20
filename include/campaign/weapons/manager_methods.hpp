#ifndef BLACK_CAMPAIGN_WEAPON_MANAGER_METHODS_HPP
#define BLACK_CAMPAIGN_WEAPON_MANAGER_METHODS_HPP
#include "mod/weapons/inventory_methods.hpp"
#include "mod/weapons/catalog.h"
namespace ModWeapons {
// Descriptive native methods over the canonical PS2 pool; original names unknown.
struct WeaponManagerMethods : InventoryManager {
    void BindInstances(Weapon*,EeU64);
    void ReleaseInstance(Instance*);
    BkModWeaponDefinitionPS2 *Definition(EeS8,int);
    int Valid(EeS8);
    void QueueDelayed(float,float,Instance*,int,Vec,Vec,EeS8);
    BkModWeaponCatalogRowPS2 *Row(int);
    BkModWeaponDefinitionPS2 *PrimaryDefinition(int);
    int Word10(int); int Word14(int); int Word18(int);
};
}
#endif
