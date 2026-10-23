/* Translation unit tu_100518 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern void * D_0040F0E8;
extern s32 func_0027C320();
extern void * D_0040F0E0;
extern s32 func_0010BC08();
extern s32 D_0040F4F0;
extern s32 func_0027C328();
extern s32 func_0027C348();
extern s32 func_001080C0();
extern s32 func_001080F0();
extern s32 func_002174E0();

void func_001005A0(void *arg0)
{
 do { M2C_FIELD(arg0, s32 *, 0x10290) = 0x200000; M2C_FIELD(arg0, s32 *, 0x10288) = 0 & 0xFFFFu; } while (0);
  M2C_FIELD(arg0, s32 *, 0x1028C) = 0;
}

void func_001005C0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xA0) = (s32) M2C_FIELD(D_0040F0E8, s32 *, 0x618);
    if (M2C_FIELD(arg0, s32 *, 0) == 0) {
        func_0027C320(arg0, M2C_FIELD(D_0040F0E0, s32 *, 0x2107C));
    }
    func_0010BC08(D_0040F4F0);
    func_0027C328(arg0);
}

/* Assembly between the functions: func_00100628 (2584 bytes) */

void func_00101040(void) {
    func_0027C348();
}

/* Assembly between the functions: func_00101060 (8 bytes), func_00101068 (1152 bytes), func_001014E8 (296 bytes), func_00101610 (232 bytes), func_001016F8 (8 bytes), func_00101700 (912 bytes), func_00101A90 (8 bytes), func_00101A98 (1256 bytes), func_00101F80 (16 bytes) */

void func_00101F90(void) {
    func_001080C0();
}

M2C_UNK * func_00101FB0(void) {
    if (func_001080C0() != 0) {
        return "Main";
    }
    if (func_001080F0() != 0) {
        return "Resource";
    }
    return "Unknown";
}

/* Assembly between the functions: func_00102000 (128 bytes), func_00102080 (64 bytes), func_001020C0 (2160 bytes), func_00102930 (672 bytes), func_00102BD0 (920 bytes), func_00102F68 (496 bytes) */

s32 func_00103158(void *arg0)
{
  func_002174E0(arg0 + 0x210A0);
  M2C_FIELD(arg0, s32 *, 0x21080) = (M2C_FIELD(arg0, s32 *, 0x2107C) = 0);
  return 1;
}

/* Assembly between the functions: func_001031A0 (88 bytes), func_001031F8 (176 bytes), func_001032A8 (176 bytes), func_00103358 (72 bytes), func_001033A0 (272 bytes), func_001034B0 (288 bytes), func_001035D0 (288 bytes), func_001036F0 (184 bytes), func_001037A8 (88 bytes) */

void func_00103800(void *arg0, s8 arg1)
{
  M2C_FIELD(arg0, s32 *, 0x21088) = 1;
  M2C_FIELD(arg0, s8 *, 0x210CB) = arg1;
}
