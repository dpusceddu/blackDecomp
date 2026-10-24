#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" {
extern const char D_003F7138[8] __attribute__((aligned(8)))="S_174";
}

void PrefixedSelector::Primary(char* name,Actor* actor) {
if(CheckBC(actor)) EmitFallback(name,D_003BD190,prefix,D_003F7138,D_003F6DF0,actor); else Emit(name,D_003BD190,prefix,D_003F6DF0,actor);
}
