#include "ps2/prelude.h"

extern s8 D_0040EAD8;
extern s32 func_002B4DD0();
extern s32 func_0027F730();
extern s32 func_0027F7D0();
extern s32 func_0027F818();

void func_00125060(s32 arg0) {
    M2C_UNK temp_16;
    s32 temp_17;

    temp_16 = (D_0040EAD8 != 0) ? 0x19 : 0x1E;
    func_002B4DD0(2);
    func_0027F730(temp_16);
    temp_17 = arg0 + 0x20120;
    func_0027F7D0(temp_17);
    func_0027F818(temp_17);
}
