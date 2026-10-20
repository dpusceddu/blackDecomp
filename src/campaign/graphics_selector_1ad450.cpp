#include "campaign/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" {
extern const char D_003F70C0[8] __attribute__((aligned(8)))="S_110";
extern const char D_003F70C8[8] __attribute__((aligned(8)))="S_170";
extern const char D_003F70D0[8] __attribute__((aligned(8)))="S_114";
extern const char D_003F70D8[8] __attribute__((aligned(8)))="S_130";
extern const char D_003F70E0[8] __attribute__((aligned(8)))="S_176";
}

void PrefixedSelector::State(char* name,Actor* actor,int state,long alternate) {
if(state==0) Emit(name,D_003BD190,prefix,D_003F70C0,actor);
 else if(state==1) { if(!alternate)Emit(name,D_003BD190,prefix,D_003F6A88,actor);else Emit(name,D_003BD190,prefix,D_003F70C8,actor); }
 else if(state==2)Emit(name,D_003BD190,prefix,D_003F70D0,actor);
 else if(state==3) {if(!alternate)Emit(name,D_003BD190,prefix,D_003F70D8,actor);else Emit(name,D_003BD190,prefix,D_003F70E0,actor);}
}
