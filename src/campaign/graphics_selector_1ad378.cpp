#include "campaign/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" {
extern const char D_003F70A8[8] __attribute__((aligned(8)))="S_131";
extern const char D_003F70B0[8] __attribute__((aligned(8)))="S_172";
extern const char D_003F70B8[8] __attribute__((aligned(8)))="S_050";
}

void PrefixedSelector::Stand(char* name,Actor* actor) {
if(CheckBF(actor)) Emit(name,D_003BD190,prefix,D_003F70A8,actor);
 else if(CheckBC(actor)) EmitFallback(name,D_003BD190,prefix,D_003F70B0,D_003F70B8,actor);
 else Emit(name,D_003BD190,prefix,D_003F70B8,actor);
}
