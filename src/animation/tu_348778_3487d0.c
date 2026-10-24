#include "ps2/prelude.h"
#include "animation/pose_cache.h"

f32 func_003487D0(BkModSourceClipPS2 *arg0) {
    return (f32) arg0->frameCount;
}

s32 func_003487E0(BkModSourceClipPS2 *arg0) {
    return arg0->skeletonIndex;
}

s32 func_003487E8(BkModSourceClipPS2 *arg0) {
    return (s32)&arg0->frameCount;
}
