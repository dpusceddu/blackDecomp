#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 (*D_003C87E0)();

void func_002F8C38(s32 **arg0) {
    s32 temp_4;
    s32 temp_4_5;
    u32 temp_4_10;
    u32 temp_4_11;
    u32 temp_4_12;
    u32 temp_4_2;
    u32 temp_4_3;
    u32 temp_4_4;
    u32 temp_4_6;
    u32 temp_4_7;
    u32 temp_4_8;
    u32 temp_4_9;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x18);
    if (temp_4 != 0) {
        D_003C87E0(temp_4 - 0x10);
        M2C_FIELD(arg0, s32 *, 0x18) = 0;
    }
    temp_4_2 = M2C_FIELD(arg0, u32 *, 0x1C);
    if (temp_4_2 != 0) {
        D_003C87E0(temp_4_2);
        M2C_FIELD(arg0, u32 *, 0x1C) = 0U;
    }
    temp_4_3 = M2C_FIELD(arg0, u32 *, 0x20);
    if (temp_4_3 != 0) {
        D_003C87E0(temp_4_3);
        M2C_FIELD(arg0, u32 *, 0x20) = 0U;
    }
    temp_4_4 = M2C_FIELD(arg0, u32 *, 0x24);
    if (temp_4_4 != 0) {
        D_003C87E0(temp_4_4);
        M2C_FIELD(arg0, u32 *, 0x24) = 0U;
    }
    temp_4_5 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_4_5 != 0) {
        D_003C87E0(temp_4_5 - 0x10);
        M2C_FIELD(arg0, s32 *, 0x34) = 0;
    }
    temp_4_6 = M2C_FIELD(arg0, u32 *, 0x38);
    if (temp_4_6 != 0) {
        D_003C87E0(temp_4_6);
        M2C_FIELD(arg0, u32 *, 0x38) = 0U;
    }
    temp_4_7 = M2C_FIELD(arg0, u32 *, 0x3C);
    if (temp_4_7 != 0) {
        D_003C87E0(temp_4_7);
        M2C_FIELD(arg0, u32 *, 0x3C) = 0U;
    }
    temp_4_8 = M2C_FIELD(arg0, u32 *, 0x48);
    if (temp_4_8 != 0) {
        D_003C87E0(temp_4_8);
        M2C_FIELD(arg0, u32 *, 0x48) = 0U;
    }
    temp_4_9 = M2C_FIELD(arg0, u32 *, 0x4C);
    if (temp_4_9 != 0) {
        D_003C87E0(temp_4_9);
        M2C_FIELD(arg0, u32 *, 0x4C) = 0U;
    }
    temp_4_10 = M2C_FIELD(arg0, u32 *, 0x50);
    if (temp_4_10 != 0) {
        D_003C87E0(temp_4_10);
        M2C_FIELD(arg0, u32 *, 0x50) = 0U;
    }
    temp_4_11 = M2C_FIELD(arg0, u32 *, 0x40);
    if (temp_4_11 != 0) {
        D_003C87E0(temp_4_11);
        M2C_FIELD(arg0, u32 *, 0x40) = 0U;
    }
    temp_4_12 = M2C_FIELD(arg0, u32 *, 0x44);
    if (temp_4_12 != 0) {
        D_003C87E0(temp_4_12);
        M2C_FIELD(arg0, u32 *, 0x44) = 0U;
    }
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
}
