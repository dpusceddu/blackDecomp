#include "auto/prelude.h"

extern s32 func_0018DE48();

s32 func_0018E5B8(s32 arg0, s32 arg1) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 4);
    return func_0018DE48((s32) (temp_4 + 0xC94), arg1, M2C_FIELD(temp_4, s32 *, 0x754));
}
