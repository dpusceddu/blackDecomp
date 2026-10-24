#include "ps2/prelude.h"

extern s32 func_00348A90(s32, s32);
extern s32 func_00352A30(s8 *arg0);

void func_00348B18(s32 arg0, s8 *arg1) {
    func_00348A90(arg0, func_00352A30(arg1));
}
