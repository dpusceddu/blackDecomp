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
