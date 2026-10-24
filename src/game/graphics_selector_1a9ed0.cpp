#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
#include "ps2/prelude.h"
#include "game/actor/vector_math.h"
extern BkVectorPS2 D_004432C0,D_004432D0;extern const char *D_003BD0E0[],*D_003BD0F8[],*D_003BD110[],*D_003BD128[];
// Unmatched: VU0 lifetimes, branch layout and original inline expansion remain unresolved.
void Selector::Aim(char* name,Actor* actor) {

 Movement* movement=func_00135550(actor);BkVectorPS2 delta,normalDelta,forward;float angle,speed;int sector;const char **table;
 BkVectorPS2 target=*(BkVectorPS2 *)((char*)movement+0x1fb0),position=*(BkVectorPS2 *)((char*)actor+0xa0);
 __asm__("vsub.xyz deltav, targetv, posv":"=j deltav"(delta):"j targetv"(target),"j posv"(position));
 normalDelta=BkNormalizePS2(delta);forward=BkNormalizePS2(D_004432D0);speed=M2C_FIELD((char*)movement,float *,0x1fa0);
 angle=func_0029E0D8(BkClampedDotPS2(normalDelta,forward))*57.295780181884766f;
 if(SumWord(BlackGame::Mul3(BkCrossPS2(normalDelta,forward),D_004432C0))>0.0f)angle=-angle;
 angle-=M2C_FIELD((char*)movement,float *,0);
 if(angle<0.0f) {float magnitude=-angle;angle=-(magnitude-(float)(int)(magnitude/360.0f)*360.0f);}
 else angle=angle-(float)(int)(angle/360.0f)*360.0f;
 if(angle< -180.0f)angle+=360.0f;else if(angle>180.0f)angle-=360.0f;
 if(angle> -45.0f && angle<45.0f)sector=0;
 else if(angle>45.0f && angle<135.0f)sector=3;
 else {sector=1;if(angle> -135.0f && angle< -45.0f)sector=2;}
 if(speed>0.2f)table=M2C_FIELD((char*)movement,u8 *,0x30)?D_003BD0F8:D_003BD0E0;
 else table=M2C_FIELD((char*)movement,u8 *,0x30)?D_003BD128:D_003BD110;
 Emit(name,(char*)actor+0x3b9,D_003BD140,table[sector],actor);

}
