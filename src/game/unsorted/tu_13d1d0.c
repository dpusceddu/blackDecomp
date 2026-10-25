#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0013D4B8();
extern void func_0013D5F8();
extern s32 func_0018C260();
extern s32 func_0018C3C0();
extern s32 func_00181418();
extern s32 func_0017CAF8();
extern s32 func_0016AC08();
extern s32 func_0013EE28();
extern s32 func_0013EE38();
extern s32 func_001814E8();
extern s32 func_0013EE48();
extern s32 func_0018C368();
extern s32 func_00181560();
extern s32 func_0018D580();
extern s32 func_001796E0();
extern s32 D_0040F4D4;
extern s32 func_0017B220();
extern s32 func_0017BA00();
extern s32 func_0016DDE0();
extern s32 func_00138390();
extern s32 func_0018D9E8();
extern s32 func_00181AB0();
extern s32 func_0018DCE0();
extern s32 func_0018D4C8();
extern s32 func_00173168();
extern void func_00139060();
extern s32 D_0040F514;
extern s32 func_00176F00();
extern void func_0013D680();
extern s32 func_00180610();
extern s32 func_00183AA0();
extern s32 func_00188D08();
extern s32 func_00187F90();
extern s32 func_00182138();
extern s32 func_00185DA8();
extern s32 func_0018ADE0();
extern s32 func_0018D108();
extern s32 func_00183260();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_13d1d0", func_0013D1D0);

void func_0013D228(void *arg0) {
    void *temp_16;

    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0x7C), s32 *, 0x38C) ^ 2) != 0) {
        temp_16 = arg0 + 0x1DA0;
        func_0013D4B8();
        func_0013D5F8(arg0);
        func_0018C260(temp_16);
        if (func_0018C3C0(temp_16) != 0) {
            func_00181418(arg0 + 0xEC0);
            func_0017CAF8(arg0 + 0x650);
        }
        func_0016AC08(arg0 + 0x1F90);
        func_0013D588(arg0);
    }
}

s32 func_0013D2B0(void) {
    func_0013EE28();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_13d1d0", func_0013D2D0);

void func_0013D2D8(s32 arg0) {
    func_0013EE38();
    func_001814E8(arg0 + 0xEC0);
}

s32 func_0013D308(s32 arg0) {
    s32 temp_16;

    temp_16 = arg0;
    func_0013EE48(arg0);
    func_0018C368(temp_16 + 0x1DA0);
    func_00181560(temp_16 + 0xEC0);
    func_0018D580(temp_16 + 0xD10);
    func_001796E0(D_0040F4D4, temp_16);
    func_0017B220(D_0040F4D4 + 0x1150, temp_16);
    func_0017BA00(D_0040F4D4 + 0x1290, temp_16);
    return func_0016DDE0(D_0040F4D4, temp_16);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_13d1d0", func_0013D388);

s32 func_0013D3F0(void *arg0) {
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x7C), void **, 0x34C), s32 *, 0x18);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_13d1d0", func_0013D400);

void func_0013D430(void *arg0, s32 arg1) {
    s32 temp_18;
    void *temp_2;

    temp_18 = arg0 + 0xC94;
    temp_2 = M2C_FIELD(arg0, void **, 0x7C);
    M2C_FIELD(temp_2, s32 *, 0x39C) = arg1;
    func_00138390(M2C_FIELD(temp_2, s32 *, 0x328), temp_2 + 0x3B9, arg1);
    func_0018D9E8(temp_18, arg1);
    func_00181AB0(arg0 + 0xEC0, func_0018DCE0(temp_18));
    func_0018D4C8(arg0 + 0xD10);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_13d1d0", func_0013D4B8);

void func_0013D588(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x1FC0) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void ***, 0x7C), s32 *, 0x3A4) == 0) {
            func_00173168(D_0040F4D4 + 0x22800, arg0);
        }
        func_00139060(D_0040F514, M2C_FIELD(arg0, void ***, 0x7C));
        M2C_FIELD(arg0, u8 *, 0x1FC0) = 0U;
    }
}

void func_0013D5F8(void *arg0) {
    if (func_00176F00(arg0 + 0x1FCC) & 0xFF) {
        func_0013D680(arg0);
    }
    func_00180610(arg0 + 0xB30);
    func_00183AA0(arg0 + 0x6F0);
    func_00188D08(arg0 + 0x150);
    func_00187F90(arg0 + 0x290);
    func_00182138(arg0 + 0x810);
    func_00185DA8(arg0 + 0x90);
    func_0018ADE0(arg0 + 0xCC0);
    func_0018D108(arg0 + 0xD10);
    func_00183260(arg0 + 0x1EB0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_13d1d0", func_0013D680);
