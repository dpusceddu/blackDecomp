#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355420);

#include "ps2/recovered_types.h"
extern s32 D_003D6340;
extern s32 func_0035C308(void *);
extern s32 func_003566F0(s32);
extern s32 func_0035C470(s32);

s32 func_003554F8(void *arg0, s32 arg1) {
    s32 temp_2;

    if (D_003D6340 == 0) {
        return 0x81018001;
    }
    if (((u32) (M2C_FIELD(arg0, s32 *, 4) - 2) >= 2U) || (M2C_FIELD(arg0, s32 *, 8) != 0)) {
        return 0x81010016;
    }
    temp_2 = func_0035C308(arg0);
    if (temp_2 < 0) {
        return 0x81010017;
    }
    func_003566F0(temp_2);
    return func_0035C470(temp_2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355588);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355598);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355708);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355928);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355A48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355C70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355D68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355D70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355F88);
