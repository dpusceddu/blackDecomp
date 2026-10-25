#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_0018BFE8();
extern s32 func_00181B08();
extern s32 func_00173FB8(s32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_001854B8);

void func_00185530(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x68) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_00185538);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_001855F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_001856B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_00185708);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_00185798);

void func_00185870(s32 *arg0) {
    u8 sp[24];
    func_0018BFE8(sp);
    func_00181B08(*arg0 + 0xEC0, sp);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_001858A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_00185A70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_00185B50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_00185B80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_00185BA8);

void func_00185C38(s32 arg0) {
    func_00173FB8(arg0 + 0x2C);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_00185C58);

#include "ps2/recovered_types.h"
extern s32 * func_00173640(f32 *, f32);
extern s32 func_00173690(f32 *);

s32 * func_00185CB0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 var_2;

    if (arg1 < 2) {
        var_2 = arg2 < 2;
        if (var_2 == 0) {
            var_2 = func_00173640((f32 *) ((s32 *) (((s8 *) arg0) + 0x114)), 1.0f);
        }
    } else {
        var_2 = arg2 < 2;
        if (var_2 != 0) {
            var_2 = func_00173690((f32 *) ((s32 *) (((s8 *) arg0) + 0x114)));
        }
    }
    return (s32 *) var_2;
}
