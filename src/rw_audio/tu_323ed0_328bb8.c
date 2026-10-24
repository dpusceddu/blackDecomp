#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00324640();
extern s32 func_003152C8(M2C_UNK *);
extern M2C_UNK D_0045C0C0;

s32 func_00328BB8(void) {
    return 0;
}

void func_00328BC0(void) {
    func_00324640();
}

s32 func_00328BE0(void) {
    return func_003152C8(&D_0045C0C0) != 0;
}
