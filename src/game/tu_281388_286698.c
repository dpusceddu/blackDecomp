#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_002867C0(void *, s32, s32);

void * func_00286698(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_2;

    temp_2 = func_002867C0(arg0, 0x8050, 4);
    M2C_FIELD(temp_2, s32 *, 0xC) = arg4;
    M2C_FIELD(temp_2, s32 *, 0) = arg1;
    M2C_FIELD(temp_2, s32 *, 4) = arg2;
    M2C_FIELD(temp_2, s32 *, 8) = arg3;
    M2C_FIELD(arg0, s32 *, 0x2418) = arg1;
    M2C_FIELD(arg0, s32 *, 0x2874) = arg2;
    M2C_FIELD(arg0, s32 *, 0x2878) = arg3;
    M2C_FIELD(arg0, s8 *, 0x288E) = (s8) arg4;
    M2C_FIELD(arg0, s8 *, 0x288D) = 0;
    M2C_FIELD(arg0, s8 *, 0x288C) = 0;
    return temp_2;
}
