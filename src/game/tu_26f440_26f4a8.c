/* Translation unit tu_26f440 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_00355B40();

s32 func_0026F4A8(s32 *arg0) {
    return *arg0;
}

void func_0026F4B0(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

s32 func_0026F4B8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x58);
}

/* Assembly between the functions: func_0026F4C0 (72 bytes) */

s32 func_0026F508(s32 arg0, s32 arg1)
{
  unsigned char new_var;
  new_var = 0;
  if (func_00355B40(*((s32 *) (((s8 *) arg0) + (0x54 ^ new_var))), arg1, 0, 1, arg0 + 0x94, arg0 + 0xCC) == 0)
  {
    return 1;
    do
    {
      arg0++;
      arg0--;
    }
    while (new_var);
  }
  func_0026F908(arg0, 0xD);
  return 0;
}

s32 func_0026F560(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xD8);
    if (temp_2 < 0) {
        return -1;
    }
    return temp_2 << 0xA;
}

/* Assembly between the functions: func_0026F580 (192 bytes), func_0026F640 (64 bytes), func_0026F680 (8 bytes), func_0026F688 (96 bytes), func_0026F6E8 (96 bytes), func_0026F748 (80 bytes), func_0026F798 (72 bytes), func_0026F7E0 (296 bytes) */

void func_0026F908(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x50) = 0xE;
    M2C_FIELD(arg0, s32 *, 0xD8) = -1;
    M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    M2C_FIELD(arg0, s32 *, 0x58) = arg1;
    M2C_FIELD(arg0, s32 *, 0xD0) = 0;
    if (arg1 == 3) {
        M2C_FIELD(arg0, s32 *, 0xD4) = 0;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0xD4) = 1;
}

/* Assembly between the functions: func_0026F948 (136 bytes) */

s32 func_0026F9D0(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x0:
        return 0;
    case 0x6F:
    case 0x13:
        func_0026F908(arg0, 1);
block_13:
        return 0xD;
    case 0x1C:
        func_0026F908(arg0, 0xB);
        goto block_13;
    case 0x17:
        func_0026F908(arg0, 0xC);
        goto block_13;
    default:
        func_0026F908(arg0, 0xD);
        goto block_13;
    }
}

s32 func_0026FA70(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_5;

    if (arg1 >= 0) {
        if (arg2 != 0) {
            M2C_FIELD(arg2, s32 *, 0) = arg1;
        }
        return 0;
    }
    temp_5 = arg1 & 0xFFFF;
    if ((temp_5 == 0x13) || (temp_5 == 0x6F)) {
        func_0026F908(arg0, 1);
    } else {
        func_0026F908(arg0, 0xD);
    }
    return 0xD;
}

s32 func_0026FAD0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_5;

    if (arg1 >= 0) {
        if (arg2 != 0) {
            M2C_FIELD(arg2, s32 *, 0) = arg1;
        }
        return 0;
    }
    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x1C:
        func_0026F908(arg0, 0xB);
        break;
    case 0x6F:
    case 0x13:
        func_0026F908(arg0, 1);
        break;
    default:
        func_0026F908(arg0, 0xD);
        break;
    }
    return 0xD;
}

s32 func_0026FB60(s32 arg0, s32 arg1) {
    s32 temp_5;
    s32 var_2;

    temp_5 = arg1 & 0xFFFF;
    if (temp_5 == 0x13) {
        goto block_5;
    }
    if (temp_5 >= 0x14) {
        goto block_4;
    }
    var_2 = 0;
    if (temp_5 == 0) {
        goto block_8;
    }
    goto block_6;
block_4:
    if (temp_5 != 0x6F) {
        goto block_6;
    }
block_5:
    func_0026F908(arg0, 1);
    goto block_7;
block_6:
    func_0026F908(arg0, 0xD);
block_7:
    var_2 = 0xD;
block_8:
    return var_2;
}

/* Assembly between the functions: func_0026FBC0 (128 bytes), func_0026FC40 (312 bytes), func_0026FD78 (264 bytes) */

s32 func_0026FE80(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x0:
        return 0;
    case 0x14:
    case 0x16:
        func_0026F908(arg0, 9);
block_12:
        return 0xD;
    case 0x6F:
    case 0x13:
        func_0026F908(arg0, 1);
        goto block_12;
    default:
        func_0026F908(arg0, 0xD);
        goto block_12;
    }
}

s32 func_0026FF10(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x0:
        return 0;
    case 0x16:
    case 0x14:
    case 0x2:
        func_0026F908(arg0, 9);
block_15:
        return 0xD;
    case 0x13:
    case 0x6F:
        func_0026F908(arg0, 1);
        goto block_15;
    default:
        func_0026F908(arg0, 0xD);
        goto block_15;
    }
}
