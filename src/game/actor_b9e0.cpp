#include "game/actor/volume_state.hpp"
namespace CampaignActor {
extern "C" {
void func_00165AA8(void*);
void func_0026AA68(int);void func_0026A840(int);
void func_001AE5E8(void*,const Matrix4*,PositionArg,PositionArg,PositionArg);
extern char *D_0040F4C0;extern Position4 D_00414D00;
}
void OnceVolume::SignalOnce(long message){
 if(!fired){func_00165AA8(this);Signal(message);fired=1;result=1;}
}
void OnceVolume::Debug(){
 func_0026AA68(0);func_0026A840(0);
 func_001AE5E8(D_0040F4C0,&world,Load(lower),Load(upper),Load(D_00414D00));
}
}
// Unmatched: 0x165430 VU yaw polynomial and rigid-inverse temporary copies.
// Unmatched: 0x1656F0 byte-bool normalization and VU register lifetimes.
