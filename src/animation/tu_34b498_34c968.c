#include "include_asm.h"
#include "ps2/prelude.h"

#include "animation/animation_graph_node.h"
#include "animation/animation_parameters.h"
#include "ps2/recovered_types.h"
extern f32 * func_0034BC30(s32 *, Recovered_AnimationGraphNode *, Recovered_AnimationParameters *, u32, void *, s32, f32, f32, f32, f32, f32);
extern s32 func_0034C8C8(void *, Recovered_AnimationGraphNode *, Recovered_AnimationParameters *);

f32 * func_0034C968(s32 *arg0, void *arg1, s32 arg2, s32 arg3, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg1, void **, 8);
    return func_0034BC30(arg0, (Recovered_AnimationGraphNode *) arg1, arg2, arg3, func_0034C8C8, M2C_FIELD(temp_2, s32 *, 8), fparg0, fparg1, fparg2, M2C_FIELD(temp_2, f32 *, 0xC), fparg3);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034CA18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034CA68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034CAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034CC00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034CE20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034D040);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034D0B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034D1E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034D300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034D530);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034D738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034D838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034D9B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034DC30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034DDD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034E220);
