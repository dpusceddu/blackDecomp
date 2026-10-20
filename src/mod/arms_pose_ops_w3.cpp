#include "animation/pose_campaign.hpp"

namespace ArmsPose {

void Cache::Enable(s8 enabled) { BkModPoseCacheEnablePS2(enabled); }
void Cache::Clear() { BkModPoseCacheClearPS2(); }
void Cache::ForceBone(int index) { BkModPoseCacheForceBonePS2(index); }
void Cache::Initialize() { Construct(1, 0xffff); }

Pose* Cache::Allocate()
{
    if (D_0046A500 >= D_003D20D4) return 0;
    return &slots[D_0046A500++].root;
}

// Unmatched: Blend retains slerp helper, register and masked-loop scheduling differences.
// Unmatched: Select retains allocation and null-branch scheduling differences.
// Unmatched: Compose retains vector helper and loop register allocation differences.
// Unmatched: Difference retains inverse-helper and masked-loop scheduling differences.
// Unmatched: Weight retains slerp helper and temporary lifetimes.
// Unmatched: Build retains raw/cache pose copy and frame conversion differences.
// Unmatched: Discrete retains conversion context and two unexplained scheduling NOPs.
// Unmatched: Offsets retains vector assignment and loop pointer scheduling differences.
// Unmatched: Overlay retains slerp and pointer induction differences.

extern Skeleton* GetSkeleton(Operations*) __asm__("func_003489A8");
extern void SampleBone(Pose*, const void*, int, float) __asm__("func_00345480");

Pose* ClipOperations::Default(Operations* owner, BkModSourceClipPS2* clip,
                              unsigned flags, float frame)
{
    Skeleton* skeleton = GetSkeleton(owner);
    // This argument order is a scoped, exact caller recipe for the same ABI.
    extern Pose* BuildOrdered(Operations*, BkModSourceClipPS2*, Skeleton*, float,
                              unsigned) __asm__("func_00346F58");
    return BuildOrdered(owner, clip, skeleton, frame, flags);
}

Pose* ClipOperations::Root(Pose* out, Operations* owner, BkModSourceClipPS2* clip,
                           unsigned flags, int index, float time)
{
    if (!clip || !clip->tracks) return 0;
    int format = clip->trackFormat & 0x7fffffff;
    switch (format) {
    case 3: {
        char* offset = (char*)(index << 5);
        char* base = (char*)clip->tracks;
        Pose* in = (Pose*)((int)offset + (int)base);
        asm volatile("lq $8,0(%0)\n\tsq $8,0(%1)"
                     : : "r"(in), "r"(out) : "$8", "memory");
        // Raw tracks copy XYZ as 8+4 bytes; destination W is set below.
        unsigned long xy = *(unsigned long*)in->translation;
        unsigned z = *(unsigned*)(in->translation + 2);
        *(unsigned*)(out->translation + 2) = z;
        *(unsigned long*)out->translation = xy;
        break;
    }
    case 4:
        SampleBone(out, clip->tracks, index, time);
        break;
    case 0:
    case 1:
    case 2:
        break;
    }
    out->translation[3] = 1;
    return out;
}

float* GraphOperations::Scaled(void* owner, AnimationGraphNode* node,
                               AnimationParameters* parameters, unsigned flags,
                               float current, float previous, float factor,
                               float coefficient)
{
    return AnimationGraph_EvaluateNode(owner, node, parameters, current / factor,
        previous / factor, flags, coefficient / factor, 1.0f);
}

}
