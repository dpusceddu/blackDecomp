#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: 51/425 instructions differ in scalar views, shared point tails and VU allocation; 1704-byte span is preserved.
// Synthetic finite-input checks cover feature memory and preserved registers; gameplay, VU scratch state and W are unverified.
// Recorded replay: 9/54 pass; 45 differ in VU outputs, with 64% original block coverage. This remains a draft.
#ifdef BLACK_NONMATCHING
#include "ps2/ee_types.h"
#include "ps2/vu0_math.h"
extern "C" float sqrtf(float);

static inline float DotXYZ(EeS128 first, EeS128 second)
{
    EeS128 product = BkVuMulXYZ(first, second), sum;
    __asm__("vaddy.x sumv, productv, productvy" : "=j sumv"(sum) : "j productv"(product));
    __asm__("vaddz.x sumv, sumv, productvz" : "+j sumv"(sum) : "j productv"(product));
    float value;
    __asm__("qmfc2.ni bitsr, sumv" : "=r bitsr"(value) : "j sumv"(sum));
    return value;
}
static inline int FloatWord(float value)
{
    union { float value; int bits; } scalar;
    scalar.value = value;
    return scalar.bits;
}
static inline float DotFloatAndWord(EeS128 first,EeS128 second,int& word)
{
    float bits = DotXYZ(first, second);
    word = FloatWord(bits);
    float value;
    __asm__("mtc1 bitsr, valuef" : "=f valuef"(value) : "r bitsr"(word));
    return value;
}
static inline EeS128 NegateXYZ(EeS128 value)
{
    EeS128 result;
    __asm__("vsub.xyz resultv, vf0, inputv" : "=j resultv"(result) : "j inputv"(value));
    return result;
}

static inline EeS128 CrossAxisXYZ(EeS128 axis,EeS128 direction)
{
    EeS128 result;
    __asm__ volatile("vopmula.xyz ACC, directionv, axisv\n\t"
                     "vopmsub.xyz resultv, axisv, directionv"
                     : "=j resultv"(result) : "j axisv"(axis), "j directionv"(direction));
    return result;
}

// Only the X lane is consumed by the following broadcast operation.
static inline EeS128 ScalarNative(float scalar)
{
    EeS128 result;
    __asm__("qmtc2.ni scalarr, resultv" : "=j resultv"(result) : "r scalarr"(scalar));
    return result;
}

union ScalarWordStorage { int bits; float value; };
static inline float AbsoluteStored(int word,volatile ScalarWordStorage& scalar)
{
    scalar.bits = word;
    scalar.bits &= 0x7fffffff;
    return scalar.value;
}

static inline EeS128 NativeQuad(EeS128 value)
{
    EeS128 result;
    __asm__("qmfc2.ni resultv, inputv" : "=r resultv"(result) : "j inputv"(value));
    return result;
}

struct TriangleSupportView {
    EeS128 vertex0, faceNormal, vertex1, vertex2, edges[3];
    float payload[3];
};
struct FeatureEdge {
    EeS128 vertex, direction, plane;
    float length;
    unsigned unspecifiedLengthLanes[3];
    FeatureEdge() {}
    void Initialize(const EeS128& start, const EeS128& along, float extent)
    {
        vertex = start;
        direction = along;
        length = extent;
    }
    // The constructor leaves the plane and the other length lanes unassigned.
    void BuildPlane(const EeS128& axis)
    {
        plane = CrossAxisXYZ(axis, direction);
        float lengthSquared = DotXYZ(plane, plane);
        if (lengthSquared > 1.1920928955078125e-07f) {
            float inverse = 1.0f / sqrtf(lengthSquared);
            plane = BkVuScaleXYZ(plane, ScalarNative(inverse));
        }
    }
};
struct TriangleFeatureView {
    unsigned identity;
    unsigned char unknown004[12];
    FeatureEdge edges[4];
    EeS128 faceNormal, point;
    int edgeCount;
    void BuildPlanes(int forward, const EeS128* axis)
    {
        if (forward) {
            for (int i = 0; i < edgeCount; ++i)
                edges[i].BuildPlane(*axis);
        } else {
            for (int i = 0; i < edgeCount; ++i)
                edges[i].BuildPlane(NegateXYZ(*axis));
        }
    }
};

typedef char TrianglePayloadOffset[((int)&((TriangleSupportView*)0)->payload == 0x70) ? 1 : -1];
typedef char FeatureEdgeSize[sizeof(FeatureEdge) == 0x40 ? 1 : -1];
typedef char FeatureLengthOffset[((int)&((FeatureEdge*)0)->length == 0x30) ? 1 : -1];
typedef char FeaturePointOffset[((int)&((TriangleFeatureView*)0)->point == 0x120) ? 1 : -1];
typedef char FeatureCountOffset[((int)&((TriangleFeatureView*)0)->edgeCount == 0x130) ? 1 : -1];

