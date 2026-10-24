#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_00173640(void *, f32);
extern s32 func_00182550();

void func_00182EA8(void *arg0) {
    func_00173640(arg0 + 0x2C, 1.0f);
    func_00182550(arg0, 2);
}
