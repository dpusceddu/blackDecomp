/* INCLUDE_ASM marks a function of the translation unit that is still assembly.
 *
 *   INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100628);
 *
 * The compiler sees only a harmless declaration. configure.py and tools/include_asm.py read the markers from the
 * source and link each marked function from its assembly object at its original position; every other function of the
 * file's address range (see config/SLUS_213.76/splits.yaml) must be defined by the source. To recover a function,
 * replace its INCLUDE_ASM line with C or C++ and run ninja. See docs/build.md.
 */
#ifndef BLACK_INCLUDE_ASM_H
#define BLACK_INCLUDE_ASM_H

#ifndef INCLUDE_ASM
#define INCLUDE_ASM(dir, name) extern char include_asm_##name
#endif

#endif
