/* Translation unit tu_10a870 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0026F7E0(s32, M2C_UNK, M2C_UNK);
extern s32 func_00275340(void *);
extern s32 func_00275398(void *, M2C_UNK, void *);

s32 func_0010B160(s32 arg0) {
    s32 temp_16;
    s32 var_3;

    temp_16 = arg0 + 0x9B0;
    var_3 = func_0026F7E0(temp_16, 0, 0);
    if ((var_3 != 0) && (var_3 != 0xD)) {
        var_3 = func_0026F7E0(temp_16, 1, 0);
    }
    return var_3;
}

/* Assembly between the functions: func_0010B1B8 (16 bytes), func_0010B1C8 (56 bytes), func_0010B200 (56 bytes), func_0010B238 (56 bytes), func_0010B270 (56 bytes) */

void func_0010B2A8(void *arg0)
{
  s8 *new_var;
  M2C_FIELD(arg0, s8 *, 0x515) = 0;
  M2C_FIELD(arg0, s32 *, 0xC) = 1;
  arg0 += 0;
  new_var = (s8 *) arg0;
 do { *((s32 *) (new_var + 0x10)) = 0; } while (0);
}

void func_0010B2C0(void *arg0, s8 arg1)
{
  M2C_FIELD(arg0, s8 *, 0x517) = arg1;
  if ((arg1 && arg1) && arg1)
  {
  }
  M2C_FIELD(arg0, s32 *, 0xC) = 5;
 M2C_FIELD(arg0, s32 *, 0x1C) = 0; M2C_FIELD(arg0, s8 *, 0x515) = 0;
}

void func_0010B2D8(void *arg0)
{
  M2C_FIELD(arg0, s8 *, 0x515) = 0;
  M2C_FIELD(arg0, s32 *, 0x28) = 0;
  M2C_FIELD(arg0, s32 *, 0xC) = 9;
}

void func_0010B2F0(void *arg0)
{
  M2C_FIELD(arg0, s8 *, 0x515) = 0;
  M2C_FIELD(arg0, s32 *, 0x2C) = 0;
  *((s32 *) (0xC + ((s8 *) arg0))) = 6;
}

void func_0010B308(void *arg0)
{
  s8 *new_var;
  new_var = ((s8 *) arg0) + 0x515;
  M2C_FIELD(arg0, s32 *, 0x30) = (*((s8 *) new_var) = 0);
  M2C_FIELD(arg0, s32 *, 0xC) = 7;
}

s32 func_0010B320(s32 arg0) {
    return arg0 + 0x3A;
}

void * func_0010B328(void *arg0, void *arg1) {
    return arg0 + (((s32) arg1 << 6) + 0x34A);
}

/* Assembly between the functions: func_0010B338 (112 bytes), func_0010B3A8 (304 bytes) */

void func_0010B4D8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x4FC) = arg1;
}

/* Assembly between the functions: func_0010B4E0 (80 bytes) */

s32 func_0010B530(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s16 *, 0x4CA) = 0;
    M2C_FIELD(arg0, s16 *, 0x4CC) = 0;
    if ((arg1 != NULL) && (func_00275340(arg1) > 0)) {
        func_00275398(arg0 + 0x4CA, 0x14, arg1);
        return 1;
    }
    return 0;
}

s32 func_0010B590(s32 arg0) {
    return func_00275340(arg0 + 0x4CA) > 0;
}

/* Assembly between the functions: func_0010B5B0 (88 bytes) */

void func_0010B608(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x500) = arg1;
}

u8 func_0010B610(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x515);
}

void func_0010B618(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x516) = arg1;
}

s32 func_0010B620(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x4F8);
    M2C_FIELD(arg0, s32 *, 0x4F8) = 0;
    return temp_2;
}
