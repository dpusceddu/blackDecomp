#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193980();
extern s32 func_00173690(void **);
extern s32 func_001825B0(void *);
extern s32 func_00193988();

void func_001973F0(s32 arg0) {
    func_00193980();
    func_00173690(arg0 + 0x20);
    func_00173690(arg0 + 0x24);
}

void func_00197428(void **arg0) {
    func_001825B0(*arg0 + 0x810);
    func_00193988(arg0);
}
