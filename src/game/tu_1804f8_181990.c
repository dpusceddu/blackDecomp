#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void func_001818A8(RecoveredAIActionStack *); /* AIActionStack_Pop */
extern void func_00181660(RecoveredAIActionStack *, u32, s32); /* AIActionStack_PushAndEnter */

void func_00181990(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x4C0) > 0) {
        do {
            func_001818A8((RecoveredAIActionStack *) arg0);
        } while (M2C_FIELD(arg0, s32 *, 0x4C0) > 0);
    }
    func_00181660((RecoveredAIActionStack *) arg0, (u32) arg1, 0);
}
