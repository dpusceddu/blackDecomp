#include "include_asm.h"
#include "ps2/prelude.h"
#include "animation/pose_cache.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00348778);

f32 func_003487D0(BkModSourceClipPS2 *arg0) {
    return (f32) arg0->frameCount;
}

s32 func_003487E0(BkModSourceClipPS2 *arg0) {
    return arg0->skeletonIndex;
}

s32 func_003487E8(BkModSourceClipPS2 *arg0) {
    return (s32)&arg0->frameCount;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003487F0);