static inline int GreaterScalar(float a, float b) { return b < a; }

extern "C" void func_0033F400(const TriangleSupportView* support, int forward,
                              EeS128 axis, TriangleFeatureView* feature)
{
    FeatureEdge edgeTemp0, edgeTemp1, edgeTemp2, edgeTemp3, edgeTemp4;
    FeatureEdge edgeTemp5, edgeTemp6, edgeTemp7, edgeTemp8;
    volatile ScalarWordStorage alignmentAbs, edgeAbs;
    int alignmentWord;
    float alignment = DotFloatAndWord(axis, support->faceNormal, alignmentWord);
    if (0.95f < AbsoluteStored(alignmentWord, alignmentAbs)) {
        if ((alignment < 0.0f) == forward) {
            edgeTemp0.Initialize(support->vertex0, support->edges[0], support->payload[0]);
            feature->edges[0] = edgeTemp0;
            edgeTemp1.Initialize(support->vertex1, support->edges[1], support->payload[1]);
            feature->edges[1] = edgeTemp1;
            edgeTemp2.Initialize(support->vertex2, support->edges[2], support->payload[2]);
            feature->edges[2] = edgeTemp2;
            feature->identity = 8;
        } else {
            edgeTemp3.Initialize(support->vertex0, NegateXYZ(support->edges[2]), support->payload[2]);
            feature->edges[0] = edgeTemp3;
            edgeTemp4.Initialize(support->vertex2, NegateXYZ(support->edges[1]), support->payload[1]);
            feature->edges[1] = edgeTemp4;
            edgeTemp5.Initialize(support->vertex1, NegateXYZ(support->edges[0]), support->payload[0]);
            feature->edges[2] = edgeTemp5;
            feature->identity = 0;
        }
        feature->faceNormal = support->faceNormal;
        feature->edgeCount = 3;
    } else {
        int perpendicular = 0;
        unsigned selected = 0;
        for (unsigned i = 0; i < 3; ++i) {
            if (AbsoluteStored(FloatWord(DotXYZ(axis, support->edges[i])), edgeAbs) < 0.05f) {
                perpendicular = 1;
                selected = i;
            }
        }
        if (perpendicular) {
            if (selected == 0) {
                if (GreaterScalar(DotXYZ(support->vertex0, axis), DotXYZ(support->vertex2, axis))) {
                    edgeTemp6.Initialize(support->vertex0, support->edges[0], support->payload[0]);
                    feature->edges[0] = edgeTemp6;
                    feature->edgeCount = 1;
                    feature->identity = 6;
                } else {
                    feature->point = *(const volatile EeS128*)&support->vertex2;
                    feature->edgeCount = 0;
                    feature->identity = 3;
                }
            } else if (selected == 1) {
                if (GreaterScalar(DotXYZ(support->vertex1, axis), DotXYZ(support->vertex0, axis))) {
                    edgeTemp7.Initialize(support->vertex1, support->edges[1], support->payload[1]);
                    feature->edges[0] = edgeTemp7;
                    feature->edgeCount = 1;
                    feature->identity = 4;
                } else {
                    feature->point = *(const volatile EeS128*)&support->vertex0;
                    feature->edgeCount = 0;
                    feature->identity = 1;
                }
            } else {
                int chooseEdge = GreaterScalar(DotXYZ(support->vertex2, axis), DotXYZ(support->vertex1, axis));
                EeS128 selectedNative = NativeQuad(support->vertex2);
                if (chooseEdge) {
                    edgeTemp8.Initialize(selectedNative, support->edges[2], support->payload[2]);
                    feature->edges[0] = edgeTemp8;
                    feature->edgeCount = 1;
                    feature->identity = 2;
                } else {
                    feature->point = *(const volatile EeS128*)&support->vertex1;
                    feature->edgeCount = 0;
                    feature->identity = 5;
                }
            }
        } else {
            feature->edgeCount = 0;
            float best = DotXYZ(support->vertex0, axis);
            feature->point = support->vertex0;
            feature->identity = 1;
            float second = DotXYZ(support->vertex1, axis);
            if (best < second) {
                best = second;
                feature->point = support->vertex1;
                feature->identity = 5;
            }
            if (best < DotXYZ(support->vertex2, axis)) {
                feature->point = NativeQuad(support->vertex2);
                feature->identity = 3;
            }
        }
    }
    feature->BuildPlanes(forward, &axis);
}

#endif
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033F400);
#endif
