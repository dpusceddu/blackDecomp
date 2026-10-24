#include "ps2/prelude.h"

void func_001AF180(void *draw_list, s32 kind, s32 comparator) {
    M2C_FIELD(draw_list, s32 *, 0x14) = comparator;
    M2C_FIELD(draw_list, s32 *, 0x10) = kind;
    M2C_FIELD(draw_list, s32 *, 8) = 0;
    M2C_FIELD(draw_list, s32 *, 0xC) = 0;
    M2C_FIELD(draw_list, s32 *, 0) = 0;
    M2C_FIELD(draw_list, s32 *, 4) = 0;
}
