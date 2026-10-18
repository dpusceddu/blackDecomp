#include "auto/prelude.h"

extern char D_00409080[];
extern char D_004090C0[];
const char rodata_00409080[64] __asm__("D_00409080") __attribute__((aligned(8))) = "Q24Kaim7CObject" "\000" "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity9CIterator" "\000\000\000";
const char rodata_004090C0[24] __asm__("D_004090C0") __attribute__((aligned(8))) = "Q24Kaim11CInfoEntity" "\000\000\000\000";
extern s32 D_0049BEB0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_00394C68(void) {
    if (D_0049BEB0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, D_00409080);
        }
        func_00370168(&D_0049BEB0, D_004090C0, &D_0040EBC0);
    }
    return &D_0049BEB0;
}
