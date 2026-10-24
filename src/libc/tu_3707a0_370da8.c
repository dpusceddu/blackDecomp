#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 D_0049BF30;
extern s32 func_00370760();
extern s32 D_0040EC48;

#include "ps2/recovered_types.h"

void * func_00370DA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5, void *arg6) {
    s32 temp_18;
    void *temp_16;
    void *temp_16_2;
    void *temp_17;
    void *temp_2;

    temp_2 = ((void *(*)()) arg0)();
    temp_16_2 = M2C_FIELD(temp_2, void **, 4);
    temp_16 = temp_16_2 + 0x10;
    temp_17 = temp_2 + M2C_FIELD(temp_16_2, s16 *, 0x10);
    temp_18 = ((s32 (*)()) arg1)();
    return M2C_FIELD(temp_16, void *(**)(void *, s32, s32, s32, s32, void *), 4)(temp_17, temp_18, arg2, arg3, ((s32 (*)()) arg4)(), arg5);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00370E58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00370E90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00370EC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00370F00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00370F38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00370F70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00370FA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00370FE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00371018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00371050);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00371088);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003710C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003710F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00371130);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00371168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003711A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003711D8);

s32 * func_00371210(void) {
    if (D_0049BF30 == 0) {
        func_00370760();
        func_00370168(&D_0049BF30, "17__array_type_info", &D_0040EC48);
    }
    return &D_0049BF30;
}
