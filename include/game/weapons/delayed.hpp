#ifndef BLACK_WEAPONS_DELAYED_HPP
#define BLACK_WEAPONS_DELAYED_HPP
#include "game/weapons/moving.hpp"
namespace Weapons {
// Methods over the verified storage prefix; original class name unknown.
struct DelayedShotMethods : BkDelayedShotPS2 {
    // A2 is unused, before the two 128-bit vector arguments.
    void Initialize(float,float,Instance*,int,Vec,Vec,EeS8) __asm__("func_001632F8");
    void Update(float);
};
}
#endif
