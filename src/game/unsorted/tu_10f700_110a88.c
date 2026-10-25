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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00112790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110a88", func_00113FE8);
