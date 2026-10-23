#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_0012EEC8(void *arg0) {
    void *temp_2;

    temp_2 = (void *) (((u32) M2C_FIELD(arg0, void **, 4)) + ((u32) arg0));
    M2C_FIELD(arg0, void **, 4) = temp_2;
    M2C_FIELD(arg0, void **, 8) = (void *) ((void *) (((u32) M2C_FIELD(arg0, void **, 8)) + ((u32) arg0)));
    return (s32) temp_2;
}
