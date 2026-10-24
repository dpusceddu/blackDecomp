#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

void func_001E0930(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    u32 temp_3;
    void *temp_4;
    void *temp_4_2;

    temp_3 = M2C_FIELD(arg0, u32 *, 0x2410);
    if (temp_3 < 0x40U) {
        temp_4 = (temp_3 * 0x50) + arg0;
        M2C_FIELD(temp_4, s128 *, 0xD0) = (s128) M2C_FIELD(arg1, s128 *, 0);
        temp_4_2 = temp_4 + 0xD0;
        M2C_FIELD(temp_4_2, s128 *, 0x10) = (s128) M2C_FIELD(arg1, s128 *, 0x10);
        M2C_FIELD(temp_4_2, s128 *, 0x20) = (s128) M2C_FIELD(arg1, s128 *, 0x20);
        M2C_FIELD(temp_4_2, s128 *, 0x30) = (s128) M2C_FIELD(arg1, s128 *, 0x30);
        M2C_FIELD(((M2C_FIELD(arg0, u32 *, 0x2410) * 0x50) + arg0), s8 *, 0x114) = 0;
        M2C_FIELD(((M2C_FIELD(arg0, u32 *, 0x2410) * 0x50) + arg0), s8 *, 0x115) = (s8) arg2;
        M2C_FIELD(arg0, u32 *, 0x2410) = (u32) (M2C_FIELD(arg0, u32 *, 0x2410) + 1);
    }
}
