#ifndef BLACK_CAMPAIGN_WEAPONS_DELAYED_HPP
#define BLACK_CAMPAIGN_WEAPONS_DELAYED_HPP
#include "mod/weapons/moving.hpp"
namespace ModWeapons {
// Native methods over the verified storage prefix; original class name unknown.
struct DelayedShotMethods : BkModDelayedShotPS2 {
    // A2 is unused, before the two 128-bit vector arguments.
    void Initialize(float,float,Instance*,int,Vec,Vec,EeS8) __asm__("func_001632F8");
    void Update(float);
};
}
#endif
