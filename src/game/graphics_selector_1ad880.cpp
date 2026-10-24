#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
void PrefixedSelector::Secondary(char* name,Actor* actor) {
if(CheckBC(actor)) EmitFallback(name,D_003BD190,prefix,D_003F7120,D_003F7128,actor); else Emit(name,D_003BD190,prefix,D_003F7128,actor);
}
