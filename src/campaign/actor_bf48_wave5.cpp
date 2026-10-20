#include "campaign/actor/room_region.hpp"
namespace CampaignActor {
extern "C" {
void func_0026AA68(int);void func_0026A840(int);
void func_001AE5E8(void*,const Matrix4*,PositionArg,PositionArg,PositionArg);
extern char*D_0040F4C0;extern Position4 D_00414D10;
}
void RoomRegion::Debug(){
 func_0026AA68(0);func_0026A840(0);
 func_001AE5E8(D_0040F4C0,&world,Load(lower),Load(upper),Load(D_00414D10));
}
}
// Unmatched: 0x169F38 yaw/inverse helper temporaries and vector-bound readbacks.
// Unmatched: 0x16A250 predicate normalization and return-zero epilogue scheduling.
// Unmatched: 0x16A7C0 yaw/inverse helper temporaries and copy ordering.
// Unmatched: 0x16AA78 return-zero epilogue scheduling.
