#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00110A88(void *arg0) {
    void *temp_2;

    temp_2 = (void *) (((u32) M2C_FIELD(arg0, void **, 0x18)) + ((u32) arg0));
    M2C_FIELD(arg0, void **, 0x18) = temp_2;
    M2C_FIELD(arg0, void **, 0x1C) = (void *) ((void *) (((u32) M2C_FIELD(arg0, void **, 0x1C)) + ((u32) arg0)));
    return (s32) temp_2;
}
