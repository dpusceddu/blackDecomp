#include "ps2/prelude.h"

extern char D_00400B00[];
const char rodata_00400B00[72] __asm__("D_00400B00") __attribute__((aligned(8))) = "MaxTeam" "\000" "Service" "\000" "Entity" "\000\000" "_Name" "\000\000\000" "ActionClass" "\000\000\000\000\000" "Brain" "\000\000\000" "Team" "\000\000\000\000" "Agent" "\000\000\000";
extern s32 func_00289028();

M2C_UNK ** func_002891D8(M2C_UNK ***arg0) {
    u8 sp[8];
    func_00289028(sp, arg0, D_00400B00, M2C_FIELD(arg0, M2C_UNK **, 4));
    return M2C_FIELD(arg0, M2C_UNK ***, 0);
}
