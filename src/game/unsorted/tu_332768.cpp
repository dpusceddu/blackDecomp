#include "include_asm.h"

#include "physics/startup_constants.h"

using namespace PhysicsStartup;

namespace RecordViews {
// Only these five word accesses are established; class identity and field
// meanings are unknown.
struct FiveWordRecord {
    unsigned int word00, word04, word08, word0c, word10;
};
}
using namespace RecordViews;

extern "C" {
extern StartupToken D_0040E888, D_0040E890;
extern ConstantQuad D_0045CD30, D_0045CD40, D_0045CD50, D_0045CD60;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040E888,8\n.extern D_0040E890,8");

extern "C" void func_00332768(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E888);
            func_00100258(&D_0040E890);
            VectorTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            VectorTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            VectorTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            VectorTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0045CD30.value = qa;
            D_0045CD40.value = qb;
            D_0045CD50.value = qc;
            D_0045CD60.value = qd;
        } else {
            func_00100260(&D_0040E890, 2);
            func_00100230(&D_0040E888, 2);
        }
    }
}

extern "C" FiveWordRecord* func_003328B0(FiveWordRecord** holder,
    unsigned int word00, unsigned int word04, unsigned int word0c, unsigned int word08)
{
    FiveWordRecord* record = *holder;
    if (record != 0) {
        record->word00 = 0;
        record->word04 = 0;
        record->word08 = 0;
        record->word0c = 0;
        record->word10 = 0;
    }
    record->word00 = word00;
    record->word04 = word04;
    record->word0c = word0c;
    record->word08 = word08;
    return record;
}

extern "C" void func_003328E8() { func_00332768(1, 65535); }
extern "C" void func_00332908() { func_00332768(0, 65535); }

extern "C" {
StartupToken D_0040E888 __attribute__((section(".sbss")));
StartupToken D_0040E890 __attribute__((section(".sbss")));
ConstantQuad D_0045CD30, D_0045CD40, D_0045CD50, D_0045CD60;
}
