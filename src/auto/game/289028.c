#include "auto/prelude.h"

extern char D_00400A08[];
const char rodata_00400A08[104] __asm__("D_00400A08") __attribute__((aligned(8))) = "%d" "\000\000\000\000\000\000" "RawData" "\000" "Graph" "\000\000\000" "AdditionalData" "\000\000" "CFindNearestData" "\000\000\000\000\000\000\000\000" "CAstarData" "\000\000\000\000\000\000" "UpdateWithPathObjects" "\000\000\000";
extern s32 func_0035D728();
extern s32 func_00288EF8();

M2C_UNK *** func_00289028(M2C_UNK ***arg0, M2C_UNK ***arg1, M2C_UNK *arg2, M2C_UNK *arg3) {
    u8 sp[8];
    func_0035D728(sp, D_00400A08, arg3);
    func_00288EF8(arg0, arg1, arg2, sp);
    return arg0;
}
