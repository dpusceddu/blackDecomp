#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001F1C08();
extern s32 func_00275260(void *, s32, M2C_UNK);
extern void * D_003BDC88;
extern void * D_003BDC8C;

void func_001FDBF8(void *arg0) {
    func_001F1C08();
    func_00275260(D_003BDC88, arg0 + 0x18, 4);
    func_00275260(D_003BDC8C, arg0 + 0x20, 4);
    M2C_FIELD(arg0, s32 *, 0x70) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdbf8", func_001FDC48);
