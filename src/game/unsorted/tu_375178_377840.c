#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_003753E0();
extern s32 func_003778D8();
extern s32 func_00377968();
extern s32 func_0031D268(void *, M2C_UNK, M2C_UNK);
extern s32 func_0037B1D0();
extern s32 func_0037B220(s32);

void func_00377840(void) {
    func_003753E0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377860);

void func_00377868(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14C) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), s32 *, 0x10) + (func_003778D8() << 5));
}

void func_003778A0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14C) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), s32 *, 0x10) + (func_00377968() << 5));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_003778D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377968);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377A10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377A20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377BD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377BE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377C28);

void * func_00377C80(void *arg0, s32 arg1, s16 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s16 *, 4) = arg2;
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s16 *, 8) = 0;
    M2C_FIELD(arg0, s16 *, 0xA) = 0;
    return (func_0031D268(arg0 + 0xC, 1, 1) == 0) ? NULL : arg0;
}


s32 func_00378698(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x340) = 0;
    return (func_0037B1D0(arg0 + 0x104, arg1, 0xBB80, M2C_FIELD(arg2, s32 *, 0), M2C_FIELD(arg2, s32 *, 4), M2C_FIELD(arg2, s32 *, 8)) == 0) ? 0 : arg0;
}


s32 func_00378740(s32 arg0) {
    func_0037B220(arg0 + 0x104);
    return arg0;
}
