#include "include_asm.h"

#include "physics/startup_constants.h"

using namespace PhysicsStartup;
extern "C" {
extern StartupToken D_0040E988, D_0040E990;
extern ConstantQuad D_0045E9A0, D_0045E9B0, D_0045E9C0, D_0045E9D0;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040E988,8\n.extern D_0040E990,8");

extern "C" void func_00341520(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E988);
            func_00100258(&D_0040E990);
            VectorTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            VectorTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            VectorTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            VectorTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0045E9A0.value = qa;
            D_0045E9B0.value = qb;
            D_0045E9C0.value = qc;
            D_0045E9D0.value = qd;
        } else {
            func_00100260(&D_0040E990, 2);
            func_00100230(&D_0040E988, 2);
        }
    }
}

extern "C" void func_00341668() {}
// Used by TriangleVolume's shared operation table; method identity is unknown.
extern "C" int func_00341670() { return 1; }
extern "C" void func_00341678() { func_00341520(1, 65535); }
extern "C" void func_00341698() { func_00341520(0, 65535); }

extern "C" {
StartupToken D_0040E988 __attribute__((section(".sbss")));
StartupToken D_0040E990 __attribute__((section(".sbss")));
ConstantQuad D_0045E9A0, D_0045E9B0, D_0045E9C0, D_0045E9D0;
}
