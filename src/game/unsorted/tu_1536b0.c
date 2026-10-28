#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00165AE0();
extern s32 func_00165AF8();
extern void func_00154530(s32);
extern s32 func_00165B98();

void func_001536B0(void) {

}

void func_001536B8(void *arg0) {
    func_00165AE0();
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
}

s32 func_001536E0(void *arg0) {
    func_00165AF8();
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    return 1;
}

void func_00153710(void *arg0) {
    func_00154530(M2C_FIELD(arg0, s32 *, 0x18));
}

s32 func_00153730(void* object) {
    func_00165B98(object);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_00153750);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_00153758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_00153B60);
extern void func_00153F78(void*);
extern void func_00154110(void*);
extern void func_001543C8(void*);
extern void func_001545D8(void*);
void func_00153EB0(void* self, f32 elapsed) {
    switch (M2C_FIELD(self, s32*, 0x94)) {
    case 1:
        M2C_FIELD(self, f32*, 0x134) += elapsed;
        M2C_FIELD(self, f32*, 0x138) += elapsed;
        func_00153F78(self);
        func_001545D8(self);
        break;
    case 2:
        M2C_FIELD(self, f32*, 0x134) += elapsed;
        M2C_FIELD(self, f32*, 0x138) += elapsed;
        func_00154110(self);
        func_001545D8(self);
        break;
    case 3:
        M2C_FIELD(self, f32*, 0x134) += elapsed;
        M2C_FIELD(self, f32*, 0x138) += elapsed;
        func_001543C8(self);
        func_001545D8(self);
        break;
    case 0:
    case 4:
    default:
        break;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_00153F78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_00154110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_001543C8);

void func_00154518(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x94) == 0) {
        M2C_FIELD(arg0, s32 *, 0x94) = 1;
    }
}

// UNVERIFIED: original object and virtual operation identities.
typedef struct { u8 unknown[0x10]; s16 adjustment; u16 unknown12; void (*finish)(void*, int); } Recovered_FinishVtable;
typedef struct { u8 unknown[0x10]; Recovered_FinishVtable* vtable; u8 unknown14[0x7C]; int kind; int state; } Recovered_FinishObject;
extern u8* D_0040F0E0;
void func_00154530(s32 object) {
    Recovered_FinishObject* self = (Recovered_FinishObject*)object;
    if (self->state != 4) {
        u8* stats;
        self->vtable->finish((u8*)self + self->vtable->adjustment, 0);
        stats = *(u8**)(D_0040F0E0 + 0x21070);
        switch (self->kind) {
        case 0: stats += 0xC; (*(u16*)(stats + 0x14))++; break;
        case 1: stats += 0xC; (*(u16*)(stats + 0x16))++; break;
        }
        self->state = 4;
        func_001545D8(self);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_001545D8);
// UNVERIFIED: original object and callback identities.
typedef struct { u8 unknown[0x20]; s16 adjustment; u16 unknown22; s32 (*check)(void*); } Recovered_ModeVtable;
typedef struct { u8 unknown[0x10]; Recovered_ModeVtable* vtable; } Recovered_ModeChild;
typedef struct { u8 unknown[0x18]; Recovered_ModeChild* child; u8 unknown1C[0x114]; u32 state; } Recovered_ModeOwner;
s32 func_00154640(Recovered_ModeOwner* self) {
    Recovered_ModeChild* child;
    func_00165B98(self);
    func_00153730((u8*)self + 0x70);
    child = self->child;
    if (!child->vtable->check((u8*)child + child->vtable->adjustment)) return 0;
    self->state = 0;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_00154698);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_001546A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_00154A10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_00154A70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_00154AE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1536b0", func_00154DD0);
