#include "ps2/prelude.h"

void func_00166C00(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0xA0) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x22) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x20) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0xA0) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0xA4) = arg1;
block_6:
    return;
}

void func_00166C30(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x48) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 2) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x4C) = arg1;
block_6:
    return;
}

void func_00166C60(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x50) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 6) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 4) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x50) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x54) = arg1;
block_6:
    return;
}

void func_00166C90(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x58) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 8) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x58) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x5C) = arg1;
block_6:
    return;
}

void func_00166CC0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x60) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0xE) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0xC) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x60) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x64) = arg1;
block_6:
    return;
}

void func_00166CF0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x68) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x10) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x68) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x6C) = arg1;
block_6:
    return;
}

void func_00166D20(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x70) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x16) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x14) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x70) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x74) = arg1;
block_6:
    return;
}

void func_00166D50(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x78) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x1A) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x18) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x78) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x7C) = arg1;
block_6:
    return;
}

void func_00166D80(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x1E) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x1C) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x80) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x84) = arg1;
block_6:
    return;
}

void func_00166DB0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x88) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x26) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x24) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x88) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x8C) = arg1;
block_6:
    return;
}

void func_00166DE0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x90) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x2A) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x28) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x90) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x94) = arg1;
block_6:
    return;
}

void func_00166E10(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0x98) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x2C) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0x98) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0x9C) = arg1;
block_6:
    return;
}

void func_00166E40(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0xA8) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x30) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0xA8) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0xAC) = arg1;
block_6:
    return;
}

void func_00166E70(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0xB0) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x36) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x34) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0xB0) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0xB4) = arg1;
block_6:
    return;
}

void func_00166EA0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0xB8) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x3A) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x38) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0xB8) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0xBC) = arg1;
block_6:
    return;
}

void func_00166ED0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0xC0) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x3E) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x3C) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0xC0) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0xC4) = arg1;
block_6:
    return;
}

void func_00166F00(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0xC8) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x42) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x40) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0xC8) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0xCC) = arg1;
block_6:
    return;
}

void func_00166F30(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, s32 *, 0xD0) == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x46) = (s16) arg2;
    goto block_5;
block_3:
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) arg2;
    M2C_FIELD(arg0, s32 *, 0xD0) = arg1;
    return;
block_5:
    M2C_FIELD(arg0, s32 *, 0xD4) = arg1;
block_6:
    return;
}

s32 func_00166F60(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xD0);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x46) = 0;
        M2C_FIELD(arg0, s32 *, 0xD4) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x44) = 0;
    M2C_FIELD(arg0, s32 *, 0xD0) = 0;
    return temp_2;
}

s32 func_00166F80(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x48);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 2) = 0;
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    return temp_2;
}

s32 func_00166FA0(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x50);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 6) = 0;
        M2C_FIELD(arg0, s32 *, 0x54) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    return temp_2;
}

s32 func_00166FC0(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x58);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0xA) = 0;
        M2C_FIELD(arg0, s32 *, 0x5C) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    return temp_2;
}

s32 func_00166FE0(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x60);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0xE) = 0;
        M2C_FIELD(arg0, s32 *, 0x64) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    return temp_2;
}
