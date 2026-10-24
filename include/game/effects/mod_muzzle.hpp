#ifndef BLACK_MOD_MUZZLE_METHODS_HPP
#define BLACK_MOD_MUZZLE_METHODS_HPP
#include "game/effects/runtime.hpp"
namespace ModEffects {
// Named PS2 access methods; original class identity and allocation extent are unverified.
class MuzzleMethods : public Muzzle {
public:
 void InitializeFields() __asm__("func_001BCC18");
 int Reset() __asm__("func_001BCDD8");
 int IsActive() __asm__("func_001BD610");
 void InitializeVertices() __asm__("func_001BCC30");
 void Advance() __asm__("func_001BCDF8");
 void Draw() __asm__("func_001BCF50");
 void Start(MuzzleResource *) __asm__("func_001BD508");
};
}
#endif
