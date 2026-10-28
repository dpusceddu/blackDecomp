#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_00110A88(void *arg0) {
    void *temp_2;

    temp_2 = (void *) (((u32) M2C_FIELD(arg0, void **, 0x18)) + ((u32) arg0));
    M2C_FIELD(arg0, void **, 0x18) = temp_2;
    M2C_FIELD(arg0, void **, 0x1C) = (void *) ((void *) (((u32) M2C_FIELD(arg0, void **, 0x1C)) + ((u32) arg0)));
    return (s32) temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00110AA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00110AB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00110B98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00110BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00110C10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00110C50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00110C90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00112398);
#ifdef NON_MATCHING
// Unmatched: global vector address and copy scheduling differ.
// Partial curve view; the original type and field meanings are UNVERIFIED.
typedef struct {
    char unknown00[0x10];
    s32 field10, field14, field18;
    char unknown1c[4];
    u128 field20, field30, field40, field50;
} CurveInitDraft;
extern u128 D_0040F070, D_0040F080;
extern void func_0027ACC8(void);

void func_00112790(CurveInitDraft* self, s32 a, s32 b) {
    func_0027ACC8();
    self->field20 = D_0040F070;
    self->field30 = D_0040F070;
    self->field40 = D_0040F080;
    self->field50 = D_0040F080;
    self->field14 = a;
    self->field18 = b;
    self->field10 = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00112790);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00113FE8);
