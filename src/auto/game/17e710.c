#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00173640(void *, f32);
extern f32 func_0018DD78();

void func_0017E710(void *arg0, s128 arg1) {
    func_00173640(arg0 + 0x18, func_0018DD78(M2C_FIELD(arg0, s32 *, 0x48)));
    M2C_FIELD(arg0, s8 *, 0x82) = 1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s128 *, 0x20) = arg1;
}
