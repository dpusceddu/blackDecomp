#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
#include "ps2/prelude.h"
#include "game/actor/vector_math.h"
typedef struct {char bytes[12];} BkAnimationName12PS2;
extern float D_003BD154;extern int D_004158D8[2];extern const char D_003F68E0[],D_003F68E8[],D_003F68B8[];extern const char *D_003BD080[],*D_003BD020[],*D_003BD050[];
// Unmatched: VU0 lifetimes, branch layout and original inline expansion remain unresolved.
void Selector::Action(char* name,Actor* actor,int action) {

 Movement* movement=func_00135550(actor);char* motion=(char*)movement+0xa0;int backwards,state,crouching,choice;const char *suffix;float speed;unsigned int random;
 backwards=SumWord(BlackGame::Mul3(*(BkVectorPS2 *)(motion+0x10),M2C_FIELD((char*)movement,char **,0x7c)?*(BkVectorPS2 *)(M2C_FIELD((char*)movement,char **,0x7c)+0xf0):0))<0.0f;
 state=M2C_FIELD((char*)actor,int *,0x39c);crouching=M2C_FIELD((char*)actor,u8 *,0x3aa);
 if(state==38 && func_00360838("SK_DF_S_490",M2C_FIELD((char*)actor,char **,0x330)+0x5c)==0){crouching=1;M2C_FIELD((char*)func_00135550(actor),u8 *,0x30)=1;func_00135578(actor,1);}
 choice=M2C_FIELD(func_0015D248(D_0040F4E0,func_00136B30(D_0040F4D0+0x30),0),int *,0x94)==2;
 if(!choice) {
  speed=M2C_FIELD(motion,float *,0x24);
  if(speed<D_003BD154)choice=1;
  else if(speed<D_003BD154+D_003BD154) {
   random=(D_004158D8[0]<<16)+(D_004158D8[0]>>16)+D_004158D8[1];D_004158D8[1]+=random;D_004158D8[0]=random;
   choice=0.5f<=((float)random*2.3283064365386963e-10f);
  }
 }
 switch(action) {
 case 2:suffix=backwards?"S_351":"S_350";break;
 case 3:suffix="S_356";break;
 case 11:suffix="S_322";break;
 case 4:suffix="S_377";break;
 case 5:case 8:suffix="S_377";break;
 case 6:suffix="S_471";break;
 case 7:suffix="S_476";break;
 case 9:suffix="S_330";break;
 case 10:
  if((unsigned)(M2C_FIELD(motion,int *,0x28)-7)<4)suffix=backwards?"S_345":"S_346";
  else suffix=backwards?"S_351":"S_350";
  break;
 case 1:
  if(state==40){suffix=backwards?(M2C_FIELD(motion,int *,0x28)?D_003F68E8:D_003F68E0):D_003F68B8;goto common;}
  if(choice && backwards){if(crouching)suffix="C_560";else {suffix=D_003BD080[M2C_FIELD(motion,int *,0x28)];goto common;}}
  else if(crouching)suffix="C_540";
  else {suffix=(backwards?D_003BD020:D_003BD050)[M2C_FIELD(motion,int *,0x28)];goto common;}
  break;
 default:*(BkAnimationName12PS2 *)name=*(const BkAnimationName12PS2 *)(crouching?"SH_AR_C_560":"SH_AR_S_560");return;
 }
 EmitFallback(name,(char*)actor+0x3b9,func_00137AE0(actor),suffix,D_003F68E0,actor);return;
common:EmitFallback(name,(char*)actor+0x3b9,D_003BD140,suffix,D_003F68E0,actor);

}
