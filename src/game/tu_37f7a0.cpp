#include "physics/startup_constants.h"

using namespace PhysicsStartup;
extern "C" {
extern StartupToken D_0040EA98, D_0040EAA0;
extern ConstantQuad D_0048EE70, D_0048EE80, D_0048EE90, D_0048EEA0;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040EA98,8\n.extern D_0040EAA0,8");

extern "C" void func_0037F7A0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040EA98);
            func_00100258(&D_0040EAA0);
            VectorTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            VectorTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            VectorTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            VectorTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0048EE70.value = qa;
            D_0048EE80.value = qb;
            D_0048EE90.value = qc;
            D_0048EEA0.value = qd;
        } else {
            func_00100260(&D_0040EAA0, 2);
            func_00100230(&D_0040EA98, 2);
        }
    }
}

extern "C" void func_0037F8E8() { func_0037F7A0(1, 65535); }
extern "C" void func_0037F908() { func_0037F7A0(0, 65535); }

extern "C" {
StartupToken D_0040EA98 __attribute__((section(".sbss")));
StartupToken D_0040EAA0 __attribute__((section(".sbss")));
ConstantQuad D_0048EE70, D_0048EE80, D_0048EE90, D_0048EEA0;
}
