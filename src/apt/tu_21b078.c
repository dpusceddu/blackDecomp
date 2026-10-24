#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00250058(void *, s32);
extern void * D_0043DEE0;

s32 * func_0021B078(s32 arg0) {
    s32 *temp_2;

    temp_2 = func_00250058(D_0043DEE0, arg0 + 4);
    *temp_2 = arg0;
    return (s32 *) (((s8 *) temp_2) + 4);
}
