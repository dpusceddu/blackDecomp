/* Translation unit kynapse/tu_2dad10 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern M2C_UNK D_003E6438;
extern s32 func_002E7610();
extern M2C_UNK D_00450FD8;
extern M2C_UNK func_002DAD10;
extern M2C_UNK * D_004510E8;
extern M2C_UNK D_003E5E40;
extern s32 func_002DADD0();
extern unsigned int D_003E0040;
extern s32 (*D_003C87E0)();
extern s32 D_003E6428;

void * func_002DADA8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E6438;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    return arg0;
}

/* Assembly between the functions: func_002DADD0 (368 bytes), func_002DAF40 (512 bytes), func_002DB140 (1800 bytes), func_002DB848 (384 bytes), func_002DB9C8 (792 bytes), func_002DBCE0 (1368 bytes), func_002DC238 (1448 bytes) */

void func_002DC7E0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7610(&D_00450FD8, "CPointMapper", &func_002DAD10, 0, 0, 0);
            return;
        }
        D_004510E8 = &D_003E5E40;
    }
}

void func_002DC840(M2C_UNK **arg0, s32 arg1)
{
  *arg0 = &D_003E6438;
  arg0++;
  arg0--;
  func_002DADD0();
  *arg0 = &D_003E0040;
  if (arg1 & 1)
  {
    D_003C87E0(arg0);
  }
}

/* Assembly between the functions: func_002DC8A0 (144 bytes), func_002DC930 (192 bytes) */

void func_002DC9F0(void) {
    D_003E6428 = 0;
}

void func_002DCA00(void) {
    func_002DC7E0(1, 0xFFFF);
}

void func_002DCA20(void) {
    func_002DC7E0(0, 0xFFFF);
}
