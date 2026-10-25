#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_00414D54;
extern s32 func_001AAF10();
extern s32 func_00137AE0();
extern M2C_UNK D_003F6A88;
extern M2C_UNK D_0040D9C8;


#ifdef NON_MATCHING
// Unmatched: 0x1a8a20: VU0 temporaries and normalized-angle stack layout.
#include "game/actor/vector_math.h"
extern char *func_00135550(void *);
extern char *func_00137AE0(char *);
extern char *func_001AB1C0(void *,char *,char *,char *,const char *,char *);
extern float func_0029E0D8(float);
extern BkVectorPS2 D_004432C0;
extern char D_003F6A40;
char *func_001A8A20(void *selector,char *name,char *actor) {
 char *movement=func_00135550(actor);
 BkVectorPS2 desired=*(BkVectorPS2 *)(movement+0x60),forward=*(BkVectorPS2 *)(actor+0x90);
 int state=M2C_FIELD(actor,int *,0x39c),locked=state==41||state==40;
 float angle; BkVectorPS2 normalDesired,normalForward;
 if((u8)(BkSumPS2(BkMultiplyPS2(desired,desired))<2.3283064365386963e-10f) || (u8)(BkSumPS2(BkMultiplyPS2(forward,forward))<2.3283064365386963e-10f) || locked)
  return func_001AB1C0(selector,name,actor+0x3b9,func_00137AE0(actor),&D_003F6A40,actor);
 normalForward=BkNormalizePS2(forward); normalDesired=BkNormalizePS2(desired);
 angle=func_0029E0D8(BkClampedDotPS2(normalForward,normalDesired))*57.295780181884766f;
 if(BkSumPS2(BkMultiplyPS2(BkCrossPS2(normalForward,normalDesired),D_004432C0))>0.0f)angle=-angle;
 if(angle>135.0f || angle< -135.0f)return func_001AB1C0(selector,name,actor+0x3b9,func_00137AE0(actor),"S_093",actor);
 if(angle< -45.0f)return func_001AB1C0(selector,name,actor+0x3b9,func_00137AE0(actor),"S_094",actor);
 if(angle>45.0f)return func_001AB1C0(selector,name,actor+0x3b9,func_00137AE0(actor),"S_095",actor);
 return func_001AB1C0(selector,name,actor+0x3b9,func_00137AE0(actor),"S_092",actor);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1a83a0", func_001A8A20);
#endif


void func_001A8E30(s8 *arg0, s32 arg1, s32 arg2) {
    s32 var_3;
    s8 temp_3;

    temp_3 = *arg0;
    if (temp_3 == -1) {
        var_3 = 0;
    } else {
        var_3 = M2C_FIELD(((temp_3 * 4) + D_00414D54), s32 *, 0);
    }
    if (var_3 == 0xA) {
        func_001AAF10(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6A88, &D_0040D9C8, arg2);
        return;
    }
    func_001AAF10(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), "U_SHO", &D_003F6A88, arg2);
}
