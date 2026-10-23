#include "auto/prelude.h"

extern s32 func_00193B40();

u8 func_00193A08(void **arg0) {
    return M2C_FIELD(func_00193B40(arg0), u8 *, 8);
}
