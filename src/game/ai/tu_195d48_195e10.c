#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00188F10();
extern s32 func_00195D48();
extern s32 func_00195F08();
extern s32 func_00180B70();
extern s128 func_00189048();
extern s32 func_00193A60(void **, M2C_UNK, f32);

void func_00195E10(RecoveredAIActionHeader *arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        func_00193990(arg0, 1U);
        return;
    }
    if (func_00188F10(arg0->brain + 0x150) == 0) {
        func_00195D48(arg0);
        return;
    }
    if (func_00195F08(arg0) == 0) {
        func_00195D48(arg0);
    }
}

void func_00195E80(void **arg0) {
    void *temp_16;

    if ((func_00188F10(*arg0 + 0x150) == 0) || (temp_16 = *arg0, (((func_00180B70(temp_16 + 0xB30, func_00189048(temp_16 + 0x150)) ^ 1) & 0xFF) != 0))) {
        func_00195D48(arg0);
        return;
    }
    func_00193A60(arg0, 0, 0.0f);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_195d48_195e10", func_00195F08);
