#include "include_asm.h"

#include "game/actor/volume_state.hpp"
namespace CampaignActor {
extern "C" {
void func_0026AA68(int);void func_0026A840(int);
void func_001AE5E8(void*,const Matrix4*,PositionArg,PositionArg,PositionArg);
extern char*D_0040F4C0;extern Position4 D_00414CE0;
}

void CrossingVolume::Debug(){
 func_0026AA68(0);func_0026A840(0);
 func_001AE5E8(D_0040F4C0,&world,Load(lower),Load(upper),Load(D_00414CE0));
}
}
// Unmatched: 0x164268 VU yaw/inverse temporary context and two-byte loop shape.
// Unmatched: 0x164548 event-packet lifetimes, boolean normalization and vector readback allocation.
