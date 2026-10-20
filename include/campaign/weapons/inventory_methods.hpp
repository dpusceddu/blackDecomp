#ifndef BLACK_CAMPAIGN_WEAPON_INVENTORY_METHODS_HPP
#define BLACK_CAMPAIGN_WEAPON_INVENTORY_METHODS_HPP
#include "mod/weapons/moving.hpp"
#include "mod/weapons/inventory.h"
namespace ModWeapons {
/* Partial actor inventory access view. Fields not consumed by exact methods
   remain instruction leads; the original C++ class identity is unknown. */
struct Inventory : BkModInventoryPS2 {
 BkModWeaponOwnerPS2 *owner;
 Weapon **slots; Weapon *current, *next;
 float gain; EeU64 pendingIdentity; int phase; float timer;
 EeU16 pickupAmount; EeS8 slotCount, selectedSlot, pendingWeapon;
 EeU8 busy, request;
 void Switch(); int Select(); void Force(Weapon*); void Allocate(EeS8); void Clear();
 int Pickup(int); void FinishPickup(); int Remaining(); int Eligible(EeS8);
 void Update(int,int,int,int,int,int,int,Action*);
 static Weapon *Current();
};
struct CatalogEntry { EeU64 identity; EeU8 unknown08[0x14]; int kind; };
struct Catalog { EeU8 unknown00, count; EeU8 unknown02[2]; CatalogEntry *entries; };
struct InventoryManager : MovingPool {
 void Allocate(); int Reset(); void Tick(); void Load(Catalog*); void ClearCatalog();
 Weapon *Create(BkModWeaponOwnerPS2*,EeS8); void Release(Weapon*);
};
typedef char InventoryOwner1c[(unsigned)&((Inventory*)0)->owner==0x1c?1:-1];
typedef char InventoryPhase38[(unsigned)&((Inventory*)0)->phase==0x38?1:-1];
typedef char InventorySlots42[(unsigned)&((Inventory*)0)->slotCount==0x42?1:-1];
}
#endif
