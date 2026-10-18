#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_0023EB78();
extern s32 func_002405E8();

s32 func_002406A0(s32 arg0, s32 arg1) {
    u8 sp[8] __attribute__((aligned(16)));

    func_0023EB78(M2C_FIELD(arg0, s32 *, 0), arg1, 0, (s32) sp, (s32) (sp + 4));
    return func_002405E8(arg0, *(s32 *)(sp + 4));
}

s32 func_002406E0(s32 arg0, s32 arg1) {
    return func_002406A0(arg0, M2C_FIELD(arg1, s32 *, 0));
}
