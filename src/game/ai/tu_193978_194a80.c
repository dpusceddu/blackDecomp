#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

extern s32 func_0018D608();
extern s32 func_0018AB08();
extern s32 func_00178F28();
extern s32 * func_00188F80();
extern s32 func_00193A28();
extern u32 func_001829A8(RecoveredAIController *);
extern s32 func_001829E8(void *);
extern s32 func_00188F10(void *);
extern void func_0017E428(void *, s128);
extern s128 func_00189048(void *);
extern void func_00193990(RecoveredAIActionHeader *, u8);

s32 func_00194A80(void **arg0, s32 *arg1) {
    s32 var_2;

    if (*arg1 == 2) {
        var_2 = 1;
        if (func_0018D608(*arg0 + 0xD10) != 0) {
            var_2 = 1;
            if (func_0018AB08(*arg0 + 0x150) != 0) {
                if (func_00178F28(func_00188F80(*arg0 + 0x150)) != 0) {
                    func_00193A28(arg0, 0x15, 0);
                }
                return 1;
            }
        }
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return var_2;
    }
    var_2 = 0;
    return var_2;
}

void func_00194B08(RecoveredAIActionHeader *action) {
    u8 result;
    u8 *query;
    if (func_001829A8((RecoveredAIController *) ((u8 *) action->brain + 0x810)) == 0) {
        func_00193990(action, 0);
        return;
    }
    if (func_001829E8((u8 *) action->brain + 0x810) == 0) goto track;
    query = (u8 *) action->brain + 0x90;
    result = 0;
    if (query[0x75] && (query[0xA0] || query[0xA1])) result = 1;
    func_00193990(action, result);
    return;
track:
    if (func_00188F10((u8 *) action->brain + 0x150)) {
        u8 *owner = action->brain;
        func_0017E428(owner + 0x650, func_00189048(owner + 0x150));
    }
}
