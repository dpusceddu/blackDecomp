#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0020DC20();
extern s32 func_0020DB90(s32 *, s32);
extern s32 func_0020DB90();
extern s32 func_0027C278(s32);
extern s32 func_00209F38();
extern s32 func_0020BC00();
extern void * D_0040F544;
extern s32 func_00209FF8();
extern s32 func_00275340();
extern s32 func_00275398();
extern s32 func_00275260();
extern s32 func_00275340(void *);
extern s32 func_00275398(s32, s32, void *);
extern s32 func_00209618(void *);
extern s32 func_00209760(void *);
extern s32 func_00209F98();
extern s32 func_00209EC8(s32, s32, s32);

void func_0020DC60(s32 *arg0, s32 arg1) {
    s32 temp_17;

    temp_17 = arg1 + 1;
    if (*arg0 < temp_17) {
        func_0020DC20();
        func_0020DB90(arg0, temp_17);
    }
}

s32 func_0020DCB0(s32 arg0) {
    M2C_FIELD(arg0, s16 **, 4) = NULL;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = -1;
    func_0020DB90(arg0, 0x10);
    *M2C_FIELD(arg0, s16 **, 4) = 0;
    return 1;
}

void func_0020DCF8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = func_0027C278(arg1);
    func_00209F38(func_0020BC00(D_0040F544, 3), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 4));
}

void func_0020DD48(void *arg0) {
    func_00209FF8(func_0020BC00(D_0040F544, 3), M2C_FIELD(arg0, s32 *, 8));
}

void func_0020DD88(void *arg0) {
    *M2C_FIELD(arg0, s16 **, 4) = 0;
}

void func_0020DD98(M2C_UNK *arg0, void *arg1) {
    u8 sp[512];
    s32 temp_16;
    s32 temp_17;

    temp_17 = func_00275340(M2C_FIELD(arg0, s32 *, 4));
    temp_16 = 0x100 - temp_17;
    func_00275398(sp, 0x100, M2C_FIELD(arg0, s32 *, 4));
    if (temp_16 > 0) {
        func_00275260(arg1, sp + (temp_17 * 2), temp_16);
    }
    func_0020DC60(arg0, temp_17 + temp_16);
    func_0020DE78(arg0, sp);
}

#ifdef NON_MATCHING
// Unmatched: buffer-growth receiver setup occupies a different call delay slot (2 instructions).
extern s32 func_0020DB58(void*, const char*);
void func_0020DE28(s32* self, const char* text) {
    func_0020DC60(self, func_0020DB58(self, text));
    func_00275260(text, M2C_FIELD(self, void**, 4), self[0]);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_20dc60", func_0020DE28);
#endif

void func_0020DE78(s32 *arg0, void *arg1) {
    func_0020DC60(arg0, func_00275340(arg1));
    func_00275398(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 0), arg1);
}

#ifdef NON_MATCHING
// Unmatched: native stack reservation and all argument-home offsets are 16 bytes larger (17 instructions).
extern s32* func_00369FB8(void*, s32, const char*, void*);

void func_0020DEC8(s32* self, const char* format, ...) {
    char buffer[256];
    /* MIPS EABI: unnamed GP arguments begin in the remaining eight-byte register homes. */
    char* args = (char*)__builtin_next_arg(format);
    s32 namedRegisters = __builtin_args_info(2);
    if (namedRegisters < 8) args -= (8 - namedRegisters) * 8;
    func_00369FB8(buffer, 256, format, args);
    func_0020DE28(self, buffer);
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_20dc60", func_0020DEC8);
#endif

s32 func_0020DF30(void) {
    func_0020DC20();
    return 1;
}

void func_0020DF50(void) {

}

void func_0020DF58(void) {

}

void func_0020DF60(void) {

}

void func_0020DF68(void) {
    func_00209618(D_0040F544 + 4);
}

void func_0020DF90(void) {
    func_00209760(D_0040F544 + 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_20dc60", func_0020DFB8);

void func_0020DFC8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_17;

    temp_17 = func_0027C278(arg1);
    func_00209F98(func_0020BC00(D_0040F544, 0), temp_17, arg2);
}

void func_0020E020(s32 arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = func_0027C278(arg1);
    func_00209FF8(func_0020BC00(D_0040F544, 0), temp_16);
}

void func_0020E068(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_16;

    temp_16 = func_0020BC00(D_0040F544, 2);
    func_00209EC8(temp_16, func_0027C278(arg1), arg2);
}

void func_0020E0C8(s32 arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = func_0020BC00(D_0040F544, 2);
    func_00209FF8(temp_16, func_0027C278(arg1));
}
