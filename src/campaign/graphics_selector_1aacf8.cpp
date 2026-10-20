#include "campaign/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
// Unmatched: branch layout and preserved receiver lifetimes.
void Selector::Utility(char* name,Actor* actor,long alternate) {
char suffix[6];
 if(alternate)__builtin_strcpy(suffix,"U_112");else __builtin_strcpy(suffix,"U_113");
 Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),suffix,actor);
}
