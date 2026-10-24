#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_004063E8[];
const char rodata_004063E8[88] __asm__("D_004063E8") __attribute__((aligned(8))) = "Q24Kaimt8CVarList1ZPQ24Kaim5CTeam" "\000\000\000\000\000\000\000" "Q34Kaimt8CVarList1ZPQ24Kaim5CTeam9CIterator" "\000\000\000\000\000";
extern s32 D_0049B4F8;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00406398;
extern s32 func_00370168();

s32 * func_0038CBA8(void) {
    if (D_0049B4F8 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00406398);
        }
        func_00370168(&D_0049B4F8, D_004063E8, &D_0040EBC0);
    }
    return &D_0049B4F8;
}
