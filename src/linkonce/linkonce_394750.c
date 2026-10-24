#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00408B70[];
const char rodata_00408B70[104] __asm__("D_00408B70") __attribute__((aligned(8))) = "Q34Kaimt8CVarList1ZQ24Kaim4CGap5CCell" "\000\000\000" "Q34Kaimt8CVarList1ZQ24Kaim4CGap9CIterator" "\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BE70;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00408B18;
extern s32 func_00370168();

s32 * func_00394750(void) {
    if (D_0049BE70 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00408B18);
        }
        func_00370168(&D_0049BE70, D_00408B70, &D_0040EBC0);
    }
    return &D_0049BE70;
}
