#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" {
extern const char D_003F7180[8] __attribute__((aligned(8)))="S_175";
}

void PrefixedSelector::Final(char* name,Actor* actor) {
if(CheckBC(actor)) EmitFallback(name,D_003BD190,prefix,D_003F7180,D_003F6E30,actor); else Emit(name,D_003BD190,prefix,D_003F6E30,actor);
}
