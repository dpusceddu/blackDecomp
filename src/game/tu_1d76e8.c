#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00324F98();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D76E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D7A60);

s32 func_001D7B98(void) {
    return func_00324F98() != 0;
}

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_0027FCF8(void *, void *, s32);

void * func_001D7BB8(void *arg0, s32 arg1) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s64 *)(sp + 0) = (s64) arg1;
    return func_0027FCF8(M2C_FIELD(arg0, void **, 0x88), sp, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D7BE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D7C20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D7CC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D7D40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D7EC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D7EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D83D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D83F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8428);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8478);

void func_001D84C8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x26) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D84D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8600);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8AD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8BB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8BC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8CF8);

s32 func_001D8D68(void) {
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8D70);

void func_001D8DE8(void) {

}

void func_001D8DF0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8DF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8E38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8F38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D8FD8);

void func_001D90F8(void) {

}
