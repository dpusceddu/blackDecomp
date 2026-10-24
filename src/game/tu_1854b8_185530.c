/* Translation unit tu_1854b8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern void func_0018BFE8();
extern s32 func_00181B08();
extern s32 func_00173FB8(s32);

void func_00185530(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x68) = arg1;
}

/* Assembly between the functions: func_00185538 (192 bytes), func_001855F8 (184 bytes), func_001856B0 (88 bytes), func_00185708 (144 bytes), func_00185798 (216 bytes) */

void func_00185870(s32 *arg0) {
    u8 sp[24];
    func_0018BFE8(sp);
    func_00181B08(*arg0 + 0xEC0, sp);
}

/* Assembly between the functions: func_001858A8 (456 bytes), func_00185A70 (224 bytes), func_00185B50 (48 bytes), func_00185B80 (40 bytes), func_00185BA8 (144 bytes) */

void func_00185C38(s32 arg0) {
    func_00173FB8(arg0 + 0x2C);
}
