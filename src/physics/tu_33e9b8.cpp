#include "include_asm.h"

#include "physics/startup_constants.h"
#include "ps2/vu0_math.h"

using namespace PhysicsStartup;
extern "C" {
extern StartupToken D_0040E968, D_0040E970;
extern ConstantQuad D_0045E920, D_0045E930, D_0045E940, D_0045E950;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040E968,8\n.extern D_0040E970,8");

extern "C" void func_0033E9B8(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E968);
            func_00100258(&D_0040E970);
            VectorTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            VectorTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            VectorTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            VectorTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0045E920.value = qa;
            D_0045E930.value = qb;
            D_0045E940.value = qc;
            D_0045E950.value = qd;
        } else {
            func_00100260(&D_0040E970, 2);
            func_00100230(&D_0040E968, 2);
        }
    }
}

struct AxisSupportView {
    EeS128 origin;
    unsigned char unknown10[0x30];
    EeS128 firstEdge;
    unsigned char unknown50[0x20];
    float firstPayload;
};
struct AxisInterval { float low, high; };


static inline float DotXYZ(EeS128 first, EeS128 second)
{
    EeS128 product = BkVuMulXYZ(first, second);
    EeS128 sum;
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
static inline float AbsoluteWord(int word)
{
    volatile union { int bits; float value; } scalar;
    scalar.bits = word;
    scalar.bits &= 0x7fffffff;
    return scalar.value;
}

extern "C" void func_0033EB00() {}
extern "C" void func_0033EB08(const AxisSupportView* support, EeS128 axis, AxisInterval* interval)
{
    interval->low = interval->high = DotXYZ(axis, support->origin);
    float extent = AbsoluteWord(FloatWord(DotXYZ(support->firstEdge, axis))) * support->firstPayload;
    interval->low -= extent;
    interval->high += extent;
}
extern "C" int func_0033EB88() { return 1; }

extern "C" void func_0033EB90() { func_0033E9B8(1, 65535); }
extern "C" void func_0033EBB0() { func_0033E9B8(0, 65535); }

extern "C" {
StartupToken D_0040E968 __attribute__((section(".sbss")));
StartupToken D_0040E970 __attribute__((section(".sbss")));
ConstantQuad D_0045E920, D_0045E930, D_0045E940, D_0045E950;
}
