#include "include_asm.h"

namespace NearestPointRecovery {
// Scoped PS2 access views; unused fields and original class identities remain UNVERIFIED.
struct IndexView { int value; };
struct PointView {
    virtual void Slot0();
    virtual IndexView* GetIndex();
};
struct PointSlotsPrefix {
    void* vtable;
    PointView* slots[8];
};
typedef void (*ErasedVirtualFunction)();
struct VirtualEntry {
    short thisAdjustment;
    unsigned short reserved;
    ErasedVirtualFunction function;
};
struct __attribute__((aligned(8))) GlobalWord { unsigned int value; };
struct __attribute__((aligned(8))) RegistrationStorage {
    unsigned char unverified00[0x110];
    VirtualEntry* classTable;
};
}
using namespace NearestPointRecovery;

extern "C" {
void* func_0038E108(void*, const char*, int, int, int, int);
void* func_0038E438(void*, const char*, int, int, int, int);
void func_0038E3C0();
void func_0038E390();
void func_0038E350();
void func_0038E5C8();
void func_0038E300();
void func_0038E2D0();
void func_003893B0();
void func_0038E298();
void func_002904E8();
extern int D_003E6428;
extern GlobalWord D_003EA768, D_003EA770;
extern VirtualEntry D_003EA778[3], D_003EA790[3], D_003EA7A8[3], D_003EA7C0[5];
extern RegistrationStorage D_004513D8;
extern const char D_00406A00[];
const char D_00406A00[40] __attribute__((aligned(8))) =
    "CNearestPoint" "\000\000\000" "Q24Kaim13CPointWrapper" "\000";

void func_002E72F0(int enabled, int phase)
{
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_0038E108(&D_004513D8, D_00406A00, 0, 0, 0, 0);
            D_004513D8.classTable = D_003EA778;
            return;
        }
        D_004513D8.classTable = D_003EA790;
    }
}

PointSlotsPrefix* func_002E7360(PointSlotsPrefix* self)
{
    PointView** slot;
    unsigned int index;
    index = 0;
    slot = self->slots;
    self->vtable = D_003EA7C0;
    do {
        *slot = 0;
        ++index;
        ++slot;
    } while (index < 8U);
    return self;
}

PointView* func_002E7398(PointSlotsPrefix* owner, const int* index)
{
    owner = (PointSlotsPrefix*)((char*)owner + *index * 4);
    return owner->slots[0];
}

// A void return and an IndexView* return emit the same body; the return contract remains UNVERIFIED.
void func_002E73B0(PointSlotsPrefix* owner, PointView* point)
{
    IndexView* index = point->GetIndex();
    owner->slots[index->value] = point;
}

void* func_002E7400(void* self, const char* name, int first, int second)
{
    func_0038E438(self, name, first, second, 0, 0);
    ((RegistrationStorage*)self)->classTable = D_003EA7A8;
    return self;
}

void* func_002E7440(void* self, const char* name, int first, int second)
{
    func_0038E108(self, name, first, second, 0, 0);
    ((RegistrationStorage*)self)->classTable = D_003EA778;
    return self;
}

void func_002E7480() { D_003E6428 = 0; }
void func_002E7490() { D_003EA768.value = 0; }

// Keep these definitions here: the section switch closes the preceding leaf's
// unwind extent before alignment for the static initialization stubs.
#define NEAREST_DATA __attribute__((section(".data.nearest_point"), aligned(8)))
GlobalWord D_003EA768 NEAREST_DATA = {0};
GlobalWord D_003EA770 NEAREST_DATA = {1};
VirtualEntry D_003EA778[3] NEAREST_DATA = {
    {0, 0, func_0038E3C0}, {0, 0, func_0038E390}, {0, 0, 0}
};
VirtualEntry D_003EA790[3] NEAREST_DATA = {
    {0, 0, func_0038E350}, {0, 0, func_0038E5C8}, {0, 0, 0}
};
VirtualEntry D_003EA7A8[3] NEAREST_DATA = {
    {0, 0, func_0038E300}, {0, 0, func_0038E2D0}, {0, 0, 0}
};
VirtualEntry D_003EA7C0[5] NEAREST_DATA = {
    {0, 0, func_003893B0}, {0, 0, func_0038E298},
    {0, 0, func_002904E8}, {0, 0, func_002904E8}, {0, 0, 0}
};
#undef NEAREST_DATA

void func_002E74A0() { func_002E72F0(1, 0xFFFF); }
void func_002E74C0() { func_002E72F0(0, 0xFFFF); }
RegistrationStorage D_004513D8 __attribute__((aligned(8)));
}
