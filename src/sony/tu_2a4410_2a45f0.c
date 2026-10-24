#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 D_003C1664;
extern M2C_UNK * func_0036D518();
extern s32 func_0036A460();
extern s32 func_002A4598();
extern s32 func_0036D568();
extern s32 D_003C1688;

s32 func_002A45F0(void) {
    M2C_UNK *temp_16;

    D_003C1664 = 1;
    temp_16 = func_0036D518();
    func_0036A460(0x80000012, func_002A4598, 0);
    if (temp_16 != NULL) {
        func_0036D568();
    }
    D_003C1664 = 0;
    D_003C1688 = 1;
    return 1;
}
