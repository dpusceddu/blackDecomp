#include "ps2/ee_types.h"

namespace CompoundRecovery {
// Layouts cover only accesses supported by the PS2 bodies. Xbox compound.cpp
// supplies the Wake/Sleep algorithms and provisional class/field names.
struct Body;
struct Solver {
    void WakeBody(Body*) __asm__("func_0037CF60");
    void SleepBody(Body*) __asm__("func_0037CFD0");
};
struct Body {
    unsigned char unknown00[0x4c];
    Solver* solver;
    unsigned char unknown50[0x3c];
    unsigned int state;
    unsigned char unknown90[0x1c];
    unsigned int quietFrames;
};
struct Instance {
    unsigned char unknown00[0x58];
    Body* body;
    unsigned char unknown5c[0x14];
};
struct Compound {
    unsigned int unknown00[2];
    unsigned int instanceCount;
    Instance* instances;
};
struct StorageBlock {
    void* memory;
    unsigned int unknown04;
};
// Constructors/destructors do not access fields. The retail labels support only
// this aligned storage extent; the startup objects' identities are unknown.
struct StartupToken {} __attribute__((aligned(8)));
// Only XYZ are initialized by the retail helper; the fourth lane is transported
// from its stack temporary without an assigned semantic value.
struct ConstantQuad {
    float x, y, z, unspecifiedW;
    void Store(EeS128 value) { *(EeS128*)this = value; }
} __attribute__((aligned(16)));
struct ConstantTemporary {
    volatile float x, y, z, unspecifiedW;
    ConstantTemporary(float a, float b, float c) : x(a), y(b), z(c) {}
    operator EeS128() const { return *(const volatile EeS128*)this; }
} __attribute__((aligned(16)));
}
using namespace CompoundRecovery;

extern "C" void* func_0032AD30(StorageBlock*, const void*);
extern "C" {
extern StartupToken D_0040E828, D_0040E830;
extern ConstantQuad D_0045CBB0, D_0045CBC0, D_0045CBD0, D_0045CBE0;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040E828,8\n.extern D_0040E830,8");

extern "C" void func_0032B598(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E828);
            func_00100258(&D_0040E830);
            // Volatile XYZ writes and a native volatile 128-bit read preserve
            // each temporary's unassigned fourth lane and its copy lifetime.
            ConstantTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            ConstantTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            ConstantTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            ConstantTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0045CBB0.Store(qa);
            D_0045CBC0.Store(qb);
            D_0045CBD0.Store(qc);
            D_0045CBE0.Store(qd);
        } else {
            func_00100260(&D_0040E830, 2);
            func_00100230(&D_0040E828, 2);
        }
    }
}

extern "C" void* func_0032B6E0(void* memory, const void* definition)
{
    StorageBlock block;
    block.memory = memory;
    return func_0032AD30(&block, definition);
}

extern "C" void func_0032B700(Compound* compound)
{
    for (unsigned int i = 0; i < compound->instanceCount; ++i) {
        Instance* instance = &compound->instances[i];
        Body* body = instance->body;
        if ((body->state & 7) != 4)
            body->solver->WakeBody(body);
        instance->body->quietFrames = 0;
    }
}

extern "C" void func_0032B798(Compound* compound)
{
    for (unsigned int i = 0; i < compound->instanceCount; ++i) {
        Instance* instance = &compound->instances[i];
        if ((instance->body->state & 7) != 2)
            instance->body->solver->SleepBody(instance->body);
    }
}

extern "C" void func_0032B820() { func_0032B598(1, 65535); }
extern "C" void func_0032B840() { func_0032B598(0, 65535); }

extern "C" {
StartupToken D_0040E828 __attribute__((section(".sbss")));
StartupToken D_0040E830 __attribute__((section(".sbss")));
ConstantQuad D_0045CBB0;
ConstantQuad D_0045CBC0;
ConstantQuad D_0045CBD0;
ConstantQuad D_0045CBE0;
}
