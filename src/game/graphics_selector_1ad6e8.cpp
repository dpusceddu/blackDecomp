#include "include_asm.h"

#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" {
extern const char D_003F7130[8] __attribute__((aligned(8)))="S_173";
}

void PrefixedSelector::Special(char* name,Actor* actor) {
if(actor->At<unsigned char>(0x8b3)) { if(CheckBC(actor))EmitFallback(name,D_003BD190,prefix,D_003F7120,D_003F7128,actor);else Emit(name,D_003BD190,prefix,D_003F7128,actor); }
 else if(CheckBC(actor))EmitFallback(name,D_003BD190,prefix,D_003F7130,D_003F6DE8,actor);else Emit(name,D_003BD190,prefix,D_003F6DE8,actor);
}
