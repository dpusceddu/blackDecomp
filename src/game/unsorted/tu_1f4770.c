#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_0040F0E0;
extern s32 func_001F5950(void*, void*);
extern s32 func_001F4E38(void*, void*, s32, s8*);
extern s32 func_00275260(const char*, u16*, s32);
extern s32 func_00275128(const u16*, void*, s32);
extern s32 func_003848F8(u16*, const u16*, s32*, s32*, s32*);
/* These call signatures and the output buffer layout remain UNVERIFIED. */
extern void* D_0040F4D0;
extern void* D_0040F4E8;
extern void* func_00122900(void*, s8);
extern s32 func_0012F880(void*, void*, s32, void*);
extern s32 func_00160AA8(void*, s32);

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
s32 func_001F5850(void) {
    s32 output[4];
    void* progress = (u8*)D_0040F4D0 + 0x910;
    void* level = func_00122900(D_0040F4E8, M2C_FIELD(D_0040F4D0, s8*, 0x5AAC));
    s32 difficulty = M2C_FIELD(D_0040F0E0, s32*, 0x2014C);
    s32 kind = func_0012F880(progress, level, difficulty, output);

    switch (kind) {
        case 0: return func_00160AA8((u8*)D_0040F4D0 + 0x8F0, (s8)M2C_FIELD(D_0040F0E0, s32*, 0x2014C));
        case 2: return output[0];
        case 1:
        default: return 0;
    }
}

void func_001F5928(void *arg0) {
    if (M2C_FIELD(D_0040F0E0, s32 *, 0x2014C) != 0) {
        M2C_FIELD(arg0, s8 *, 0x19A4) = 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5950);
