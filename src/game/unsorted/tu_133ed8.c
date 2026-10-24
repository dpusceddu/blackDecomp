#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00142F50(void *);
extern s32 func_001394B8(void *, s32);
extern s32 D_0040F514;
extern s32 func_00133F80(s32 *);
extern s32 func_001A5EE8(void *);
extern s32 func_001B6CF8(s32, s32 *, s32);
extern void * D_0040F4D8;

s32 func_00133ED8(s32 *arg0) {
    s32 *var_16;
    s32 temp_4;
    s32 var_18;

    var_16 = (s32 *) (((s8 *) arg0) + 0x25C);
    var_18 = 7;
    do {
        temp_4 = *var_16;
        var_18 -= 1;
        if (temp_4 != 0) {
            func_00142F50((void *) temp_4);
        }
        var_16 = (s32 *) (((s8 *) var_16) + 4);
    } while (var_18 >= 0);
    func_001394B8((void *) D_0040F514, (s32) arg0);
    func_00133F80(arg0);
    func_001A5EE8(M2C_FIELD(arg0, void **, 0x330));
    func_001B6CF8((s32) ((void *) (((s8 *) D_0040F4D8) + 0x66290)), arg0, 1);
    M2C_FIELD(arg0, s64 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 0x38C) = 4;
    M2C_FIELD(arg0, s32 *, 0x348) = 0;
    return 1;
}
