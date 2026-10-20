#include "mod/arms/rig.hpp"

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

    // This leaf boundary has no compiler-held VU values across the microcall.
    // Its fixed input/output vectors are verified here; no general microprogram
    // clobber or synchronization contract is implied for other callers.
    asm volatile("lqc2 vf15,0(%0)\n\t"
                 "lqc2 vf16,16(%0)\n\t"
                 "lqc2 vf17,32(%0)\n\t"
                 "lqc2 vf18,48(%0)\n\t"
                 "vcallms 0x490\n\t"
                 "vnop\n\t"
                 "sqc2 vf1,0(%1)\n\t"
                 "sqc2 vf2,16(%1)\n\t"
                 "sqc2 vf3,32(%1)\n\t"
                 "sqc2 vf4,48(%1)"
                 : : "r"(input), "r"(output)
                 : "vf1", "vf2", "vf3", "vf4", "vf5", "vf6", "vf7", "vf8",
                   "vf9", "vf10", "vf11", "vf12", "vf13", "vf14", "vf15", "vf16",
                   "vf17", "vf18", "vf19", "vf20", "vf21", "vf22", "vf23", "vf24",
                   "vf25", "vf26", "vf27", "vf28", "vf29", "vf30", "vf31", "memory");
}

}
