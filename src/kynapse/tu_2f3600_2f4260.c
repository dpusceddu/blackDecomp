#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00407900[];
const char rodata_00407900[32] __asm__("D_00407900") __attribute__((aligned(8))) = "CPathCostData" "\000\000\000" "Q24Kaim7CObject" "\000";
extern s32 func_002F35B0();
extern M2C_UNK D_00452388;
extern M2C_UNK func_002F3600;
extern M2C_UNK * D_00452498;
extern M2C_UNK D_003EC200;
extern M2C_UNK * D_003EDE90;
extern s32 (*D_003C87E0)();
extern M2C_UNK * D_003E0040;

void func_002F4260(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002F35B0(&D_00452388, D_00407900, &func_002F3600);
            return;
        }
        D_00452498 = &D_003EC200;
    }
}

s32 func_002F4330(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s8 *temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 8) + ((arg1 * M2C_FIELD(arg0, s32 *, 0xC)) + arg2);
    *temp_2 = (s8) arg3;
    return (s32) temp_2;
}

void func_002F4350(void) {
    func_002F4260(1, 0xFFFF);
}

void func_002F4370(void) {
    func_002F4260(0, 0xFFFF);
}

