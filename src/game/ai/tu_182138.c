#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00182158();
extern s32 func_0017E5A8(s32);
extern s32 func_001829A8();
extern s32 func_00182550();

s32 func_00182138(s32 arg0) {
    M2C_FIELD(arg0, s8 *, 0x36) = 0;
    return func_00182158(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182270);

void func_00182318(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x34) = arg1;
}

#include "ps2/recovered_types.h"
extern s32 func_00182608(void *, s128, s32, f32);
extern f32 func_0018DA40(void *);

s32 func_00182320(void *arg0, s128 arg1, s32 arg2) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x310), s8 *, 0x6D4) = 0;
    return func_00182608(arg0, arg1, arg2, func_0018DA40(M2C_FIELD(arg0, void **, 0x310) + 0xC94));
}

#include "ps2/recovered_types.h"
extern s32 func_00182608(void *, s128, s32, f32);
extern f32 func_0018DA88(void *);

s32 func_00182380(void *arg0, s128 arg1, s32 arg2) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x310), s8 *, 0x6D4) = 0;
    return func_00182608(arg0, arg1, arg2, 1.55f);
}

s32 func_001823B0(void *arg0, s128 arg1, s32 arg2) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x310), s8 *, 0x6D4) = 0;
    return func_00182608(arg0, arg1, arg2, func_0018DA88(M2C_FIELD(arg0, void **, 0x310) + 0xC94));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182508);

s32 func_00182510(void *arg0) {
    func_0017E5A8(M2C_FIELD(arg0, s32 *, 0x310) + 0x650);
    M2C_FIELD(arg0, s8 *, 0x37) = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182550);

void func_001825B0(void *arg0) {
    if (func_001829A8(arg0) != 0) {
        func_00182550(arg0, 0);
    } else {
        func_00182550(arg0, M2C_FIELD(arg0, s32 *, 0x30));
    }
    func_00182318(arg0, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001828C0);

s32 func_00182960(s32 arg0) {
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182968);

s32 func_001829A0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x30);
}
