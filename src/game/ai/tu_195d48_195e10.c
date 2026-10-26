#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00188F10();
extern s32 func_00195D48();
extern s32 func_00195F08();
extern s32 func_00180B70();
extern s128 func_00189048();
extern s32 func_00193A60(void **, M2C_UNK, f32);
extern s32 func_0018DDD8(void *);
extern s32 D_003F66E0[];
extern s32 D_003F66C0[];
extern void *func_00181A90(void *, s32);

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

// Unmatched: 00195F08: owned read-only selection tables are not recovered.
#ifdef NON_MATCHING
s32 func_00195F08(RecoveredAIActionHeader *action) {
    s32 count;
    s32 *choices;
    s32 index;
    if (func_0018DDD8((u8 *) action->brain + 0xC94)) {
        count = 3;
        choices = D_003F66E0;
    } else {
        count = 7;
        choices = D_003F66C0;
    }
    index = M2C_FIELD(action, s32 *, 8);
    while (index < count) {
        s32 choice = choices[index];
        void *candidate = func_00181A90((u8 *) action->brain + 0xEC0, choice);
        void *vtable = M2C_FIELD(candidate, void **, 4);
        if (M2C_FIELD(vtable, s32 (**)(void *), 0x6C)(
                (u8 *) candidate + M2C_FIELD(vtable, s16 *, 0x68)) != 0) {
            func_00193A28(action, choice, 0);
            M2C_FIELD(action, s32 *, 8)++;
            return 1;
        }
        index = ++M2C_FIELD(action, s32 *, 8);
    }
    return 0;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_195d48_195e10", func_00195F08);
