#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_0040F0E0;
extern s32 func_001F5950(void*, void*);
extern s32 func_001F4E38(void*, void*, s32, s8*);

#ifdef NON_MATCHING
// Unmatched: owner and target use swapped saved registers.
s32 func_001F4D30(void* owner, s8* value, void* target) {
    s32 result = func_001F5950(owner, target);
    if (result != 0) { result = func_001F4E38(owner, target, 0, value); }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F4D30);
#endif
#ifdef NON_MATCHING
// Unmatched: owner and target use swapped saved registers.
s32 func_001F4D88(void* owner, s8* value, void* target) {
    s32 result = func_001F5950(owner, target);
    if (result != 0) { result = func_001F4E38(owner, target, 1, value); }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F4D88);
#endif
#ifdef NON_MATCHING
// Unmatched: owner and target use swapped saved registers.
s32 func_001F4DE0(void* owner, s8* value, void* target) {
    s32 result = func_001F5950(owner, target);
    if (result != 0) { result = func_001F4E38(owner, target, 3, value); }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F4DE0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F4E38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5418);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5850);

void func_001F5928(void *arg0) {
    if (M2C_FIELD(D_0040F0E0, s32 *, 0x2014C) != 0) {
        M2C_FIELD(arg0, s8 *, 0x19A4) = 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5950);
