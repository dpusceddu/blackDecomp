/* Include original code in this translation unit, using its selected assembler. */
#ifndef BLACK_INCLUDE_ASM_H
#define BLACK_INCLUDE_ASM_H
#define INCLUDE_ASM(dir, name) __asm__(".include \"" dir "/" #name ".s\"\n")
#endif
