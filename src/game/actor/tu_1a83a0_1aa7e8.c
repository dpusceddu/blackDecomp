#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001AB1C0(s32, s32, M2C_UNK *, s32, M2C_UNK *, s32);
extern s32 func_00137AE0(s32);
extern M2C_UNK D_003F6DE8;
extern M2C_UNK D_003F6DF0;
extern M2C_UNK D_003F6DF8;
extern M2C_UNK D_003F6E00;
extern s32 func_001AB1C0();
extern s32 func_00137AE0();
extern M2C_UNK D_003F6E30;
extern s32 func_0035CBC0();
extern s32 func_0035C7A4();
extern s32 func_00345F28();

void func_001AA7E8(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6DE8, arg2);
}

void func_001AA848(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6DF0, arg2);
}

void func_001AA8A8(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6DE8, arg2);
}

void func_001AA908(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6DF8, arg2);
}

void func_001AA968(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6E00, arg2);
}

void func_001AA9C8(void) {

}

void func_001AA9D0(void) {

}


void func_001AAD90(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6E30, arg2);
}

void func_001AADF0(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), "S_750", arg2);
}

void func_001AAE50(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), "U_745", arg2);
}

void func_001AAEB0(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), "S_650", arg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AAF10);

#ifdef NON_MATCHING
// Unmatched: 0x1ab1c0: fallback branch layout and register lifetimes.
#include "ps2/prelude.h"
extern int func_00360838(const char *, const char *);
extern char *D_003BD13C, *D_003BD140, *D_003BD144;
extern char *func_001AB338(void *, char *, const char *, const char *, const char *, void *);
extern char *func_0035CBC0(char *, const char *);
extern char *func_0035C7A4(char *, const char *);
char *func_001AB1C0(void *actor, char *name, const char *prefix, const char *variant, const char *suffix, void *context) {
    int defaultPrefix = func_00360838(D_003BD13C, prefix) == 0;
    int defaultVariant = func_00360838(defaultPrefix ? D_003BD140 : D_003BD144, variant) == 0;
    char *result = func_001AB338(actor, name, prefix, variant, suffix, context);
    if (result) return result;
    if (!defaultVariant) {
        result = func_001AB338(actor, name, prefix, defaultPrefix ? D_003BD140 : D_003BD144, suffix, context);
        if (result) return result;
    }
    if (!defaultPrefix) {
        result = func_001AB338(actor, name, D_003BD13C, variant, suffix, context);
        if (result) return result;
    }
    func_0035CBC0(name, D_003BD13C);
    func_0035C7A4(name, D_003BD140);
    return func_0035C7A4(name, suffix);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AB1C0);
#endif

s32 func_001AB338(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5) {
    u8 sp[16];
    func_0035CBC0(arg1, arg2);
    func_0035C7A4(arg1, arg3);
    func_0035C7A4(arg1, arg4);
    return func_00345F28(arg1, M2C_FIELD(M2C_FIELD(arg5, void **, 0x330), s32 *, 0x54), sp) == 1;
}
