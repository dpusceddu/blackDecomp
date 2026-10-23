#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 * func_0032E320();
extern M2C_UNK D_0043F3F0;

s32 func_0025CC48(s32 *arg0, s32 arg1) {
    return M2C_FIELD(((((s32) ((arg1 - *func_0032E320(*arg0)) * 0xBA2E8BA3) >> 4) * 4) + ((s32) &D_0043F3F0)), s32 *, 0);
}
