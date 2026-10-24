#include "include_asm.h"

#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" {
extern const char D_003F7140[8] __attribute__((aligned(8)))="S_178";
}

void PrefixedSelector::Tertiary(char* name,Actor* actor) {
if(CheckBC(actor)) EmitFallback(name,D_003BD190,prefix,D_003F7140,D_003F6DF8,actor); else Emit(name,D_003BD190,prefix,D_003F6DF8,actor);
}
