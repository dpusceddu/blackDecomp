#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00406550[];
const char rodata_00406550[32] __asm__("D_00406550") __attribute__((aligned(8))) = "IPathFinder" "\000\000\000\000\000" "Q24Kaim7CObject" "\000";
extern s32 func_002E75D0();
extern M2C_UNK D_004512B0;
extern M2C_UNK * D_004513C0;
extern M2C_UNK D_003E00E0;
extern s32 func_0038D4C0();
extern M2C_UNK D_003E9678;
extern s32 D_0049B938;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2e4f58", func_002E4F58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2e4f58", func_002E5088);

void func_002E5178(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E75D0(&D_004512B0, D_00406550, NULL, 0, 0, 0);
            return;
        }
        D_004513C0 = &D_003E00E0;
    }
}

s32 func_002E51D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0038D4C0(arg0, arg1, arg2, arg3, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E9678;
    return arg0;
}

s32 func_002E5218(void *arg0, void *arg1) {
    s32 *temp_16;
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0xC);
    temp_16 = temp_4 + (M2C_FIELD(arg1, s32 *, 0) * 4);
    if (*temp_16 == 0) {
        *temp_16 = M2C_FIELD(arg1, s32 (**)(s32), 4)(temp_4);
    }
    M2C_FIELD(arg0, s32 *, 0x14) = *temp_16;
    return 1;
}

void func_002E5278(void) {
    D_0049B938 = 0;
}

void func_002E5288(void) {
    func_002E5178(1, 0xFFFF);
}

void func_002E52A8(void) {
    func_002E5178(0, 0xFFFF);
}
