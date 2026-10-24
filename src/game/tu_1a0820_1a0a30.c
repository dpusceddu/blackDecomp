#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_0017E770(f32 *);
extern s32 func_001580C0(void *);
extern void func_00193A28(RecoveredAIActionHeader *, u32, s32); /* AIAction_RequestSuccessor */
extern M2C_UNK D_003DFF80;
extern s32 func_0018D6C0(void *);

void func_001A0A30(s32 *arg0) {
    u8 sp[8] __attribute__((aligned(16)));

    if ((func_0017E770(M2C_FIELD(arg0, s32 *, 0) + 0x650) == NULL) && (func_001580C0(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), void **, 0x7C), void **, 0x2A4)) != 0)) {
        func_00193A28((RecoveredAIActionHeader *) arg0, 3U, 0);
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 8) != 0) {
        *(M2C_UNK * *)(sp + 4) = &D_003DFF80;
        *(s32 * *)(sp + 8) = (s32 *) (((s8 *) arg0) + 0xC);
        *(s32 *)(sp + 0) = 0;
        func_00193A28((RecoveredAIActionHeader *) arg0, func_0018D6C0(M2C_FIELD(arg0, s32 *, 0) + 0xD10), (s32) sp);
        return;
    }
    func_00193A28((RecoveredAIActionHeader *) arg0, func_0018D6C0(M2C_FIELD(arg0, s32 *, 0) + 0xD10), 0);
}
