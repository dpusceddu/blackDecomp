#include "physics/startup_constants.h"
// SN requires the sized extern before this initializer to select its GP form.
__asm__(".extern D_0040E948,8\n.extern D_0040E950,8");

using namespace PhysicsStartup;

extern "C" {
extern StartupToken D_0040E948, D_0040E950;
extern ConstantQuad D_0045E8A0, D_0045E8B0, D_0045E8C0, D_0045E8D0;
void* func_00100228(StartupToken*);
void* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}

extern "C" void func_0033BA90(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E948);
            func_00100258(&D_0040E950);
            VectorTemporary first(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 firstValue = first;
            VectorTemporary second(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 secondValue = second;
            VectorTemporary third(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 thirdValue = third;
            VectorTemporary fourth(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 fourthValue = fourth;
            D_0045E8A0.value = firstValue;
            D_0045E8B0.value = secondValue;
            D_0045E8C0.value = thirdValue;
            D_0045E8D0.value = fourthValue;
        } else {
            func_00100260(&D_0040E950, 2);
            func_00100230(&D_0040E948, 2);
        }
    }
}

extern "C" int func_0033BBD8() { return 0; }
extern "C" int func_0033BBE0() { return 0; }
extern "C" void func_0033BBE8() { func_0033BA90(1, 65535); }
extern "C" void func_0033BC08() { func_0033BA90(0, 65535); }

extern "C" {
StartupToken D_0040E948 __attribute__((section(".sbss")));
StartupToken D_0040E950 __attribute__((section(".sbss")));
ConstantQuad D_0045E8A0;
ConstantQuad D_0045E8B0;
ConstantQuad D_0045E8C0;
ConstantQuad D_0045E8D0;
}
