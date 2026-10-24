#include "include_asm.h"

#include "game/actor/state.hpp"
namespace CampaignActor {
extern "C" {
extern unsigned char *D_0040F4BC;extern char *D_0040F4D0;extern void*D_0040F51C;
long func_001A6840(void*,int,int);void func_001354E0(void*,void*);void func_00156E90(void*);void func_001A6330(void*,Request*);void func_001F2838(void*,int,int);
}

void Controller::Update(){
 switch(State()) {
 case 1: Active()=Aim();break;
 case 2: if(Target())Follow(Target());break;
 case 3:
  if(!Entered()) {Entered()=1;func_00156E90(OwnerRef()->Action());if(Player())func_001F2838(D_0040F51C,0,5);}
  else if(func_001A6840(OwnerRef()->Animation(),0,0))func_001354E0(D_0040F4D0+0x30,D_0040F4D0+0x520);
  break;
 case 4:
  if(D_0040F4BC[0x1678])break;
  if(!Entered()) {Entered()=1;Request r;r.kind=6;r.first=0;r.second=0;r.flag=0;func_001A6330(OwnerRef()->Animation(),&r);if(Player())func_001F2838(D_0040F51C,0,5);}
  else if(func_001A6840(OwnerRef()->Animation(),0,0))func_001354E0(D_0040F4D0+0x30,D_0040F4D0+0x520);
  break;
 }
 Finish();
}
}
