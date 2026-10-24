/* Translation unit tu_1f9028 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_001F1C08();
extern void func_00200A68(void *arg0);
extern s32 func_001F9028(void *);
extern s32 func_001FA468(void *);

void func_001F9980(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xB90) = 1;
}

/* Assembly between the functions: func_001F9990 (176 bytes), func_001F9A40 (184 bytes), func_001F9AF8 (232 bytes), func_001F9BE0 (480 bytes), func_001F9DC0 (40 bytes), func_001F9DE8 (200 bytes) */

void func_001F9EB0(void *arg0) {
    func_001F1C08();
    M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    M2C_FIELD(arg0, s32 *, 0xA4) = 0;
    func_00200A68(arg0 + 0x20);
    func_001F9028(arg0 + 0xC0);
    func_001FA468(arg0 + 0xC80);
    M2C_FIELD(arg0, s32 *, 0xEA8) = 0;
}

/* Assembly between the functions: func_001F9EF8 (568 bytes), func_001FA130 (632 bytes), func_001FA3A8 (144 bytes), func_001FA438 (48 bytes), func_001FA468 (112 bytes), func_001FA4D8 (384 bytes), func_001FA658 (1344 bytes) */

s32 func_001FAB98(void) {
    return 1;
}
