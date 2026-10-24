#include "include_asm.h"
#include "ps2/prelude.h"

extern u8 func_001746D8();
extern s32 func_001746C8();

void func_00174740(void *arg0) {
    s32 temp_2_2;
    s32 temp_3;
    void *temp_2;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x3C);
    switch (temp_3) {                               /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 0x28) != 0) {
            func_001746D8();
        } else {
            func_001746C8();
        }
        return;
    case 1:
        temp_2 = M2C_FIELD(arg0, void **, 0x24);
        if (temp_2 != NULL) {
            temp_2_2 = M2C_FIELD(temp_2, s32 *, 0x38C);
            if (temp_2_2 != 0) {
                if ((temp_2_2 ^ 1) != 0) {
                    goto block_9;
                }
            }
        } else {
block_9:
            if (M2C_FIELD(arg0, u8 *, 0x28) == 0) {
                func_001746C8();
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001747D0);
