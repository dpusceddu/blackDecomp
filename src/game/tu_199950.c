#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00177F18(s32);
extern s32 func_0017B268(s32);

void func_00199950(s32 *arg0) {
    func_00177F18(*arg0 + 0x1F00);
    func_0017B268(*arg0 + 0x1F60);
}
