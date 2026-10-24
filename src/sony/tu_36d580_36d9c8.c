#include "include_asm.h"
#include "ps2/prelude.h"

void func_0036D9C8(void) {
    __asm__ volatile("li $3, 116\n\tsyscall");
}

void func_0036D9D8(void) {
    __asm__ volatile("li $3, 90\n\tsyscall");
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036D9E8);

void func_0036DA20(void) {
    __asm__ volatile("li $3, 91\n\tsyscall");
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036DA30);
