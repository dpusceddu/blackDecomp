#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0020D960();
extern void func_0020D1A8();
extern void * D_0040F544;

void func_0020C4B8(s32 arg0) {
    func_0020D960();
    func_0020D1A8(D_0040F544 + 0xE90, arg0);
}
