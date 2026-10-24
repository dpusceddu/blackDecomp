#include "physics/startup_constants.h"
// SN requires the sized extern before this initializer to select its GP form.
__asm__(".extern D_0040E9C8,8\n.extern D_0040E9D0,8");

using namespace PhysicsStartup;

extern "C" {
extern StartupToken D_0040E9C8, D_0040E9D0;
extern ConstantQuad D_0045EAA0, D_0045EAB0, D_0045EAC0, D_0045EAD0;
void* func_00100228(StartupToken*);
void* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}

extern "C" void func_00341B98(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E9C8);
            func_00100258(&D_0040E9D0);
            VectorTemporary first(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 firstValue = first;
            VectorTemporary second(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 secondValue = second;
            VectorTemporary third(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 thirdValue = third;
            VectorTemporary fourth(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 fourthValue = fourth;
            D_0045EAA0.value = firstValue;
            D_0045EAB0.value = secondValue;
            D_0045EAC0.value = thirdValue;
            D_0045EAD0.value = fourthValue;
        } else {
            func_00100260(&D_0040E9D0, 2);
            func_00100230(&D_0040E9C8, 2);
        }
    }
}

extern "C" void func_00341CE0() { func_00341B98(1, 65535); }
extern "C" void func_00341D00() { func_00341B98(0, 65535); }

extern "C" {
StartupToken D_0040E9C8 __attribute__((section(".sbss")));
StartupToken D_0040E9D0 __attribute__((section(".sbss")));
ConstantQuad D_0045EAA0;
ConstantQuad D_0045EAB0;
ConstantQuad D_0045EAC0;
ConstantQuad D_0045EAD0;
}
