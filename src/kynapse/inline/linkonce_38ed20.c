#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00406CD0[];
const char rodata_00406CD0[72] __asm__("D_00406CD0") __attribute__((aligned(8))) = "Q24Kaim12CTimeManager" "\000\000\000" "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity9CIterator" "\000\000\000";
extern s32 D_0049BA90;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00406C78;
extern s32 func_00370168();

s32 * func_0038ED20(void) {
    if (D_0049BA90 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00406C78);
        }
        func_00370168(&D_0049BA90, D_00406CD0, &D_0040EBC0);
    }
    return &D_0049BA90;
}
