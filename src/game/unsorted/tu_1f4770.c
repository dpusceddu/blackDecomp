#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_0040F0E0;
extern s32 func_001F5950(void*, void*);
extern s32 func_001F4E38(void*, void*, s32, s8*);
extern s32 func_00275260(const char*, u16*, s32);
extern s32 func_00275128(const u16*, void*, s32);
extern s32 func_003848F8(u16*, const u16*, s32*, s32*, s32*);

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
#ifdef NON_MATCHING
// Unmatched: destination and output buffer use swapped saved registers.
void* func_001F5418(void* owner, const char* text, s32 first, s32 last) {
    s32 difference;
    s32 last_value;
    s32 first_value;
    u16 input[128];
    u16 output[128];
    void* destination;

    first_value = first;
    last_value = last;
    difference = last - first;
    func_00275260(text, input, 128);
    destination = (u8*)owner + 0x18E4;
    func_003848F8(output, input, &first_value, &last_value, &difference);
    func_00275128(output, destination, 128);
    return destination;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5418);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5850);

void func_001F5928(void *arg0) {
    if (M2C_FIELD(D_0040F0E0, s32 *, 0x2014C) != 0) {
        M2C_FIELD(arg0, s8 *, 0x19A4) = 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5950);
