#include "include_asm.h"

#include "physics/relocation.hpp"
#include "physics/startup_constants.h"

using namespace PhysicsStartup;
extern "C" {
extern StartupToken D_0040E938, D_0040E940;
extern ConstantQuad D_0045E860, D_0045E870, D_0045E880, D_0045E890;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040E938,8\n.extern D_0040E940,8");

extern "C" void func_0033B708(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E938);
            func_00100258(&D_0040E940);
            VectorTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            VectorTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            VectorTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            VectorTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0045E860.value = qa;
            D_0045E870.value = qb;
            D_0045E880.value = qc;
            D_0045E890.value = qd;
        } else {
            func_00100260(&D_0040E940, 2);
            func_00100230(&D_0040E938, 2);
        }
    }
}

int PhysicsRelocatedHandle::Relocate(const PhysicsRelocationContext* context)
{
    data += (unsigned)this - (unsigned)context->originalBase;
    func_00341B48((char*)this + 0x10, context);
    return 1;
}

extern "C" void func_0033B890() { func_0033B708(1, 65535); }
extern "C" void func_0033B8B0() { func_0033B708(0, 65535); }

extern "C" {
StartupToken D_0040E938 __attribute__((section(".sbss")));
StartupToken D_0040E940 __attribute__((section(".sbss")));
ConstantQuad D_0045E860, D_0045E870, D_0045E880, D_0045E890;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033B850);
