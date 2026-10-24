#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00406100[];
const char rodata_00406100[64] __asm__("D_00406100") __attribute__((aligned(8))) = "Q24Kaim7CObject" "\000" "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity9CIterator" "\000\000\000";
extern s32 D_0049B070;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();
extern M2C_UNK D_00406180;

s32 * func_0038C020(void) {
    if (D_0049B070 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, D_00406100);
        }
        func_00370168(&D_0049B070, &D_00406180, &D_0040EBC0);
    }
    return &D_0049B070;
}
