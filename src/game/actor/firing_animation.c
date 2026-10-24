#include "include_asm.h"

#include "ps2/prelude.h"
typedef struct { char bytes[12]; } BkAnimationName12PS2;
extern const BkAnimationName12PS2 D_003F6C00,D_003F6C10,D_003F6C20,D_003F6C30,D_003F6C40;

void func_001AA280(void *selector,BkAnimationName12PS2 *name,void *actor,int state,int alternate) {
 switch(state) {
 case 19:*name=D_003F6C00;break;
 case 21:*name=D_003F6C10;break;
 case 22:*name=D_003F6C20;break;
 case 20:if(alternate)*name=D_003F6C30;else *name=D_003F6C40;break;
 case 23:*name=*(const BkAnimationName12PS2 *)"SH_AR_S_425";break;
 case 24:*name=*(const BkAnimationName12PS2 *)"SH_AR_S_430";break;
 case 25:*name=*(const BkAnimationName12PS2 *)"SH_AR_S_470";break;
 case 26:*name=*(const BkAnimationName12PS2 *)"SH_AR_S_475";break;
 case 27:case 28:*name=*(const BkAnimationName12PS2 *)"SH_AR_S_330";break;
 }
}

void func_001AA490(void *selector,BkAnimationName12PS2 *name,void *actor,int state,int alternate) {
 switch(state) {
 case 37:*name=*(const BkAnimationName12PS2 *)"SH_AR_S_765";break;
 case 35:*name=D_003F6C00;break;
 case 36:*name=D_003F6C40;break;
 case 12:*name=*(const BkAnimationName12PS2 *)"SH_AR_S_355";break;
 case 13:*name=*(const BkAnimationName12PS2 *)"SH_AR_S_441";break;
 case 14:*name=*(const BkAnimationName12PS2 *)"SH_AR_S_442";break;
 case 15:if(alternate)*name=D_003F6C30;else *name=*(const BkAnimationName12PS2 *)"SH_AR_S_416";break;
 case 16:if(alternate)*name=*(const BkAnimationName12PS2 *)"SH_AR_S_411";else *name=*(const BkAnimationName12PS2 *)"SH_AR_S_417";break;
 case 17:if(alternate)*name=*(const BkAnimationName12PS2 *)"SH_AR_S_354";else *name=*(const BkAnimationName12PS2 *)"SH_AR_S_352";break;
 case 18:if(alternate)*name=*(const BkAnimationName12PS2 *)"SH_AR_S_383";else *name=*(const BkAnimationName12PS2 *)"SH_AR_S_373";break;
 }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AA768);
