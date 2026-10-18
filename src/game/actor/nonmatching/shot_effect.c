// Unmatched: 0x1ac0e0: cached vector construction and mixed scalar/vector call ABI.
#ifdef NONMATCHING
#include "game/actor/vector_math.h"
extern char *func_00135550(void *);
extern int func_0018C408(void *,const char *);
extern int D_004158F0,D_00415910;extern BkVectorPS2 D_004158E0,D_00415900;extern void *D_0040F4D0;
extern void func_0012C428(void *,BkVectorPS2,BkVectorPS2,int,float,float,int,int,int,int,int);
static inline BkVectorPS2 make(float x,float y,float z) {BkVectorPS2 tmp,result;__asm__("pextlw tmpv, zv, xv":"=r tmpv"(tmp):"r zv"(z),"r xv"(x));__asm__("pextlw resv, yv, tv":"=r resv"(result):"r yv"(y),"r tv"(tmp));return result;}
void func_001AC0E0(int event,void **context) {
 BkVectorPS2 offset,point,row0,row1,row2,row3;char *actor,*movement;
 if(!D_004158F0){D_004158E0=make(0.0f,0.8f,-0.25f);D_004158F0=1;}
 if(!D_00415910){D_00415900=make(0.0f,0.8f,0.25f);D_00415910=1;}
 actor=*context;movement=func_00135550(actor);offset=D_004158E0;
 if(movement && M2C_FIELD(func_00135550(actor),int *,0x80)==1 && func_0018C408(func_00135550(actor)+0x1da0,"SH_AR_I_082"))offset=D_00415900;
 actor=*context;row0=*(BkVectorPS2 *)(actor+0x70);row1=*(BkVectorPS2 *)(actor+0x80);row2=*(BkVectorPS2 *)(actor+0x90);row3=*(BkVectorPS2 *)(actor+0xa0);
 __asm__("vmulax.xyz ACC, r0v, offvx\n\tvmadday.xyz ACC, r1v, offvy\n\tvmaddaz.xyz ACC, r2v, offvz\n\tvmaddw.xyz pv, r3v, vf0w":"=j pv"(point):"j r0v"(row0),"j r1v"(row1),"j r2v"(row2),"j r3v"(row3),"j offv"(offset));
 func_0012C428(D_0040F4D0,point,*(BkVectorPS2 *)(actor+0x90),0,1.5f,150.0f,13,0,0,1,0);
}

#endif
