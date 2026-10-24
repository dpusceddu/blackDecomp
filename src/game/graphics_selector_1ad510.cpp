#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" {
extern const char D_003F70E8[8] __attribute__((aligned(8)))="S_191";
extern const char D_003F70F0[8] __attribute__((aligned(8)))="S_190";
extern const char D_003F70F8[8] __attribute__((aligned(8)))="S_171";
}

void PrefixedSelector::Transition(char* name,Actor* actor) {
if(CheckC1(actor)) { if(CheckBC(actor))EmitFallback(name,D_003BD190,prefix,D_003F70E8,D_003F70F0,actor);else Emit(name,D_003BD190,prefix,D_003F70F0,actor); }
 else if(CheckBC(actor))EmitFallback(name,D_003BD190,prefix,D_003F70F8,D_003F6A00,actor);else Emit(name,D_003BD190,prefix,D_003F6A00,actor);
}
