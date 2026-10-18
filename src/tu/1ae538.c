#include "auto/prelude.h"

extern s32 func_002A90E8(s32);
extern s32 func_002A9140();
extern s32 func_0026A6F0(s32);
extern s32 func_0026A7A0();

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
