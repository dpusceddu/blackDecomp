#ifndef BLACK_ANIMATION_PARAMETER_BANK_H
#define BLACK_ANIMATION_PARAMETER_BANK_H

/* Raw slots preserve the alias between slot 70 and the count at byte 0x118. */
struct AnimationParameterBank {
    unsigned int slots[70];
    unsigned int count;
};
extern void *AnimationParameterMemory_Set(void *, int, unsigned int) __asm__("func_0035C6EC");
extern void *AnimationParameterMemory_Copy(void *, const void *, unsigned int) __asm__("func_0035C544");
#endif
