#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00179258(s32, s32);
extern s32 D_0040F4D4;
extern s32 func_001A2C70();
extern void func_001A2CF0();

void func_001A2620(void *arg0) {
    func_00179258(D_0040F4D4 + 0xFA8, M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 *, 0x298));
}

void func_001A2650(void *arg0, s32 arg1) {
    if (arg1 == 1) {
        func_001A2C70();
        M2C_FIELD(arg0, s32 *, 0x50) = arg1;
    }
}

void func_001A2690(void) {

}

void func_001A2698(s32 arg0, s32 arg1) {
    if (arg1 == 1) {
        func_001A2CF0();
    }
}



void func_001A26C0(void* self) {
    s32 phase;
    void* afterMethods;
    void* beforeMethods;

    beforeMethods = M2C_FIELD(self, void**, 0x60);
    M2C_FIELD(beforeMethods, void (**)(void*, s32), 0x54)((void*)(((s8*)self) + M2C_FIELD(beforeMethods, s16*, 0x50)),
                                                          M2C_FIELD(self, s32*, 0x54));
    phase = M2C_FIELD(self, s32*, 0x54);
    switch (phase) { /* irregular */
        case 0: M2C_FIELD(self, s32*, 0x54) = 1; break;
        case 2: M2C_FIELD(self, s32*, 0x54) = 0; break;
        case 1: M2C_FIELD(self, s32*, 0x54) = 2; break;
    }
    afterMethods = M2C_FIELD(self, void**, 0x60);
    M2C_FIELD(afterMethods, void (**)(void*, s32), 0x44)((void*)(((s8*)self) + M2C_FIELD(afterMethods, s16*, 0x40)),
                                                         M2C_FIELD(self, s32*, 0x54));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a2620", func_001A2750);
