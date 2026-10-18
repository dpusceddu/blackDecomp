/* Translation unit kynapse/tu_30ea38 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0030F678();
extern s32 func_0030FD68();

s32 func_0030FFA0(s32 arg0)
{
  s8 *new_var;
  M2C_FIELD(arg0, s8 *, 0x49) = 0;
  new_var = ((s8 *) arg0) + 0x51;
  M2C_FIELD(arg0, s32 *, 0x18) = 0;
  M2C_FIELD(arg0, s8 *, 0x48) = 1;
  *((s8 *) new_var) = 1;
  func_0030F678(arg0);
  return M2C_FIELD(arg0, s32 *, 0x18);
}

s32 func_0030FFE0(s32 arg0)
{
  M2C_FIELD(arg0, s8 *, 0x49) = 0;
  M2C_FIELD(arg0, s8 *, 0x48) = 1;
  M2C_FIELD(arg0, s32 *, 0x1C) = 0;
  M2C_FIELD(arg0, s8 *, 0x51) = 1;
  func_0030F678(arg0);
  return M2C_FIELD(arg0, s32 *, 0x1C);
}

s32 func_00310020(s32 arg0) {
    M2C_FIELD(arg0, s8 *, 0x49) = 0;
    M2C_FIELD(arg0, s8 *, 0x48) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s8 *, 0x50) = 1;
    func_0030F678(arg0);
    return M2C_FIELD(arg0, s32 *, 0x20);
}

s32 func_00310060(s32 arg0)
{
  *((s8 *) (((s8 *) arg0) + (0x48 & 0xFFFFFFFF))) = 0;
  M2C_FIELD(arg0, s32 *, 0x24) = 0x48 * 0;
  M2C_FIELD(arg0, s8 *, 0x52) = (M2C_FIELD(arg0, s8 *, 0x49) = 1);
  func_0030F678(arg0);
  return M2C_FIELD(arg0, s32 *, 0x24);
}

s32 func_003100A0(s32 arg0)
{
  M2C_FIELD(arg0, s8 *, 0x48) = 0;
  M2C_FIELD(arg0, s32 *, 0x28) = 0;
  M2C_FIELD(arg0, s8 *, 0x52) = 1;
  arg0++;
  arg0--;
  M2C_FIELD(arg0, s8 *, 0x49) = 1;
  func_0030F678(arg0);
  return M2C_FIELD(arg0, s32 *, 0x28);
}

s32 func_003100E0(s32 arg0) {
    M2C_FIELD(arg0, s8 *, 0x49) = 0;
    M2C_FIELD(arg0, s8 *, 0x48) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s8 *, 0x50) = 1;
    func_0030F678(arg0);
    return M2C_FIELD(arg0, s32 *, 0x2C);
}

/* Assembly between the functions: func_00310120 (112 bytes) */

void func_00310190(s32 arg0, void *arg1) {
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x18)) {
        M2C_FIELD(arg1, s32 *, 0x18) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x1C)) {
        M2C_FIELD(arg1, s32 *, 0x1C) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x20)) {
        M2C_FIELD(arg1, s32 *, 0x20) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x24)) {
        M2C_FIELD(arg1, s32 *, 0x24) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x28)) {
        M2C_FIELD(arg1, s32 *, 0x28) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x2C)) {
        M2C_FIELD(arg1, s32 *, 0x2C) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
}

void func_00310228(void) {
    func_0030FD68(1, 0xFFFF);
}

void func_00310248(void) {
    func_0030FD68(0, 0xFFFF);
}
