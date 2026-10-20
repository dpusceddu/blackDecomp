#include "mod/arms/rig.hpp"
#include "ps2/vu0_micro.hpp"

namespace ArmsAnimation {

// Unmatched: Build (1944 bytes) still differs in matrix temporary lifetimes and normalization scheduling.

// The PS2 matrix copy uses two rolling 128-bit loads, with no conversion.
static inline void CopyMatrix(RigMatrix* output, const RigMatrix* input)
{
    asm volatile("lq $8,0(%0)\n\t"
                 "lq $9,16(%0)\n\t"
                 "sq $8,0(%1)\n\t"
                 "lq $8,32(%0)\n\t"
                 "sq $9,16(%1)\n\t"
                 "lq $9,48(%0)\n\t"
                 "sq $8,32(%1)\n\t"
                 "sq $9,48(%1)"
                 : : "r"(input), "r"(output) : "$8", "$9", "memory");
}

void Rig::Get(int index, RigMatrix* output)
{
    char* base = (char*)selectedMatrices;
    char* offset = (char*)(index << 6);
    RigMatrix* input = (RigMatrix*)((int)offset + (int)base);
    CopyMatrix(output, input);
}

void Rig::SetBind(int index, const RigMatrix* input)
{
    AnimationSkeleton* skeleton = AnimationInstance_Skeleton(this);
    char* base = (char*)skeleton->bindMatrices;
    char* offset = (char*)(index << 6);
    RigMatrix* output = (RigMatrix*)((int)offset + (int)base);

    BlackPS2::AnimationMicro::InverseRigid(output, input);
}

}
