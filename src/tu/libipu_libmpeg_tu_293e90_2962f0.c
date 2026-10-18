/* Translation unit libipu_libmpeg/tu_293e90 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_0036A038();
extern s32 func_00369FF0();
extern void func_00296468();
extern s32 func_00298CF0();

void func_002962F0(M2C_UNK *arg0) {
    func_0036A038("[MPEG ERROR]%s\n", arg0);
}

/* Assembly between the functions: func_00296300 (160 bytes), func_002963A0 (200 bytes), func_00296468 (88 bytes) */

void func_002964C0(M2C_UNK *arg0, s32 arg1, s32 arg2) {
    u8 sp[248] __attribute__((aligned(16)));
    func_00369FF0(sp, 0x100, arg1, arg2);
    func_00296468(arg0, sp);
}

/* Assembly between the functions: func_00296500 (392 bytes), func_00296688 (1800 bytes), func_00296D90 (592 bytes), func_00296FE0 (1160 bytes), func_00297468 (544 bytes), func_00297688 (576 bytes), func_002978C8 (816 bytes), func_00297BF8 (1064 bytes), func_00298020 (416 bytes), func_002981C0 (1368 bytes), func_00298718 (376 bytes), func_00298890 (360 bytes) ... */

void func_00298DC0(void) {
    func_00298CF0();
}
