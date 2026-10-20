#include "campaign/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" { extern const char D_003F6B60[];extern const char D_003F6B70[];extern const char D_003F6B78[];extern const char D_003F6B88[];extern const char D_003F6B80[];extern const char D_003F6900[];extern const char D_003F6B90[];extern const char D_003F6B68[];extern const char D_003F6BE8[];extern const char D_003F6BF0[];extern const char D_003F6BA8[];extern const char D_003F6BB0[];extern const char D_003F6BB8[];extern const char D_003F6BC0[];extern const char D_003F6BC8[];extern const char D_003F6BD0[];extern const char D_003F6BD8[];extern const char D_003F6BE0[];extern const char D_003F6E10[];extern const char D_003F6E18[];extern const char D_0040D9E8[];extern const char D_0040D9E0[];extern const char D_0040D9D8[];extern const char D_0040D9D0[]; extern const char *D_003BCFF0[],*D_003BD0B0[],*D_003BCFC0[]; }
// Unmatched: branch layout, floating-point lifetimes and original helper expansion.
void Selector::Sector(char* name,Actor* actor,long action,float angle) {
func_00135550(actor);
 if(angle<0.0f) {float magnitude=-angle;angle=-(magnitude-(float)(int)(magnitude/360.0f)*360.0f);}
 else angle-= (float)(int)(angle/360.0f)*360.0f;
 if(angle< -180.0f)angle+=360.0f;else if(angle>180.0f)angle-=360.0f;
 char suffix[12]; *(unsigned short*)suffix=0x5f53; suffix[2]=0;
 if(action==31)func_0035C7A4(suffix,D_003BD14C);
 else if(action==32)func_0035C7A4(suffix,D_003BD150);
 else if(action==33){func_0035C7A4(suffix,D_003F6E10);Emit(name,actor->AnimationPrefix(),D_003BD140,suffix,actor);return;}
 else if(action==34){func_0035C7A4(suffix,D_003F6E18);Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),suffix,actor);return;}
 else return;
 if(angle>=-45.0f && angle<45.0f)func_0035C7A4(suffix,D_0040D9D0);
 else if(angle>=45.0f && angle<135.0f)func_0035C7A4(suffix,D_0040D9D8);
 else if(angle>=-135.0f && angle< -45.0f)func_0035C7A4(suffix,D_0040D9E0);
 else func_0035C7A4(suffix,D_0040D9E8);
 Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),suffix,actor);
}
