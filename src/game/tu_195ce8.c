#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00193980();
extern s32 func_00173640(u32 *, f32);

void func_00195CE8(void *arg0) {
    func_00193980();
    M2C_FIELD(arg0, s8 *, 8) = 0;
    func_00173640(arg0 + 0xC, 1.0f);
}
