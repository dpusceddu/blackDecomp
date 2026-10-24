#include "physics/startup_constants.h"

using namespace PhysicsStartup;
extern "C" {
extern StartupToken D_0040EAC8, D_0040EAD0;
extern ConstantQuad D_0048EF30, D_0048EF40, D_0048EF50, D_0048EF60;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040EAC8,8\n.extern D_0040EAD0,8");

extern "C" void func_00382130(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040EAC8);
            func_00100258(&D_0040EAD0);
            VectorTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            VectorTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            VectorTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            VectorTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0048EF30.value = qa;
            D_0048EF40.value = qb;
            D_0048EF50.value = qc;
            D_0048EF60.value = qd;
        } else {
            func_00100260(&D_0040EAD0, 2);
            func_00100230(&D_0040EAC8, 2);
        }
    }
}

extern "C" void func_00382278() { func_00382130(1, 65535); }
extern "C" void func_00382298() { func_00382130(0, 65535); }

extern "C" {
StartupToken D_0040EAC8 __attribute__((section(".sbss")));
StartupToken D_0040EAD0 __attribute__((section(".sbss")));
ConstantQuad D_0048EF30, D_0048EF40, D_0048EF50, D_0048EF60;
}
