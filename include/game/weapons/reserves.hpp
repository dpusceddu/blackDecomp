#ifndef BLACK_WEAPON_RESERVES_HPP
#define BLACK_WEAPON_RESERVES_HPP
#include "game/weapons/inventory.h"
namespace Weapons {
/* View of the reserve prefix; no original class name is established. */
struct Reserves : BkInventoryPS2 {
    void Initialize();
    int Reset();
    void Return(int,EeU16);
    int AtMaximum(int);
};
}
#endif
