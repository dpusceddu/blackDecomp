#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0011E1B8();

s32 func_0011E2E0(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));
    return func_0011E1B8(arg0, (s32) sp);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358_11e2e0", func_0011E300);
extern void* func_0011D498(void*);
extern s64 func_001A7DF0(void*, s32, s32);
extern void func_001412E8(void*, s32);
extern void func_0011DE40(s32*);
extern s32 func_0011E240(s32*, void*);

void func_0011E3A8(void* self, s32 arg1) {
    void* temp_2;

    temp_2 = func_0011D498(self);
    if (func_001A7DF0(M2C_FIELD(temp_2, void**, 0x330), 0, 7) == 2) {
        if (arg1 != 0) { func_001412E8((void*)M2C_FIELD(self, s32*, 0), 8); }
        M2C_FIELD(self, s8*, 0x48) = 1;
        return;
    }
    if (arg1 != 0) {
        if (M2C_FIELD(temp_2, u8*, 0x3B1) != 0) {
            func_001412E8((void*)M2C_FIELD(self, s32*, 0), 8);
            return;
        }
        func_0011DE40(self);
        if ((M2C_FIELD(self, u8*, 5) != 0) ||
            ((M2C_FIELD(self, u8*, 4) != 0) && (func_0011E240(self, (s32*)(((s8*)self) + 0x10)) == 0))) {
            func_001412E8((void*)M2C_FIELD(self, s32*, 0), 8);
        }
    }
}
