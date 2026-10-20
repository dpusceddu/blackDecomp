#ifndef BLACK_PS2_VU0_QUATERNION_HPP
#define BLACK_PS2_VU0_QUATERNION_HPP
/* Recurring authored animation-macro family: ten independent Hamilton products
   in six functions use these same VF1..4 roles. This is not the generic SN j
   allocation recipe or a claim of SDK identity. Pointer operands remain compiler
   allocated. Multiply overwrites ACC and MAC/status; Add preserves destination W
   and overwrites MAC/status. Q/I/R/VI/clip are untouched. SN accepts VF clobbers
   but cannot represent ACC/flags: those hidden states must be dead across calls.
   Inputs load before output stores, so either input may alias the output. */
#include "ps2/vu0_math.h"
namespace BlackPS2 {
namespace AnimationMath {
static inline void Multiply(void *out, const void *a, const void *b)
{
    asm volatile("lqc2 vf1,0(%0)\n\t"
                 "lqc2 vf2,0(%1)\n\t"
                 "vmul.xyzw vf4,vf1,vf2\n\t"
                 "vsubay.w ACC,vf4,vf4y\n\t"
                 "vmsubaz.w ACC,vf0,vf4z\n\t"
                 "vmsubx.w vf3,vf0,vf4x\n\t"
                 "vopmula.xyz ACC,vf1,vf2\n\t"
                 "vopmsub.xyz vf3,vf2,vf1\n\t"
                 "vmulaw.xyz ACC,vf2,vf1w\n\t"
                 "vmaddaw.xyz ACC,vf1,vf2w\n\t"
                 "vmaddw.xyz vf3,vf3,vf0w\n\t"
                 "sqc2 vf3,0(%2)"
                 : : "r"(a),"r"(b),"r"(out):"vf1","vf2","vf3","vf4","memory");
}
static inline void Add(void *out, const void *a, const void *b)
{
    asm volatile("lqc2 vf9,0(%0)\n\t"
                 "lqc2 vf10,0(%1)\n\t"
                 "lqc2 vf11,0(%2)\n\t"
                 "vadd.xyz vf11,vf9,vf10\n\t"
                 "sqc2 vf11,0(%2)"
                 : : "r"(a),"r"(b),"r"(out):"vf9","vf10","vf11","memory");
}}
}
#endif
