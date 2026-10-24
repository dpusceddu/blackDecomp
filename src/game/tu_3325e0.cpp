#include "physics/startup_constants.h"

using namespace PhysicsStartup;
extern "C" {
extern StartupToken D_0040E878, D_0040E880;
extern ConstantQuad D_0045CCF0, D_0045CD00, D_0045CD10, D_0045CD20;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040E878,8\n.extern D_0040E880,8");

extern "C" void func_003325E0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E878);
            func_00100258(&D_0040E880);
            VectorTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            VectorTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            VectorTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            VectorTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0045CCF0.value = qa;
            D_0045CD00.value = qb;
            D_0045CD10.value = qc;
            D_0045CD20.value = qd;
        } else {
            func_00100260(&D_0040E880, 2);
            func_00100230(&D_0040E878, 2);
        }
    }
}

extern "C" void func_00332728() { func_003325E0(1, 65535); }
extern "C" void func_00332748() { func_003325E0(0, 65535); }

extern "C" {
StartupToken D_0040E878 __attribute__((section(".sbss")));
StartupToken D_0040E880 __attribute__((section(".sbss")));
ConstantQuad D_0045CCF0, D_0045CD00, D_0045CD10, D_0045CD20;
}
