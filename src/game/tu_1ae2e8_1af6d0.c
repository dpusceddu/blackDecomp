#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001AF1B8(void *);

s32 func_001AF6D0(s32 arg0) {
    s32 var_17;
    void *var_16;

    var_16 = arg0 + 0xCA58;
    var_17 = 6;
    do {
        var_17 -= 1;
        func_001AF1B8(var_16);
        var_16 = (void *) (((s8 *) var_16) + 0x18);
    } while (var_17 >= 0);
    M2C_FIELD(arg0, s32 *, 0xCBC8) = 0;
    return arg0 + 0x8000;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AF738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AF768);

#ifdef NON_MATCHING
// Unmatched: 0x1af798: identity-matrix and packet store scheduling; signed flag ABI partly recovered.
#include "game/actor/vector_math.h"
typedef struct {int a,b,c,d,e;} BkDrawBatchPS2;
extern char *D_0040F4C0;extern BkVectorPS2 *D_0040E5F0;
extern void func_0035C544(void *,void *,int);
extern void func_001C62F0(int,int,unsigned int,unsigned int,unsigned int,int,int);
static inline void identity(BkVectorPS2 *matrix) {
 BkVectorPS2 a,b,c,d;
 __asm__("vsub.xyzw av, vf0, vf0\n\tvsub.xyzw bv, vf0, vf0\n\tvsub.xyzw cv, vf0, vf0\n\tvmove.xyzw dv, vf0\n\tvaddw.x av, vf0, vf0w\n\tvaddw.y bv, vf0, vf0w\n\tvaddw.z cv, vf0, vf0w":"=j av"(a),"=j bv"(b),"=j cv"(c),"=j dv"(d));
 matrix[0]=a;matrix[1]=b;matrix[2]=c;matrix[3]=d;
}
void func_001AF798(char *actor) {
 BkVectorPS2 matrix[4] __attribute__((aligned(16))),packet;BkDrawBatchPS2 *batch;int i;
 s64 low=0x10000000,high=((s64)0x8800<<32 | 0x8800)<<13;
 identity(matrix);func_0035C544((void *)0x70002d7c,matrix,64);
 {int mode=(int)D_0040F4C0+0xcd70;*(int *)mode=1;}
 for(i=0;i<M2C_FIELD(actor,int *,0xcbc8);i++) {
  batch=M2C_FIELD(actor,BkDrawBatchPS2 **,0xcb00+i*4);
  func_001C62F0(batch->a,batch->b,batch->c&0x7fffffff,batch->d&0x7fffffff,batch->e,(s64)batch->c<0,(s64)batch->d<0);
 }
 {int mode=(int)D_0040F4C0+0xcd70;*(int *)mode=0;}
 __asm__("pcpyld pv, hv, lv":"=r pv"(packet):"r hv"(high),"r lv"(low));
 *D_0040E5F0++=packet;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AF798);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AF8E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AF8F8);
