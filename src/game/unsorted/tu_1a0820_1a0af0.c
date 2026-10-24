#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0018D6F8(void *, u8);
extern M2C_UNK D_003DFF80;
extern void func_00193A28(RecoveredAIActionHeader *, u32, s32); /* AIAction_RequestSuccessor */
extern s32 * func_001A0A30(s32 *);

void func_001A0AF0(s32 *arg0, void *arg1, s32 arg2, s32 arg3) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 temp_2;

    temp_2 = func_0018D6F8(*arg0 + 0xD10, M2C_FIELD(arg1, u8 *, 8));
    if (temp_2 != 0x4A) {
        *(void * *)(sp + 8) = arg1;
        *(M2C_UNK * *)(sp + 4) = &D_003DFF80;
        *(s32 *)(sp + 0) = 0;
        func_00193A28((RecoveredAIActionHeader *) arg0, (u32) temp_2, (s32) sp);
        return;
    }
    func_001A0A30(arg0);
}
