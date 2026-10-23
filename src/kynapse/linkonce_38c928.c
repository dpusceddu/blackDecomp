#include "auto/prelude.h"

extern char D_004062F8[];
const char rodata_004062F8[88] __asm__("D_004062F8") __attribute__((aligned(8))) = "Q24Kaimt8CVarList1ZPQ24Kaim7CEntity" "\000\000\000\000\000" "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity9CIterator" "\000\000\000";
extern s32 D_0049B0C0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_004062E8;
extern s32 func_00370168();

s32 * func_0038C928(void) {
    if (D_0049B0C0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_004062E8);
        }
        func_00370168(&D_0049B0C0, D_004062F8, &D_0040EBC0);
    }
    return &D_0049B0C0;
}
