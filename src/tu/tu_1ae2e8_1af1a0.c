/* Translation unit tu_1ae2e8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_001AF180();
extern M2C_UNK func_001CA258;
extern M2C_UNK func_001CA208;
extern s32 func_001AF1C0();
extern s32 func_001AF298();

s32 func_001AF1A0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 0xC) = arg3;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    return 1;
}

void func_001AF1B8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

/* Assembly between the functions: func_001AF1C0 (216 bytes), func_001AF298 (552 bytes) */

void func_001AF4C0(void *arg0) {
    func_001AF180(arg0 + 0xCA58, 0, &func_001CA258);
    func_001AF180(arg0 + 0xCA70, 1, &func_001CA258);
    func_001AF180(arg0 + 0xCA88, 2, &func_001CA208);
    func_001AF180(arg0 + 0xCAA0, 3, NULL);
    func_001AF180(arg0 + 0xCAB8, 4, NULL);
    func_001AF180(arg0 + 0xCAD0, 5, NULL);
    func_001AF180(arg0 + 0xCAE8, 6, NULL);
}

/* Assembly between the functions: func_001AF580 (336 bytes), func_001AF6D0 (104 bytes) */

void * func_001AF738(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6, void *arg7) {
    return func_001AF1C0(arg0 + ((M2C_FIELD(arg1, u8 *, 9) * 0x18) + 0xCA58), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

void func_001AF768(s32 arg0, s32 arg1)
{
  int new_var;
  s32 temp_5;
 do { new_var = (arg1 * 0x18) + 0xCA58; temp_5 = new_var; } while (0);
  func_001AF298(arg0 + temp_5, temp_5);
}
