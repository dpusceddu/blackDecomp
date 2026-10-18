/* Translation unit apt/tu_24ad08 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00386EC8();
extern M2C_UNK D_003E22B8;
extern u16 D_003BFAF8;
extern s32 func_00253FF0();

s32 func_0024AD08(s32 arg0) {
    func_00386EC8(arg0, 1);
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E22B8;
    M2C_FIELD(arg0, u16 **, 8) = &D_003BFAF8;
    D_003BFAF8 += 1;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    return arg0;
}

/* Assembly between the functions: func_0024AD60 (144 bytes) */

s32 func_0024ADF0(s32 arg0, s32 arg1) {
    func_00386EC8(arg0, 1);
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E22B8;
    func_00253FF0(arg0 + 8, arg1);
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    return arg0;
}
