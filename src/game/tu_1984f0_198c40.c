#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_001984F0();
extern s32 func_00193A08();
extern s32 func_0017E428();
extern s128 func_00189048();
extern s32 func_0017DB98();
extern s32 func_00198568();
extern s32 func_00193A60(RecoveredAIActionHeader *, M2C_UNK, f32);

void func_00198C40(RecoveredAIActionHeader *arg0) {
    void *temp_16;
    void *temp_16_2;

    func_001984F0();
    if (func_00193A08(arg0) == 0) {
        temp_16 = arg0->brain;
        func_0017E428(temp_16 + 0x650, func_00189048(temp_16 + 0x150));
        temp_16_2 = arg0->brain;
        func_0017DB98(temp_16_2 + 0x650, func_00189048(temp_16_2 + 0x150));
    }
}

void func_00198CB8(RecoveredAIActionHeader *arg0) {
    func_00198568();
    func_00193A60(arg0, 0, 0.2f);
}
