#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00167088(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x70);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x16) = 0;
        M2C_FIELD(arg0, s32 *, 0x74) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x70) = 0;
    return temp_2;
}

s32 func_001670A8(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x88);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x26) = 0;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x88) = 0;
    return temp_2;
}

s32 func_001670C8(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x90);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x2A) = 0;
        M2C_FIELD(arg0, s32 *, 0x94) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    return temp_2;
}

s32 func_001670E8(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x98);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x2E) = 0;
        M2C_FIELD(arg0, s32 *, 0x9C) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x98) = 0;
    return temp_2;
}

s32 func_00167108(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x78);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x1A) = 0;
        M2C_FIELD(arg0, s32 *, 0x7C) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x78) = 0;
    return temp_2;
}

s32 func_00167128(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x80);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x1E) = 0;
        M2C_FIELD(arg0, s32 *, 0x84) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x80) = 0;
    return temp_2;
}

s32 func_00167148(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xA0);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x22) = 0;
        M2C_FIELD(arg0, s32 *, 0xA4) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    return temp_2;
}

s32 func_00167168(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xA8);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x32) = 0;
        M2C_FIELD(arg0, s32 *, 0xAC) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    return temp_2;
}

s32 func_00167188(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xB0);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x36) = 0;
        M2C_FIELD(arg0, s32 *, 0xB4) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x34) = 0;
    M2C_FIELD(arg0, s32 *, 0xB0) = 0;
    return temp_2;
}

s32 func_001671A8(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xB8);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x3A) = 0;
        M2C_FIELD(arg0, s32 *, 0xBC) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x38) = 0;
    M2C_FIELD(arg0, s32 *, 0xB8) = 0;
    return temp_2;
}

s32 func_001671C8(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xC0);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x3E) = 0;
        M2C_FIELD(arg0, s32 *, 0xC4) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x3C) = 0;
    M2C_FIELD(arg0, s32 *, 0xC0) = 0;
    return temp_2;
}

s32 func_001671E8(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xC8);
    if (arg1 != temp_2) {
        M2C_FIELD(arg0, s16 *, 0x42) = 0;
        M2C_FIELD(arg0, s32 *, 0xCC) = 0;
        return temp_2;
    }
    M2C_FIELD(arg0, s16 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0xC8) = 0;
    return temp_2;
}
