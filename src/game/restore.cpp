#include "game/camera/vitals.hpp"
#include "game/math/scalar.hpp"
namespace ModCamera {
struct Settings { unsigned char unknown00[0x2014c]; int difficulty; };
struct Hud {unsigned char unknown00[0x30];void*health;};
struct ServiceWorld {unsigned char unknown00[0xcbd8];Hud*hud;};
extern "C" {
extern Settings *D_0040F0E0;extern ServiceWorld *D_0040F510;extern void*D_0040F51C;extern int D_0040F544;
extern char D_003F49D8[];float func_0029E688(float,float);float func_00383890(void*);
void func_001EED98(float,void*,int);int func_001F2A60(void*,int,int,int,int);
int func_0021A7E0(const char*,int,int,int,...);int func_0024F7D0(int,...);
const char D_003F49C8[]="ReloadHealth";
}
static inline float Normalized(PlayerVitals *player){
 switch(D_0040F0E0->difficulty){
 case 0:return player->health/1200.0f;case 1:return player->health/1200.0f;
 case 2:case 3:return player->health/750.0f;
 default:return 0.0f;
 }
}
static inline bool Full(PlayerVitals *player){return func_00383890(player)>=0.999f;}
static inline void SetNormalized(PlayerVitals *player,float value){
 switch(D_0040F0E0->difficulty){
 case 0:player->health=value*1200.0f;break;case 1:player->health=value*1200.0f;break;
 case 2:case 3:player->health=value*750.0f;break;
 }
}
void PlayerVitals::Restore(int kind){
 float value=func_0029E688(Normalized(this),2.0f);
 switch(kind){
 case 0:
  if(Full(this))return;
  if(medkitCount==0)return;
  value+=0.5f;
  if(value>=1.0f)value=1.0f;else value=ModMath::SquareRoot(value);
  SetNormalized(this,value);
  func_001EED98(0.0f,D_0040F510->hud->health,6);
  func_0021A7E0(D_003F49C8,0,D_0040F544+0x38c9,0);
  {int count=--medkitCount;int event=D_0040F544+0x38c9;func_0021A7E0(D_003F49D8,0,event,1,func_0024F7D0(count));}
  break;
 case 1:
  value+=0.25f;
  if(value>=1.0f)value=1.0f;else value=ModMath::SquareRoot(value);
  SetNormalized(this,value);
  func_001F2A60(D_0040F51C,0x12,1,0,1);
  break;
 }
}
int PlayerVitals::AddMedkit(){
 if(medkitCount==3){func_001F2A60(D_0040F51C,0x35,0,0,1);return 0;}
 signed char count=(medkitCount=(unsigned char)medkitCount+1);
 int event=D_0040F544+0x38c9;
 func_0021A7E0(D_003F49D8,0,event,1,func_0024F7D0(count,this));
 if(!func_001F2A60(D_0040F51C,0xD,1,0,1))func_001F2A60(D_0040F51C,0x13,1,0,1);
 return 1;
}
}
