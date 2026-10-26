#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00335DB8(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_335db8", func_00335DB8);

void func_00335F00(void *arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0x3C);
    M2C_FIELD(arg0, s128 *, 0) = (s128) M2C_FIELD(temp_5, s128 *, 0x10);
    M2C_FIELD(arg0, s128 *, 0x10) = (s128) M2C_FIELD(temp_5, s128 *, 0x20);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_335db8", func_00335F18);
#ifdef NON_MATCHING
/* Partial views; field meanings and complete extents are UNVERIFIED. */
typedef struct {
    int unk_00;
} Recovered_PhysicsRelocatedHandle;
typedef struct {
    char unk_00[8];
    int base;
} Recovered_PhysicsRelocationContext;
typedef struct {
    char unk_00[0x20];
    void* table;
    char unk_24[0x10];
    u32 unk_34, unk_38;
    Recovered_PhysicsRelocatedHandle* handle;
    u32 unk_40;
} Recovered_PhysicsRelocatedObject;
extern int func_00341808(void);
extern int func_0033B858(Recovered_PhysicsRelocatedHandle*, Recovered_PhysicsRelocationContext*);
extern int D_003D12F8;
// Unmatched: branch layout and relocation temporary lifetimes differ.
int func_00335F20(Recovered_PhysicsRelocatedObject* object, Recovered_PhysicsRelocationContext* context) {
    if (func_00341808() != 0) {
        int delta = (int)object - context->base;
        Recovered_PhysicsRelocatedHandle* handle = (Recovered_PhysicsRelocatedHandle*)((char*)object->handle + delta);
        object->unk_34 += delta;
        object->unk_38 += delta;
        object->unk_40 += delta;
        object->handle = handle;
        func_0033B858(handle, context);
        object->table = &D_003D12F8;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_335db8", func_00335F20);
#endif

void func_00335FB0(void) {
    func_00335DB8(1, 0xFFFF);
}

void func_00335FD0(void) {
    func_00335DB8(0, 0xFFFF);
}
