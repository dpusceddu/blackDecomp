#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0A98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0C10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0D58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C1178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C12B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C14A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C18E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C34A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C4B38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C6570);

#include "ps2/recovered_types.h"
extern void * D_0040E6C8;
extern s32 func_002AC568(void *);
extern void * D_0040E6CC;
extern void * D_0040E6C0;
extern s32 func_002C0D58(s32, void *, s32);

void func_002C65E0(void) {
    if (D_0040E6C8 != NULL) {
        func_002AC568(D_0040E6C8);
        D_0040E6C8 = NULL;
    }
    if (D_0040E6CC != NULL) {
        func_002AC568(D_0040E6CC);
        D_0040E6CC = NULL;
    }
}

s32 func_002C6620(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 var_2;

    var_2 = 0;
    if (D_0040E6C0 != NULL) {
        *(s32 *)(sp + 4) = 0;
        *(s32 *)(sp + 0) = 0;
        *(s32 *)(sp + 8) = M2C_FIELD(D_0040E6C0, s32 *, 0xC);
        *(s32 *)(sp + 12) = M2C_FIELD(D_0040E6C0, s32 *, 0x10);
        var_2 = func_002C0D58(0, sp, arg2);
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C6668);
