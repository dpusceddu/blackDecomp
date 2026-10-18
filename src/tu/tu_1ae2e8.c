/* Translation unit tu_1ae2e8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0027B2C8();
extern s32 func_001C6608();
extern s32 func_001B0A20();
extern s32 func_001B0068();
extern s32 func_001B0FC8();
extern s32 func_002A90E8(s32);
extern s32 func_002A9140();
extern s32 func_0026A6F0(s32);
extern s32 func_0026A7A0();
extern s32 func_0027B260(s32);
extern s32 func_001AEA18();

s32 func_001AE3A8(s32 arg0) {
    func_0027B2C8(arg0 + 0xD360);
    func_0027B2C8(arg0 + 0xD400);
    func_0027B2C8(arg0 + 0xD4A0);
    func_001C6608(arg0 + 0xD170);
    func_001B0A20(arg0 + 0xD290);
    func_001B0068(arg0 + 0xCBE0);
    func_001B0FC8(arg0 + 0xD350);
    return 1;
}

/* Assembly between the functions: func_001AE420 (280 bytes) */

void func_001AE538(void *arg0) {
    func_002A90E8(M2C_FIELD(M2C_FIELD(arg0, void **, 0xD540), s32 *, 0x58));
    M2C_FIELD(arg0, void **, 0xD540) = NULL;
}

void func_001AE570(s32 arg0)
{
  int new_var;
  s32 *new_var2;
  new_var = arg0 + 0xD360;
  new_var2 = (s32 *) (((s8 *) new_var) + 0x58);
  func_002A9140(*new_var2, 0, 1);
}

void func_001AE5A0(void *arg0) {
    func_0026A6F0(M2C_FIELD(arg0, s32 *, 0xD540));
}

void func_001AE5C8(void) {
    func_0026A7A0();
}

/* Assembly between the functions: func_001AE5E8 (632 bytes), func_001AE860 (144 bytes) */

void func_001AE8F0(s32 arg0) {
    func_0027B260(arg0 + 0xD400);
    func_0027B260(arg0 + 0xD4A0);
    func_0027B260(arg0 + 0xD360);
}

/* Assembly between the functions: func_001AE938 (96 bytes), func_001AE998 (96 bytes) */

s32 func_001AE9F8(s32 arg0) {
    return func_001AEA18(arg0, 0);
}
