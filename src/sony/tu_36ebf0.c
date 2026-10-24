#include "include_asm.h"
#include "ps2/prelude.h"

void func_0036EBF0(void) {
    __asm__ volatile("li $3, 90\n\tsyscall");
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036EC00);

void func_0036EC38(void) {
    __asm__ volatile("li $3, 91\n\tsyscall");
}

void func_0036EC48(void) {
    __asm__ volatile("li $3, 116\n\tsyscall");
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036EC58);
