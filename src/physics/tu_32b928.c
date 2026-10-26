#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0032B9E0();
extern s32 func_0032B9E0(M2C_UNK, M2C_UNK);

#ifdef NON_MATCHING
/* Offsets are observed; the full structure and semantic names are UNVERIFIED. */
typedef struct Recovered_PhysicsPair {
    int first, second;
} Recovered_PhysicsPair;
typedef struct Recovered_PhysicsBlock {
    u32 count;
    char* entries;
    u32 pairCount;
    char* unk0c;
    char* unk10;
    Recovered_PhysicsPair* pairs;
    u32 unk18;
    void** slots;
} Recovered_PhysicsBlock;
// Unmatched: descriptor temporaries and alignment arithmetic schedule differently.
void func_0032B928(Recovered_PhysicsBlock* block) {
    u32 base = ((u32)block + 0x2f) & ~15u;
    u32 afterEntries = base + block->count * 0xA0;
    u32 first = (afterEntries + block->pairCount * 8 + 15) & ~15u;
    u32 second = (first + block->pairCount * 0x40 + 15) & ~15u;
    block->pairs = (Recovered_PhysicsPair*)afterEntries;
    block->unk0c = (char*)first;
    block->entries = (char*)base;
    block->unk10 = (char*)second;
    block->slots = (void**)(second + block->pairCount * 0x50);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_32b928", func_0032B928);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_32b928", func_0032B9E0);
#ifdef NON_MATCHING
extern void func_0032B928(Recovered_PhysicsBlock*);
extern void func_00332CB0(char**, int);
// Unmatched: the pair initialization loop has an extra scheduling instruction.
Recovered_PhysicsBlock* func_0032BB28(Recovered_PhysicsBlock** storage, u32 count, u32 pairCount) {
    Recovered_PhysicsBlock* block = *storage;
    u32 i;
    if (block) {
        block->count = 0;
        block->entries = 0;
        block->pairCount = 0;
        block->unk0c = 0;
        block->unk10 = 0;
        block->pairs = 0;
        block->unk18 = 0;
    }
    block->count = count;
    block->pairCount = pairCount;
    func_0032B928(block);
    for (i = 0; i < count; ++i) {
        char* entry = block->entries + i * 0xA0;
        func_00332CB0(&entry, 0);
        block->slots[i] = 0;
    }
    i = 0;
    if (pairCount) {
        Recovered_PhysicsPair* pair = block->pairs;
        do {
            pair->first = -1;
            pair->second = -1;
            ++pair;
            ++i;
        } while (i < pairCount);
    }
    return block;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_32b928", func_0032BB28);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_32b928", func_0032BC18);

void func_0032BC30(void) {
    func_0032B9E0(1, 0xFFFF);
}

void func_0032BC50(void) {
    func_0032B9E0(0, 0xFFFF);
}
