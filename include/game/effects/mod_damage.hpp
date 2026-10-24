#ifndef BLACK_MOD_EFFECT_DAMAGE_METHODS_HPP
#define BLACK_MOD_EFFECT_DAMAGE_METHODS_HPP
#include "game/effects/damage_window.h"
namespace ModEffects {
// Descriptive methods over the PS2 timed-damage record view; original class unknown.
class DamageWindows : public BkModEffectDamageWindowsPS2 {
public:
    int Initialize() __asm__("func_001BE940");
    int Reset() __asm__("func_001BEB28");
    void Clear() __asm__("func_001BEB50");
    void Update() __asm__("func_001BE960");
};
}
#endif
