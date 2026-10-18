/* Translation unit tu_10bbf8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0010B5B0();
extern s32 func_0010B160();

s32 func_0010BC00(void) {
    return 1;
}

void func_0010BC08(void) {

}

/* Assembly between the functions: func_0010BC10 (1768 bytes), func_0010C2F8 (160 bytes), func_0010C398 (1360 bytes), func_0010C8E8 (1584 bytes), func_0010CF18 (2776 bytes), func_0010D9F0 (1792 bytes), func_0010E0F0 (936 bytes), func_0010E498 (344 bytes), func_0010E5F0 (304 bytes) */

void func_0010E720(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x515) = 1;
    func_0010B5B0();
}

/* Assembly between the functions: func_0010E740 (896 bytes) */

s32 func_0010EAC0(s32 arg0, s32 arg1) {
    func_0010B160(arg0);
    M2C_FIELD(arg0, s32 *, 0x34) = arg1;
    return 1;
}

/* Assembly between the functions: func_0010EAF8 (200 bytes) */

s32 func_0010EBC0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x34) == 0x1F;
}
