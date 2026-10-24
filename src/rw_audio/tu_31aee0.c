#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0031AEE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0031B030);

#include "ps2/recovered_types.h"
extern s32 D_0040E1FC;
extern void * D_0040E200;

void func_0031B530(s32 arg0, void *arg1) {
    D_0040E1FC = (M2C_UNK (*)(f32 *, void *, void *, void *, void *, void *)) arg0;
    D_0040E200 = arg1;
}
