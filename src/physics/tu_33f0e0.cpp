#include "include_asm.h"

#include "physics/startup_constants.h"
#include "ps2/vu0_math.h"

using namespace PhysicsStartup;
extern "C" {
extern StartupToken D_0040E978, D_0040E980;
extern ConstantQuad D_0045E960, D_0045E970, D_0045E980, D_0045E990;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040E978,8\n.extern D_0040E980,8");

extern "C" void func_0033F0E0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E978);
            func_00100258(&D_0040E980);
            VectorTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            VectorTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            VectorTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            VectorTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0045E960.value = qa;
            D_0045E970.value = qb;
            D_0045E980.value = qc;
            D_0045E990.value = qd;
        } else {
            func_00100260(&D_0040E980, 2);
            func_00100230(&D_0040E978, 2);
        }
    }
}

struct SphereSupportView { EeS128 origin; };
struct SphereFeatureView {
    unsigned count;
    unsigned char unknown004[0x11c];
    EeS128 point;
    int edgeCount;
};
struct SphereShapeView {
    unsigned char unknown00[0x30];
    EeS128 position;
    int GetPointCore(void*, void*, SphereFeatureView*) const __asm__("func_0033F2D0");
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

extern "C" void func_0033F228() {}
extern "C" void func_0033F230(const SphereSupportView* support, int, const void*, SphereFeatureView* feature)
{
    feature->point = support->origin;
    feature->edgeCount = 0;
    feature->count = 0;
}
extern "C" void func_0033F248(const SphereSupportView* support, EeS128 axis, AxisInterval* interval)
{
    interval->low = interval->high = DotXYZ(axis, support->origin);
}
extern "C" void func_0033F278(const SphereSupportView* support, const EeS128* axes, unsigned count, AxisInterval* intervals)
{
    for (unsigned i = 0; i < count; ++i)
        intervals[i].low = intervals[i].high = DotXYZ(axes[i], support->origin);
}
extern "C" int func_0033F2C8() { return 1; }
int SphereShapeView::GetPointCore(void*, void*, SphereFeatureView* feature) const
{
    feature->edgeCount = 0;
    feature->point = position;
    return 1;
}

extern "C" void func_0033F2E8() { func_0033F0E0(1, 65535); }
extern "C" void func_0033F308() { func_0033F0E0(0, 65535); }

extern "C" {
StartupToken D_0040E978 __attribute__((section(".sbss")));
StartupToken D_0040E980 __attribute__((section(".sbss")));
ConstantQuad D_0045E960, D_0045E970, D_0045E980, D_0045E990;
}
