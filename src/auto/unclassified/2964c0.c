#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00369FF0();
extern void func_00296468();

void func_002964C0(M2C_UNK *arg0, s32 arg1, s32 arg2) {
    u8 sp[248] __attribute__((aligned(16)));
    func_00369FF0(sp, 0x100, arg1, arg2);
    func_00296468(arg0, sp);
}
