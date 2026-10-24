#include "physics/startup_constants.h"

using namespace PhysicsStartup;
extern "C" {
extern StartupToken D_0040E958, D_0040E960;
extern ConstantQuad D_0045E8E0, D_0045E8F0, D_0045E900, D_0045E910;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040E958,8\n.extern D_0040E960,8");

extern "C" void func_0033D940(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E958);
            func_00100258(&D_0040E960);
            VectorTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            VectorTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            VectorTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            VectorTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0045E8E0.value = qa;
            D_0045E8F0.value = qb;
            D_0045E900.value = qc;
            D_0045E910.value = qd;
        } else {
            func_00100260(&D_0040E960, 2);
            func_00100230(&D_0040E958, 2);
        }
    }
}

// Accessed PS2 prefixes; field roles follow the Xbox GetPointCore body.
struct PointCoreFeature {
    unsigned char unknown000[0x120];
    EeS128 point;
    int edgeCount;
};
struct PointCoreShape {
    unsigned char unknown00[0x30];
    EeS128 position;
    int GetPointCore(void*, void*, PointCoreFeature*) const __asm__("func_0033DA98");
};

extern "C" void func_0033DA88() {}
extern "C" int func_0033DA90() { return 1; }

// Unmatched: 0033DA98 body is exact; native section is eight tail padding bytes short.
#ifdef BLACK_NONMATCHING
int PointCoreShape::GetPointCore(void*, void*, PointCoreFeature* feature) const
{
    feature->edgeCount = 0;
    feature->point = position;
    return 1;
}

#endif

extern "C" void func_0033DAB8() { func_0033D940(1, 65535); }
extern "C" void func_0033DAD8() { func_0033D940(0, 65535); }

extern "C" {
StartupToken D_0040E958 __attribute__((section(".sbss")));
StartupToken D_0040E960 __attribute__((section(".sbss")));
ConstantQuad D_0045E8E0, D_0045E8F0, D_0045E900, D_0045E910;
}
