/* Translation unit libkernl/tu_36a168 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 D_00483C80;
extern M2C_UNK D_00483AD8;
extern s32 D_00483AE4;
extern s32 D_00483AEC;
extern void func_0036A410();
extern s32 D_003D716C;
extern s32 func_0036A6A0();

s32 func_0036A168(s32 arg0) {
    return (&D_00483C80)[arg0];
}

/* Assembly between the functions: func_0036A180 (16 bytes), func_0036A190 (640 bytes), func_0036A410 (56 bytes) */

s32 func_0036A448(s32 arg0, s32 arg1)
{
  s32 temp_2;
  M2C_UNK *new_var;
  new_var = &D_00483AD8;
  temp_2 = M2C_FIELD(new_var, s32 *, 0x14);
  M2C_FIELD(new_var, s32 *, 0x14) = arg0;
  M2C_FIELD(new_var, s32 *, 0x18) = arg1;
  return temp_2;
}

/* Assembly between the functions: func_0036A460 (120 bytes) */

void func_0036A4D8(s32 arg0) {
    if (arg0 < 0) {
        M2C_FIELD((((arg0 & 0x7FFFFFFF) * 0xC) + D_00483AE4), s32 *, 0) = 0;
        return;
    }
    M2C_FIELD(((arg0 * 0xC) + D_00483AEC), s32 *, 0) = 0;
}

/* Assembly between the functions: func_0036A528 (312 bytes), func_0036A660 (64 bytes), func_0036A6A0 (64 bytes), func_0036A6E0 (328 bytes), func_0036A828 (172 bytes), func_0036A8D4 (4 bytes), func_0036A8D8 (416 bytes) */

void func_0036AA78(void)
{
  func_0036A410();
  D_003D716C = 0 & 0xFFFFFFFFFFFFFFFF;
}

/* Assembly between the functions: func_0036AAA0 (168 bytes) */

void func_0036AB48(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) & 0xFFFFFFFE);
}

s32 func_0036AB68(void *arg0)
{
  s32 temp_hi;
  s8 *new_var;
  s32 new_var2;
  temp_hi = ((s32) (M2C_FIELD(arg0, s32 *, 0x24))) % ((s32) (M2C_FIELD(arg0, s32 *, 0x18)));
  new_var2 = temp_hi << 6;
  new_var = (s8 *) arg0;
  *((s32 *) (new_var + 0x24)) = (s32) (temp_hi + 1);
  return (M2C_FIELD(arg0, s32 *, 0x14)) + new_var2;
}

s32 func_0036AB98(s32 arg0, s32 arg1) {
    if (arg1 < 0) {
        goto block_4;
    }
    if (arg1 >= M2C_FIELD(arg0, s32 *, 0x20)) {
        goto block_3;
    }
    goto block_5;
block_3:
block_4:
    return func_0036AB68(arg0);
block_5:
    return M2C_FIELD(arg0, s32 *, 0x1C) + (arg1 << 6);
}

/* Assembly between the functions: func_0036ABD8 (208 bytes) */

s32 func_0036ACA8(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    return (func_0036A6A0(0x80000008, arg3, 0x40, M2C_FIELD(arg3, s32 *, 0x24), M2C_FIELD(arg3, s32 *, 0x28), M2C_FIELD(arg3, s32 *, 0x2C)) != 0) ? 0 : 0x800;
}

/* Assembly between the functions: func_0036ACE8 (208 bytes), func_0036ADB8 (8 bytes), func_0036ADC0 (80 bytes) */

s32 func_0036AE10(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    return (func_0036A6A0(0x80000008, arg3, 0x40, 0, 0, 0) != 0) ? 0 : 0x800;
}

/* Assembly between the functions: func_0036AE50 (208 bytes), func_0036AF20 (336 bytes), func_0036B070 (144 bytes), func_0036B100 (512 bytes) */

s32 func_0036B300(void *arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0);
    if ((temp_5 == NULL) || (M2C_FIELD(arg0, s32 *, 4) != M2C_FIELD(temp_5, s32 *, 0x18)) || !(M2C_FIELD(temp_5, s32 *, 0x10) & 1)) {
        return 0;
    }
    return 1;
}
