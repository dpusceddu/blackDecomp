#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_001984F0();
extern s32 func_00193A08();
extern s32 func_0017E428();
extern s128 func_00189048();
extern s32 func_0017DB98();
extern s32 func_001829E8();

void func_00198A68(RecoveredAIActionHeader *arg0) {
    void *temp_16;
    void *temp_16_2;

    func_001984F0();
    if (func_00193A08(arg0) == 0) {
        temp_16 = arg0->brain;
        func_0017E428(temp_16 + 0x650, func_00189048(temp_16 + 0x150));
        temp_16_2 = arg0->brain;
        func_0017DB98(temp_16_2 + 0x650, func_00189048(temp_16_2 + 0x150));
        if ((func_001829E8(arg0->brain + 0x810) != 0) || (func_001829A8(arg0->brain + 0x810) == 0)) {
            func_00193990(arg0, 0U);
        }
    }
}
