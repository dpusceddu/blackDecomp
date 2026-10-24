#include "include_asm.h"

#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" {
extern const char D_003F7168[8] __attribute__((aligned(8)))="S_112";
extern const char D_003F7170[8] __attribute__((aligned(8)))="S_113";
}

void PrefixedSelector::Utility(char* name,Actor* actor,long alternate) {
if(alternate) Emit(name,D_003BD190,prefix,D_003F7168,actor); else Emit(name,D_003BD190,prefix,D_003F7170,actor);
}
