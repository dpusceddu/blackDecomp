#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00133ED8();
extern s32 func_00133FA0();
extern s32 func_0013F328(s32);
extern s32 func_001306A0();
extern void func_0013F0A8(void *arg0);
extern void func_0013DB40(void *arg0);
extern s32 func_0013F3E0();
extern s32 func_001306D0();
extern s32 func_0013F0D8();
extern s32 func_0013DBA0();
extern s32 D_0040F4D0;
extern s32 func_00140008(s32);
extern s32 func_00131078();
extern s32 func_0013F298(s32);
extern s32 func_0013DEF0(void *arg0);
extern s32 func_00140048(s32);
extern s32 func_001310B8();
extern s32 func_0013F2C8(s32);
extern void func_0013DF38(s32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_139bb0", func_00139BB0);

void func_00139C58(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xBC) = (s32) M2C_FIELD(arg0, s32 *, 0xB8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_139bb0", func_00139C68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_139bb0", func_0013A300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_139bb0", func_0013A640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_139bb0", func_0013A6E8);

void func_0013B4A0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    f32 temp_f0;

    temp_f0 = M2C_FIELD(arg0, f32 *, 0x4C4);
    M2C_FIELD(arg0, f32 *, 0x4C8) = fparg2;
    M2C_FIELD(arg0, f32 *, 0x4C4) = (f32) (temp_f0 + ((fparg0 - temp_f0) * fparg1));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_139bb0", func_0013B4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_139bb0", func_0013B628);

s32 func_0013B9A0(s32 arg0) {
    func_0013BAF8();
    func_00133ED8(arg0);
    return 1;
}

void func_0013B9D0(s32 arg0) {
    func_0013BB38();
    func_00133FA0(arg0);
}

void func_0013BA00(s32 arg0) {
    func_0013F328(arg0 + 0x4F0);
    func_001306A0(arg0 + 0x620);
    func_0013F0A8(arg0 + 0x730);
    func_0013DB40(arg0 + 0x7D0);
}

s32 func_0013BA40(s32 arg0) {
    if ((func_0013F3E0(arg0 + 0x4F0, (s32) M2C_FIELD(arg0, s8 *, 0x418), arg0) != 0) && (func_001306D0(arg0 + 0x620, arg0, (s32) M2C_FIELD(arg0, s8 *, 0x418)) != 0) && (func_0013F0D8(arg0 + 0x730, (s32) M2C_FIELD(arg0, s8 *, 0x418), arg0) != 0) && (func_0013DBA0(arg0 + 0x7D0, arg0) != 0)) {
        M2C_FIELD(arg0, f32 *, 0x8AC) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_139bb0", func_0013BAC8);

void func_0013BAF8(s32 arg0) {
    func_00140008(arg0 + 0x4F0);
    func_00131078(arg0 + 0x620);
    func_0013F298(arg0 + 0x730);
    func_0013DEF0(arg0 + 0x7D0);
}

void func_0013BB38(s32 arg0) {
    func_00140048(arg0 + 0x4F0);
    func_001310B8(arg0 + 0x620);
    func_0013F2C8(arg0 + 0x730);
    func_0013DF38(arg0 + 0x7D0);
}
