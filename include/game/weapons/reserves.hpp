#ifndef BLACK_CAMPAIGN_WEAPON_RESERVES_HPP
#define BLACK_CAMPAIGN_WEAPON_RESERVES_HPP
#include "game/weapons/inventory.h"
namespace ModWeapons {
/* Native view of the reserve prefix; no original class name is established. */
struct Reserves : BkModInventoryPS2 {
    void Initialize();
    int Reset();
    void Return(int,EeU16);
    int AtMaximum(int);
};
}
#endif
