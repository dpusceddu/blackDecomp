#include "include_asm.h"

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

#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
// Unmatched: branch layout and preserved receiver lifetimes.
void PrefixedSelector::Alternate(char* name,Actor* actor,long alternate,int state) {
switch(state) {
 case 1: Emit(name,D_003BD190,prefix,"S_180",actor);break;
 case 2: EmitFallback(name,D_003BD190,prefix,"S_502","S_181",actor);break;
 case 3: Emit(name,D_003BD190,prefix,"S_182",actor);break;
 default: if(alternate)EmitFallback(name,D_003BD190,prefix,"S_501","S_101",actor);else Emit(name,D_003BD190,prefix,D_003F7118,actor);break;
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/graphics_selector_1ad510", func_001AD610);
#endif
