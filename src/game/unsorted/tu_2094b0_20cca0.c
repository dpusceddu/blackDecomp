#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0035D728(void *, s8 *, ...);
extern s32 func_0021A3B8(s8 *, s8 *);
extern s32 func_0035E750(s8 *);

u32 func_0020CCA0(void *arg0, s32 arg1, s32 arg2) {
    u8 sp[312] __attribute__((aligned(16)));

    func_0035D728(sp, "%s.%s", arg0 + ((arg2 * 0xA) + 0x38BF), arg1);
    func_0021A3B8(sp, (sp + 256));
    return func_0035E750((sp + 256));
}
