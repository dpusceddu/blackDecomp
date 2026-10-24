#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
// Unmatched: branch layout and preserved receiver lifetimes.
void Selector::Move(char* name,Actor* actor) {
Movement* movement=func_00135550(actor);
 if(__builtin_fabsf(movement->At<float>(12))>0.1f && !(unsigned char)actor->HasLayer())
  Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6A20,actor);
}
