#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00193980();
extern s32 func_00193B98();
extern void func_0019B0C0(RecoveredAIActionHeader*);
extern s32 func_00188F10(void*);
extern s32 func_00193A60(RecoveredAIActionHeader*, s32, f32);
extern s32 func_00193988();

void func_0019AE08(s32 arg0) {
    func_00193980();
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x44) = 0.5f;
    M2C_FIELD(func_00193B98(arg0), s32 *, 0x4C) = 0;
    M2C_FIELD(func_00193B98(arg0), s32 *, 0x50) = 0;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x40) = 2.0f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x3C) = 0.5f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x68) = 0.25f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x64) = 2.0f;
    M2C_FIELD(func_00193B98(arg0), s32 *, 0x6C) = 0;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x60) = 0.1f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x5C) = 10.0f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 8) = -10.0f;
    M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), s8 *, 0x104) = 1;
    M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), s8 *, 0x110) = 1;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), void **, 0x694), s8 *, 0x35) = 1;
    func_0019B0C0((RecoveredAIActionHeader*)arg0);
}

void func_0019AF20(void) {
    func_00193988();
}

void func_0019AF40(RecoveredAIActionHeader* self, s32 event, s32 value) {
    switch (event) {
    case 0x23:
        if (value) {
            func_00193A28(self, 0x16, 0);
            return;
        }
        func_00193A60(self, 0, 10.0f);
        /* fall through */
    case 0x16:
    case 8:
        func_0019B0C0(self);
        return;
    case 0x24:
        if (value) func_00193A28(self, 0x16, 0);
        else func_0019B0C0(self);
        return;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19ae08", func_0019AFF0);
void func_0019B0C0(RecoveredAIActionHeader* self) {
    if (func_00188F10((u8*)self->brain + 0x150)) {
        if (func_00193AF8(self)) {
            func_00193A28(self, 0x23, 0);
        } else {
            func_00193A28(self, 0x24, 0);
        }
    } else {
        func_00193A28(self, 0x16, 0);
    }
}

void func_0019B130(RecoveredAIActionHeader* self) {
    func_0019B0C0(self);
}
