#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0016E6B0();
extern s32 D_0040F4D4;
extern s32 func_00135550();
extern void func_001354E0(void*, void*);
extern s32 func_0025C2C8();
extern s32 D_0040F4CC;
extern s32 func_0012A280();
extern s32 D_0040F4D0;
extern s32 func_00139838();
extern s32 func_00139980(void *);
extern s32 func_00135C50();
extern s32 func_0025CDF0(s32);
extern s32 func_0015C100(s32);

s32 func_00139060(s32 arg0, s32 arg1) {
    void *temp_3;

    func_0016E6B0(D_0040F4D4, arg1);
    if (func_00135550(arg1) != 0) {
        func_001354E0(arg1, 0);
    }
    if (M2C_FIELD(arg1, s32 *, 0xB4) != 0) {
        func_0025C2C8(D_0040F4CC, arg1);
    }
    func_0012A280(D_0040F4D0, arg1);
    func_00139838(arg0 + 0x7990, arg1);
    temp_3 = M2C_FIELD(arg1, void **, 0x10);
    return M2C_FIELD(temp_3, s32 (**)(s32), 0x24)(arg1 + M2C_FIELD(temp_3, s16 *, 0x20));
}

s32 func_001390F8(s32 arg0) {
    s32 temp_2;
    void *temp_4;

    temp_4 = arg0 + 0x79A0;
    if (M2C_FIELD(temp_4, s32 *, 4) == M2C_FIELD(temp_4, s32 *, 8)) {
        temp_2 = func_00139980(temp_4);
        if (temp_2 == 0) {
            return 0;
        }
        func_00135C50(temp_2);
        goto block_4;
    }
block_4:
    return func_0025CDF0(D_0040F4CC) != 0;
}

void func_00139150(s32 arg0, s32 arg1) {
    func_0015C100(arg1 + 0x280);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_139060", func_00139170);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_139060", func_00139190);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_139060", func_00139480);
