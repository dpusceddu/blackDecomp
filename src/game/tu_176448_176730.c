#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00176460(void *);

s32 func_00176730(void *arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = (s8) arg1 * 0x1C;
    M2C_FIELD((arg0 + temp_5), s8 *, 0xE8) = 0;
    return func_00176460(arg0 + (temp_5 + 0xD0));
}
