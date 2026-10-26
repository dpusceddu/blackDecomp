#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0033A260();
extern s32 func_0033A260(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_33a260", func_0033A260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_33a260", func_0033A3A8);

void *func_0033A3B0(void *arg0, s32 arg1, s32 arg2)
{
  s8 *new_var2;
  int new_var;
  new_var2 = ((s8 *) arg0) + 4;
  *((s32 *) new_var2) = 0x10;
  new_var = (arg1 << 7) + 0x100;
  M2C_FIELD(arg0, s32 *, 0) = (s32) (((new_var + (arg2 << 7)) + (arg2 * 0x60)) + 0x27E0);
  return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_33a260", func_0033A3E8);
#ifdef NON_MATCHING
/* Partial view; field meanings and complete extent are UNVERIFIED. */
typedef struct Recovered_ManifoldScratch {
    char unk_00[0x30];
    char* unk_30;
    char unk_34[0x90];
    u32 unk_c4;
    char* unk_c8;
    char unk_cc[4];
    u32 unk_d0;
    char* unk_d4;
    char unk_d8[4];
    u32 unk_dc;
    char unk_e0[4];
    char* unk_e4;
} Recovered_ManifoldScratch;
// Unmatched: pointer arithmetic and store scheduling differ.
Recovered_ManifoldScratch* func_0033A3F0(Recovered_ManifoldScratch** storage, u32 vertices, u32 triangles) {
    Recovered_ManifoldScratch* scratch = *storage;
    if (scratch) {
        char* first = (char*)scratch + 0x100;
        char* second = first + vertices * 0x80;
        char* third;
        scratch->unk_c4 = vertices;
        scratch->unk_d0 = triangles;
        scratch->unk_dc = triangles;
        third = second + triangles * 0x60;
        scratch->unk_30 = first;
        scratch->unk_d4 = second;
        scratch->unk_c8 = third;
        scratch->unk_e4 = third + triangles * 0x80;
    }
    return scratch;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_33a260", func_0033A3F0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_33a260", func_0033A440);

void func_0033A448(void) {
    func_0033A260(1, 0xFFFF);
}

void func_0033A468(void) {
    func_0033A260(0, 0xFFFF);
}
