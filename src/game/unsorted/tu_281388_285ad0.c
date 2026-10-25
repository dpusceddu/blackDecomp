#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00285CA0(void *, s32);
extern s32 func_00286278(void *, void *);
extern s32 func_002860D0(void *, f32);

s32 func_00285AD0(void *arg0, s32 arg1) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 temp_2;
    s32 temp_2_2;

    *(s32 *)(sp + 0) = 1;
    *(s32 *)(sp + 4) = func_00285CA0(arg0, 0);
    temp_2_2 = func_00285CA0(arg0, 0);
    *(s8 *)(sp + 12) = 0;
    *(s32 *)(sp + 8) = temp_2_2;
    func_00286278((void *) (((s8 *) arg0) + 0x1C0), sp);
    temp_2 = func_002860D0(arg0, 1.0f);
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x88) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_285ad0", func_00285B58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_285ad0", func_00285B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_285ad0", func_00285C18);
