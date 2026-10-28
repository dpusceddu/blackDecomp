#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0037CCA8(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37cca8", func_0037CCA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37cca8", func_0037CDF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37cca8", func_0037CE60);
#ifdef NON_MATCHING
// Unmatched: load/store scheduling differs.
s32 func_0037CEC8(void* self, void* body, s32 unused) {
    void* list = (u8*)self + 0x60;
    s32 state;
    M2C_FIELD(M2C_FIELD(body, void**, 0x2C), void**, 0x3C) = M2C_FIELD(body, void**, 0x3C);
    state = M2C_FIELD(body, s32*, 0x8C) & 7;
    M2C_FIELD(M2C_FIELD(body, void**, 0x3C), void**, 0x2C) = M2C_FIELD(body, void**, 0x2C);
    M2C_FIELD(body, void**, 0x2C) = list;
    M2C_FIELD(body, void**, 0x3C) = M2C_FIELD(list, void**, 0x3C);
    M2C_FIELD(M2C_FIELD(list, void**, 0x3C), void**, 0x2C) = body;
    M2C_FIELD(list, void**, 0x3C) = body;
    if (state == 1) M2C_FIELD(self, s32*, 0x1C)--;
    else if (state == 2) M2C_FIELD(self, s32*, 0x20)--;
    else M2C_FIELD(self, s32*, 0x24)--;
    M2C_FIELD(body, s32*, 0x8C) = 0;
    return ++M2C_FIELD(self, s32*, 0x18);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37cca8", func_0037CEC8);
#endif
#ifdef NON_MATCHING
// Unmatched: load/store scheduling differs.
s32 func_0037CF60(void* self, void* body) {
    void* list = (u8*)self + 0x270;
    s32 result;
    M2C_FIELD(M2C_FIELD(body, void**, 0x2C), void**, 0x3C) = M2C_FIELD(body, void**, 0x3C);
    M2C_FIELD(body, s32*, 0xAC) = M2C_FIELD(self, s32*, 0x38C) - 1;
    M2C_FIELD(M2C_FIELD(body, void**, 0x3C), void**, 0x2C) = M2C_FIELD(body, void**, 0x2C);
    M2C_FIELD(body, void**, 0x2C) = list;
    M2C_FIELD(body, void**, 0x3C) = M2C_FIELD(list, void**, 0x3C);
    result = M2C_FIELD(self, s32*, 0x24) + 1;
    M2C_FIELD(body, s32*, 0x8C) = (M2C_FIELD(body, s32*, 0x8C) & 8) | 4;
    M2C_FIELD(self, s32*, 0x24) = result;
    M2C_FIELD(M2C_FIELD(list, void**, 0x3C), void**, 0x2C) = body;
    M2C_FIELD(list, void**, 0x3C) = body;
    M2C_FIELD(self, s32*, 0x20)--;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37cca8", func_0037CF60);
#endif
#ifdef NON_MATCHING
// Unmatched: load/store scheduling differs.
s32 func_0037CFD0(void* self, void* body) {
    void* list = (u8*)self + 0x1C0;
    s32 result;
    M2C_FIELD(M2C_FIELD(body, void**, 0x2C), void**, 0x3C) = M2C_FIELD(body, void**, 0x3C);
    M2C_FIELD(body, s32*, 0xAC) = M2C_FIELD(self, s32*, 0x38C) - 0;
    M2C_FIELD(M2C_FIELD(body, void**, 0x3C), void**, 0x2C) = M2C_FIELD(body, void**, 0x2C);
    M2C_FIELD(body, void**, 0x2C) = list;
    M2C_FIELD(body, void**, 0x3C) = M2C_FIELD(list, void**, 0x3C);
    result = M2C_FIELD(self, s32*, 0x20) + 1;
    M2C_FIELD(body, s32*, 0x8C) = (M2C_FIELD(body, s32*, 0x8C) & 8) | 2;
    M2C_FIELD(self, s32*, 0x20) = result;
    M2C_FIELD(M2C_FIELD(list, void**, 0x3C), void**, 0x2C) = body;
    M2C_FIELD(list, void**, 0x3C) = body;
    M2C_FIELD(self, s32*, 0x24)--;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37cca8", func_0037CFD0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37cca8", func_0037D038);
#ifdef NON_MATCHING
// Unmatched: load/store scheduling differs.
void* func_0037D0C8(void* self, void* node) {
    void* list = (u8*)self + 0x320;
    void* result;
    M2C_FIELD(M2C_FIELD(node, void**, 0), void**, 4) = M2C_FIELD(node, void**, 4);
    M2C_FIELD(self, s32*, 0x4C)++;
    M2C_FIELD(M2C_FIELD(node, void**, 4), void**, 0) = M2C_FIELD(node, void**, 0);
    M2C_FIELD(node, void**, 0) = list;
    M2C_FIELD(self, s32*, 0x50)--;
    result = M2C_FIELD(list, void**, 4);
    M2C_FIELD(node, void**, 4) = result;
    M2C_FIELD(M2C_FIELD(list, void**, 4), void**, 0) = node;
    M2C_FIELD(list, void**, 4) = node;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37cca8", func_0037D0C8);
#endif

void func_0037D118(void) {
    func_0037CCA8(1, 0xFFFF);
}

void func_0037D138(void) {
    func_0037CCA8(0, 0xFFFF);
}
