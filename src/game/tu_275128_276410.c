#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern void func_002763B0(void *arg0);
extern s32 func_002761A0();
extern s32 func_00274040(void *);
extern s32 func_00277400();
extern void func_002778C8();

void func_00276410(void *arg0) {
    func_002763B0(M2C_FIELD(arg0, void **, 0x14));
    func_002761A0(M2C_FIELD(arg0, void **, 0x14));
    func_002761A0(M2C_FIELD(arg0, void **, 0x14) + 0x20);
    func_00274040(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00276458);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002764C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002764D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00276590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002765B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00276610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00276698);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00276728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002767E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002767E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002768B0);

void func_00276960(void *arg0, s64 *arg1, s64 *arg2) {
    M2C_FIELD(arg0, s64 *, 0x20) = (s64) *arg1;
    M2C_FIELD(arg0, s64 *, 0x28) = (s64) *arg2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00276978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00276980);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00276DA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00276E58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00276E68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00277400);

void func_00277510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    func_00277400(arg0, arg1, arg2, arg3, arg4, arg5, (s32) func_002778C8, arg7);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00277530);
