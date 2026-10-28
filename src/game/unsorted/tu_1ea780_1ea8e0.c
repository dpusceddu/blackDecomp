#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_001EAA20(void *, s32, s32, void *, u16);

s32 func_001EA8E0(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, f32 fparg0) {
    s32 temp_5;
    s32 var_2;
    void *temp_3;

    temp_3 = M2C_FIELD(arg1, void **, 0x110);
    var_2 = -1;
    if (temp_3 != NULL) {
        temp_5 = M2C_FIELD(temp_3, s32 *, 0x10);
        if ((temp_5 != -1) && (M2C_FIELD(temp_3, f32 *, 8) <= fparg0)) {
            var_2 = func_001EAA20(arg0, temp_5, M2C_FIELD(temp_3, s32 *, 0xC), arg1, M2C_FIELD(temp_3, u16 *, 0x1C));
        }
    }
    return var_2;
}


#include "ps2/recovered_types.h"

s32 func_001EAB60(void *arg0) {
    s32 *var_3;
    s32 temp_2;
    s32 var_5;
    s32 var_6;

    var_6 = 0;
    var_3 = (s32 *) (((s8 *) arg0) + 4);
    var_5 = 7;
    do {
        temp_2 = *var_3 - 1;
        *var_3 = temp_2;
        if (temp_2 > 0) {
            var_6 += 1;
        } else {
            *var_3 = 0;
        }
        var_5 -= 1;
        var_3 = (s32 *) (((s8 *) var_3) + 8);
    } while (var_5 >= 0);
    M2C_FIELD(arg0, s32 *, 0x44) = var_6;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EB4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EB838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EB998);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBC88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBD88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBEB0);
extern s32 func_001EC5C8(void*);
extern void* func_001EBEB8(void*, s32, s32);
#ifdef NON_MATCHING
// Unmatched: register allocation differs.
void* func_001EBEB8(void* self, s32 threshold, s32 unused) {
    void* best = NULL;
    s32 i = 0;
    s32 score = 14;
    if (M2C_FIELD(self, s32*, 0x1E28) > 0) {
        u8* entry = self;
        do {
            if (func_001EC5C8(entry) < score) {
                best = entry;
                score = func_001EC5C8(best);
            }
            i++;
            entry += 0x40;
        } while (i < M2C_FIELD(self, s32*, 0x1E28));
    }
    return func_001EC5C8(best) >= threshold ? NULL : best;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBEB8);
#endif
#ifdef NON_MATCHING
// Unmatched: one address-add operand order differs.
void* func_001EBF68(void* self, s32 key) {
    s32 end = M2C_FIELD(self, s32*, 0x1E30);
    s32 i = M2C_FIELD(self, s32*, 0x1E38);
    if (i < end) {
        u8* entry = (i * 0x28 + 0x80) + (u8*)self;
        do {
            i++;
            if (M2C_FIELD(entry, s32*, 0x14) == 0 && M2C_FIELD(entry, s32*, 0x10) == key) return entry;
            entry += 0x28;
        } while (i < end);
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBF68);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBFC0);
extern void* D_0040F4D0;
void func_001EC060(void* self, s128 value, s32 arg2, s32 arg3, f32 delay, f32 duration) {
    u8* entry = self;
    u8* end = entry + 0x300;
    f32 time = M2C_FIELD(D_0040F4D0, f32*, 0x20);
    do {
        if (M2C_FIELD(entry, u8*, 0x400) == 0) {
            f32 start = time + delay;
            M2C_FIELD(entry, u8*, 0x400) = 1;
            M2C_FIELD(entry, s128*, 0x3E0) = value;
            M2C_FIELD(entry, s32*, 0x3F0) = arg2;
            M2C_FIELD(entry, s32*, 0x3F4) = arg3;
            M2C_FIELD(entry, f32*, 0x3F8) = start;
            M2C_FIELD(entry, f32*, 0x3FC) = start + duration;
            return;
        }
        entry += 0x30;
    } while ((s32)entry < (s32)end);
}
extern void* func_001EC600(void*, void*, s128);
void func_001EC0B8(void* self, s128 value, s32 unused) {
    s32 i = M2C_FIELD(self, s32*, 0x1E38);
    void* entry = NULL;
    void* found;
    while (i < M2C_FIELD(self, s32*, 0x1E30)) {
        entry = (u8*)self + (i * 0x28 + 0x80);
        if (M2C_FIELD(entry, s32*, 0x14) == 3 && M2C_FIELD(entry, s32*, 0x10) == 1) break;
        i++;
        entry = NULL;
    }
    if (entry) {
        found = func_001EBEB8(self, 1, i);
        if (found) func_001EC600(found, entry, value);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EC158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EC248);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EC330);
