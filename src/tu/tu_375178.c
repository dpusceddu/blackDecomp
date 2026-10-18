/* Translation unit tu_375178 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_003753E0();
extern s32 func_003778D8();
extern s32 func_00377968();
extern s32 func_0031D268(void *, M2C_UNK, M2C_UNK);
extern s32 func_0037B1D0();
extern s32 func_0037B220(s32);

void func_00377840(void) {
    func_003753E0();
}

/* Assembly between the functions: func_00377860 (8 bytes) */

void func_00377868(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14C) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), s32 *, 0x10) + (func_003778D8() << 5));
}

void func_003778A0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14C) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), s32 *, 0x10) + (func_00377968() << 5));
}

/* Assembly between the functions: func_003778D8 (144 bytes), func_00377968 (168 bytes), func_00377A10 (16 bytes), func_00377A20 (168 bytes), func_00377AC8 (272 bytes), func_00377BD8 (8 bytes), func_00377BE0 (72 bytes), func_00377C28 (88 bytes) */

void * func_00377C80(void *arg0, s32 arg1, s16 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s16 *, 4) = arg2;
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s16 *, 8) = 0;
    M2C_FIELD(arg0, s16 *, 0xA) = 0;
    return (func_0031D268(arg0 + 0xC, 1, 1) == 0) ? NULL : arg0;
}

/* Assembly between the functions: func_00377CD0 (32 bytes), func_00377CF0 (288 bytes), func_00377E10 (240 bytes), func_00377F00 (96 bytes), func_00377F60 (440 bytes), func_00378118 (464 bytes), func_003782E8 (536 bytes), func_00378500 (112 bytes), func_00378570 (56 bytes), func_003785A8 (192 bytes), func_00378668 (48 bytes) */

s32 func_00378698(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x340) = 0;
    return (func_0037B1D0(arg0 + 0x104, arg1, 0xBB80, M2C_FIELD(arg2, s32 *, 0), M2C_FIELD(arg2, s32 *, 4), M2C_FIELD(arg2, s32 *, 8)) == 0) ? 0 : arg0;
}

/* Assembly between the functions: func_003786E0 (96 bytes) */

s32 func_00378740(s32 arg0) {
    func_0037B220(arg0 + 0x104);
    return arg0;
}
