#include "ps2/prelude.h"

s16 func_00122368(void **arg0, s32 arg1) {
    if (arg1 & 1) {
        return M2C_FIELD(*arg0, s16 *, 0x1C);
    }
    if (arg1 & 2) {
        return M2C_FIELD(*arg0, s16 *, 0x22);
    }
    if (arg1 & 4) {
        return M2C_FIELD(*arg0, s16 *, 0x24);
    }
    if (arg1 & 8) {
        return M2C_FIELD(*arg0, s16 *, 0x26);
    }
    if (arg1 & 0x10) {
        return M2C_FIELD(*arg0, s16 *, 0x28);
    }
    if (arg1 & 0x20) {
        return M2C_FIELD(*arg0, s16 *, 0x2A);
    }
    if (arg1 & 0x40) {
        return M2C_FIELD(*arg0, s16 *, 0x2C);
    }
    if (arg1 & 0x80) {
        return M2C_FIELD(*arg0, s16 *, 0x2E);
    }
    if (arg1 & 0x100) {
        return M2C_FIELD(*arg0, s16 *, 0x30);
    }
    if (arg1 & 0x200) {
        return M2C_FIELD(*arg0, s16 *, 0x32);
    }
    if (arg1 & 0x400) {
        return M2C_FIELD(*arg0, s16 *, 0x34);
    }
    if (arg1 & 0x800) {
        return M2C_FIELD(*arg0, s16 *, 0x36);
    }
    if (arg1 & 0x1000) {
        return M2C_FIELD(*arg0, s16 *, 0x38);
    }
    return 0;
}
