#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
// Unmatched: branch merging and preserved selector/movement lifetimes.
void Selector::Stand(char* name,Actor* actor,long action) {
Movement* movement=func_00135550(actor);
 if(action==40) { Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),"S_005",actor); return; }
 if(!movement) { Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6A00,actor);return; }
 int mode=movement->At<int>(0x80);
 if(mode==1 && *(int*)(actor->At<char*>(0x330)+0xcc)) {func_0035CBC0(name);return;}
 int family=familyIndex==-1?0:D_00414D54[familyIndex];
 const char* suffix;
 if(movement->At<unsigned char>(0x30)) suffix=D_003F69F8;
 else if(movement->At<unsigned char>(0x35)) {
  if(family==10) { if(movement->At<float>(12)>=-10.0f) {Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),"S_001",actor);return;} suffix=D_003F6A08; }
  else if(movement->At<unsigned char>(0x3a)||(mode==1 && func_0018DDD8((char*)movement+0xc94))) {Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),"S_001",actor);return;}
  else suffix=D_003F6A10;
 } else if(movement->At<unsigned char>(0x3a)) {Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),"S_001",actor);return;}
 else if(mode==1 && func_0018DDD8((char*)movement+0xc94)) suffix=D_003F6A18;
 else suffix=D_003F6A10;
 EmitFallback(name,actor->AnimationPrefix(),func_00137AE0(actor),suffix,D_003F6A00,actor);
}
