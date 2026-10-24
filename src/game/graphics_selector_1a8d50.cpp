#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
// Unmatched: branch layout and preserved receiver lifetimes.
void Selector::MoveAlternate(char* name,Actor* actor,long alternate) {
if(!actor->HasLayer()) { if(!alternate)EmitFallback(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6A80,D_0040D9C8,actor);else EmitFallback(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6A78,D_0040D9C8,actor); }
}
