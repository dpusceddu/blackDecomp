#include "animation/arms/rig.hpp"
#include "ps2/vu0_micro.hpp"

namespace ArmsAnimation {

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

static inline void Identity(RigMatrix *matrix)
{
    asm volatile("pand $8,$zero,$zero\n\tlui $8,0x3f80\n\t"
                 "sq $8,0(%0)\n\tpextlw $8,$8,$zero\n\tsq $8,16(%0)\n\t"
                 "pextlw $9,$zero,$8\n\tsq $9,32(%0)\n\t"
                 "pextlw $9,$8,$zero\n\tsq $9,48(%0)"
                 : : "r"(matrix) : "$8", "$9", "memory");
}

// These fixed-VF expansions have no live ACC/Q/flag state across their boundary.
static inline void ScaleRows(RigMatrix *matrix, const float *scale)
{
    asm volatile("lqc2 vf9,0(%1)\n\tlqc2 vf10,0(%0)\n\t"
                 "vmulx.xyzw vf12,vf10,vf9x\n\tlqc2 vf11,16(%0)\n\t"
                 "sqc2 vf12,0(%0)\n\tvmuly.xyzw vf13,vf11,vf9y\n\t"
                 "lqc2 vf10,32(%0)\n\tsqc2 vf13,16(%0)\n\t"
                 "vmulz.xyzw vf12,vf10,vf9z\n\tsqc2 vf12,32(%0)"
                 : : "r"(matrix), "r"(scale)
                 : "vf9", "vf10", "vf11", "vf12", "vf13", "memory");
}

static inline void TransformPoint(float *output, const RigMatrix *matrix, const float *point)
{
    asm volatile("lqc2 vf1,0(%0)\n\tlqc2 vf2,16(%0)\n\t"
                 "lqc2 vf3,32(%0)\n\tlqc2 vf4,48(%0)"
                 : : "r"(matrix) : "vf1", "vf2", "vf3", "vf4", "memory");
    asm volatile("lqc2 vf9,0(%0)\n\tvmulax.xyzw ACC,vf1,vf9x\n\t"
                 "vmadday.xyzw ACC,vf2,vf9y\n\tvmaddaz.xyzw ACC,vf3,vf9z\n\t"
                 "vmaddw.xyzw vf10,vf4,vf9w\n\tsqc2 vf10,0(%1)"
                 : : "r"(point), "r"(output)
                 : "vf1", "vf2", "vf3", "vf4", "vf9", "vf10", "memory");
}

// The original normalizes XYZW and tests the squared length before its result is used.
static inline void NormalizeRow(const s128 *input, s128 *row)
{
    float squaredLength;
    asm volatile("lqc2 vf9,0(%1)\n\tvaddw.x vf12,vf0,vf0w\n\t"
                 "vmul.xyzw vf10,vf9,vf9\n\tvadday.x ACC,vf10,vf10y\n\t"
                 "vmaddaz.x ACC,vf12,vf10z\n\tvmaddw.x vf10,vf12,vf10w\n\t"
                 "vrsqrt Q,vf0w,vf10x\n\tqmfc2.ni $8,vf10\n\tmtc1 $8,%0\n\t"
                 "vwaitq\n\tvmulq.xyzw vf11,vf9,Q\n\tsqc2 vf11,0(%2)"
                 : "=f"(squaredLength) : "r"(input), "r"(row)
                 : "$8", "vf9", "vf10", "vf11", "vf12", "memory");
    if (squaredLength < 9.31322574615478515625e-10f)
        asm volatile("sq $zero,0(%0)" : : "r"(row) : "memory");
}

static inline void MultiplyMatrices(void *output, const void *local, const void *parent)
{
    asm volatile("lqc2 vf1,0(%0)\n\tlqc2 vf2,16(%0)\n\t"
                 "lqc2 vf3,32(%0)\n\tlqc2 vf4,48(%0)"
                 : : "r"(local) : "vf1", "vf2", "vf3", "vf4", "memory");
    asm volatile("lqc2 vf5,0(%0)\n\tlqc2 vf6,16(%0)\n\t"
                 "lqc2 vf7,32(%0)\n\tlqc2 vf8,48(%0)\n\t"
                 "vcallms 0\n\tvnop\n\t"
                 "sqc2 vf9,0(%1)\n\tsqc2 vf10,16(%1)\n\t"
                 "sqc2 vf11,32(%1)\n\tsqc2 vf12,48(%1)"
                 : : "r"(parent), "r"(output)
                 : "vf1", "vf2", "vf3", "vf4", "vf5", "vf6", "vf7", "vf8",
                   "vf9", "vf10", "vf11", "vf12", "memory");
}

static inline void IdentityRotation(RigMatrix *matrix)
{
    asm volatile("pand $8,$zero,$zero\n\tlui $8,0x3f80\n\t"
                 "sq $8,0(%0)\n\tpextlw $8,$8,$zero\n\tsq $8,16(%0)\n\t"
                 "pextlw $9,$zero,$8\n\tsq $9,32(%0)"
                 : : "r"(matrix) : "$8", "$9", "memory");
}

static inline s128 *NativeRowAddress(s128 *row)
{
    return row;
}

void Rig::Build(Pose *pose)
{
    RigMatrix *matrices = (RigMatrix *)selectedMatrices;
    AnimationSkeleton *skeleton = AnimationInstance_Skeleton(this);
    if (matrixBase) {
        AnimationHierarchy *bone = skeleton->hierarchy;
        RigMatrix *output = matrices;
        Identity(output);
        output->v[0] = rootScale;
        output->v[5] = rootScale;
        output->v[10] = rootScale;
        Pose *local = pose + 2;
        ++bone;
        ++output;
        RigMatrix overrideMatrix;
        RigMatrix parentCopy;
        float transformedPoint[4] __attribute__((aligned(16)));
        RigMatrix normalizedParent;
        RigMatrix fullResult;
        Pose *overridePose;
        unsigned overrideFlags;
        int index;
        for (index = 1; index < skeleton->boneCount; ++index, ++local, ++bone, ++output) {
            float homogeneous = 1.0f;
            float *overrideTranslationPointer = overrideMatrix.v + 12;
            float *pointPointer = transformedPoint;
            s128 *parentTranslationPointer = NativeRowAddress(parentCopy.row + 3);
            RigMatrix *fullResultPointer = &fullResult;

            RigMatrix *parent = matrices + bone->parent;
            FindOverride(this, index, &overridePose, &overrideFlags);
            if (overridePose != 0) {
                if (overrideFlags & 1) {
                    BlackPS2::AnimationMicro::QuaternionRotation(output, local->quaternion);
                    if (bone->flags & 4) {
                        const AnimationBind *binding = jointCache[bone - skeleton->hierarchy];
                        output->v[12] = binding->matrix.v[12];
                        output->v[13] = binding->matrix.v[13];
                        output->v[14] = binding->matrix.v[14];
                        output->v[15] = homogeneous;
                    } else {
                        output->v[12] = local->translation[0];
                        output->v[13] = local->translation[1];
                        output->v[14] = local->translation[2];
                        output->v[15] = homogeneous;
                    }
                    MultiplyMatrices(output, output, parent);
                    if (overrideFlags & 4) {
                        BlackPS2::AnimationMicro::QuaternionRotation(&overrideMatrix, overridePose->quaternion);
                        asm volatile("sqc2 vf0,0(%0)" : : "r"(overrideTranslationPointer) : "memory");
                        if (overrideFlags & 8) {
                            overrideMatrix.v[12] = overridePose->translation[0];
                            overrideMatrix.v[13] = overridePose->translation[1];
                            overrideMatrix.v[14] = overridePose->translation[2];
                        }
                        MultiplyMatrices(output, &overrideMatrix, output);
                    } else if (overrideFlags & 8) {
                        transformedPoint[0] = overridePose->translation[0];
                        transformedPoint[1] = overridePose->translation[1];
                        transformedPoint[2] = overridePose->translation[2];
                        transformedPoint[3] = homogeneous;
                        TransformPoint(output->v + 12, output, pointPointer);
                    }
                } else {
                    if (overrideFlags & 4) {
                        BlackPS2::AnimationMicro::QuaternionRotation(output, overridePose->quaternion);
                        IdentityRotation(&parentCopy);
                        asm volatile("lq $8,0(%1)\n\tsq $8,0(%0)" : : "r"(parentTranslationPointer), "r"(parent->row + 3) : "$8", "memory");
                    } else {
                        BlackPS2::AnimationMicro::QuaternionRotation(output, local->quaternion);
                        CopyMatrix(&parentCopy, parent);
                    }
                    if (overrideFlags & 8) {
                        output->v[12] = overridePose->translation[0];
                        output->v[13] = overridePose->translation[1];
                        output->v[14] = overridePose->translation[2];
                        output->v[15] = homogeneous;
                        parentCopy.v[12] = 0.0f;
                        parentCopy.v[13] = 0.0f;
                        parentCopy.v[14] = 0.0f;
                        parentCopy.v[15] = homogeneous;
                    } else {
                        if (bone->flags & 4) {
                            const AnimationBind *binding = jointCache[bone - skeleton->hierarchy];
                            output->v[12] = binding->matrix.v[12];
                            output->v[13] = binding->matrix.v[13];
                            output->v[14] = binding->matrix.v[14];
                            output->v[15] = homogeneous;
                        } else {
                            output->v[12] = local->translation[0];
                            output->v[13] = local->translation[1];
                            output->v[14] = local->translation[2];
                            output->v[15] = homogeneous;
                        }
                    }
                    MultiplyMatrices(output, output, &parentCopy);
                }
            } else {
                BlackPS2::AnimationMicro::QuaternionRotation(output, local->quaternion);
                if (bone->flags & 4) {
                    const AnimationBind *binding = jointCache[bone - skeleton->hierarchy];
                    output->v[12] = binding->matrix.v[12];
                    output->v[13] = binding->matrix.v[13];
                    output->v[14] = binding->matrix.v[14];
                    output->v[15] = homogeneous;
                } else {
                    output->v[12] = local->translation[0];
                    output->v[13] = local->translation[1];
                    output->v[14] = local->translation[2];
                    output->v[15] = homogeneous;
                }
                if (bone->flags & 8)
                    ScaleRows(output, jointCache[bone - skeleton->hierarchy]->scale);
                if (parent) {
                    if (bone->flags & 1) {
                        CopyMatrix(&normalizedParent, parent);
                        NormalizeRow(normalizedParent.row + 0, normalizedParent.row + 0);
                        NormalizeRow(normalizedParent.row + 1, normalizedParent.row + 1);
                        NormalizeRow(normalizedParent.row + 2, normalizedParent.row + 2);
                        NormalizeRow(normalizedParent.row + 3, normalizedParent.row + 3);
                        MultiplyMatrices(fullResultPointer, output, parent);
                        MultiplyMatrices(output, output, &normalizedParent);
                        output->v[12] = fullResult.v[12];
                        output->v[13] = fullResult.v[13];
                        output->v[14] = fullResult.v[14];
                    } else {
                        MultiplyMatrices(output, output, parent);
                    }
                }
            }
        }
    }
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
