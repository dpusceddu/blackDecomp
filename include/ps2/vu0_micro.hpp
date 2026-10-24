#ifndef BLACK_PS2_VU0_MICRO_HPP
#define BLACK_PS2_VU0_MICRO_HPP

// These entries belong to the animation VIF upload, not to every program that
// can occupy VU0 micro memory. The loader must have installed that image first.
// VCALLMS operands are byte addresses (0x1a8 encodes instruction index 0x35).
// VNOP is the retail macro-mode synchronization after each call.
//
// SN 1.36 accepts VF clobbers but rejects ACC, Q, I, R and VI register names.
// Consequently these complete load/call/store recipes are restricted to code
// with no compiler-unrepresented ACC/Q/I/flag state live across the operation.
// The memory clobber describes memory only; it does not protect VU specials.
// Register contracts are independently decoded from the resident microcode by
// tools/pipeline/vu0_micro.py; its flag-pipeline report is conservative, not a simulator.
// Every recipe has an isolated encoding control. Whole-function exact consumers
// now include Slerp and XYZW interpolation in pose Overlay (0x347600).
// Check the study's two-real-consumer threshold separately for each recipe.

namespace BlackPS2 {
namespace AnimationMicro {

// Animation Slerp ABI: value inputs VF18/19.xyzw and VF28.x; result VF20.xyzw.
// VF19 is modified. The polynomial also reads VF28.zw in lanes that do not
// contribute to the returned quaternion; their arithmetic flags are unspecified
// when the scalar weight transfer leaves these lanes unspecified. May clobber
// VF14..28, VF30.xyzw, VF31.xyz, VI1/2, ACC, I, Q, MAC and status; preserves R,
// clip and VU data memory. SQRT/RSQRT and both branch paths are in the image.
// All seven retail sites use T0 as the inline macro's explicit transfer scratch;
// the float operand is allocated normally (retail uses both F12 and F20).
static inline void Slerp(void *output, const void *a, const void *b, float weight)
{
    asm volatile("lqc2 vf18,0(%0)\n\t"
                 "lqc2 vf19,0(%1)\n\t"
                 "mfc1 $8,%3\n\tqmtc2.ni $8,vf28\n\t"
                 "vcallms 0x330\n\tvnop\n\tsqc2 vf20,0(%2)"
                 : : "r"(a), "r"(b), "r"(output), "f"(weight)
                 : "$8", "vf14", "vf15", "vf16", "vf17", "vf18", "vf19",
                   "vf20", "vf21", "vf22", "vf23", "vf24", "vf25", "vf26",
                   "vf27", "vf28", "vf30", "vf31", "memory");
}

// The companion animation translation recipe has fixed VF9..12 and T0 in
// every observed expansion. Unlike the XYZW variant below, it reloads the
// destination and preserves its W lane. ACC/MAC/status are overwritten.
static inline void InterpolateXYZ(void *output, const void *a, const void *b, float weight)
{
    asm volatile("lqc2 vf9,0(%0)\n\tlqc2 vf10,0(%1)\n\tmfc1 $8,%3\n\t"
                 "vsub.xyzw vf10,vf10,vf9\n\tqmtc2.ni $8,vf11\n\t"
                 "lqc2 vf12,0(%2)\n\tvaddax.xyz ACC,vf9,vf0x\n\t"
                 "vmaddx.xyz vf12,vf10,vf11x\n\tsqc2 vf12,0(%2)"
                 : : "r"(a), "r"(b), "r"(output), "f"(weight)
                 : "$8", "vf9", "vf10", "vf11", "vf12", "memory");
}

static inline void InterpolateXYZW(void *output, const void *a, const void *b, float weight)
{
    asm volatile("lqc2 vf9,0(%0)\n\tlqc2 vf10,0(%1)\n\tmfc1 $8,%3\n\t"
                 "vsub.xyzw vf10,vf10,vf9\n\tqmtc2.ni $8,vf11\n\t"
                 "vaddax.xyzw ACC,vf9,vf0x\n\t"
                 "vmaddx.xyzw vf12,vf10,vf11x\n\tsqc2 vf12,0(%2)"
                 : : "r"(a), "r"(b), "r"(output), "f"(weight)
                 : "$8", "vf9", "vf10", "vf11", "vf12", "memory");
}

// Full 4x4 multiplication, including W. Reads VF1..8.xyzw; writes VF9..12.xyzw,
// ACC.xyzw and arithmetic MAC/status flags. Preserves Q/I/R/VI and clip flags.
// 'output' may alias either input: all input vectors load before stores begin.
static inline void Multiply4x4(void *output, const void *local, const void *parent)
{
    asm volatile("lqc2 vf1,0(%0)\n\t"
                 "lqc2 vf2,16(%0)\n\t"
                 "lqc2 vf3,32(%0)\n\t"
                 "lqc2 vf4,48(%0)\n\t"
                 "lqc2 vf5,0(%1)\n\t"
                 "lqc2 vf6,16(%1)\n\t"
                 "lqc2 vf7,32(%1)\n\t"
                 "lqc2 vf8,48(%1)\n\t"
                 "vcallms 0\n\tvnop\n\t"
                 "sqc2 vf9,0(%2)\n\t"
                 "sqc2 vf10,16(%2)\n\t"
                 "sqc2 vf11,32(%2)\n\t"
                 "sqc2 vf12,48(%2)"
                 : : "r"(local), "r"(parent), "r"(output)
                 : "vf1", "vf2", "vf3", "vf4", "vf5", "vf6", "vf7", "vf8",
                   "vf9", "vf10", "vf11", "vf12", "memory");
}

// Quaternion-to-rotation, not an affine matrix multiplication. Reads VF1.xyzw;
// writes VF2..5.xyzw, VF6/7.xyz, VF11..13.xyz, VF14.w, ACC.xyz and MAC/status.
// Produces three rows only, with W zero; the caller supplies row 3 separately.
static inline void QuaternionRotation(void *threeRows, const void *quaternion)
{
    asm volatile("lqc2 vf1,0(%0)\n\tvcallms 0x1a8\n\tvnop\n\t"
                 "sqc2 vf2,0(%1)\n\t"
                 "sqc2 vf3,16(%1)\n\t"
                 "sqc2 vf4,32(%1)"
                 : : "r"(quaternion), "r"(threeRows)
                 : "vf1", "vf2", "vf3", "vf4", "vf5", "vf6", "vf7",
                   "vf11", "vf12", "vf13", "vf14", "memory");
}

// Rigid transform inverse. Reads VF15..17.xyzw and VF18.xyz; writes
// VF1..4.xyzw, VF9.xyz, ACC.xyz and arithmetic MAC/status. Q/I/R/VI/clip
// remain untouched. W of the translation input is not used.
// One exact original consumer currently verifies this recipe; it is not yet
// a two-consumer control for arbitrary enclosing functions.
static inline void InverseRigid(void *output, const void *input)
{
    asm volatile("lqc2 vf15,0(%0)\n\t"
                 "lqc2 vf16,16(%0)\n\t"
                 "lqc2 vf17,32(%0)\n\t"
                 "lqc2 vf18,48(%0)\n\t"
                 "vcallms 0x490\n\tvnop\n\t"
                 "sqc2 vf1,0(%1)\n\t"
                 "sqc2 vf2,16(%1)\n\t"
                 "sqc2 vf3,32(%1)\n\t"
                 "sqc2 vf4,48(%1)"
                 : : "r"(input), "r"(output)
                 : "vf1", "vf2", "vf3", "vf4", "vf9",
                   "vf15", "vf16", "vf17", "vf18", "memory");
}

}
}
#endif
