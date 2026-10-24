#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049BE50;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00408B18;
extern s32 func_00370168();

s32 * func_00394620(void) {
    if (D_0049BE50 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00408B18);
        }
        func_00370168(&D_0049BE50, "Q24Kaimt8CVarList1ZQ24Kaim4CGap", &D_0040EBC0);
    }
    return &D_0049BE50;
}
