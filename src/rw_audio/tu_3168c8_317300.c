#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * D_0040E780;

s32 func_00317300(void *arg0) {
    void *temp_5;

    temp_5 = arg0 + 0x28;
    M2C_FIELD(temp_5, void ***, 4) = NULL;
    M2C_FIELD(arg0, void **, 0x28) = NULL;
    M2C_FIELD(arg0, void **, 0x28) = (void *) D_0040E780;
    M2C_FIELD(temp_5, void ***, 4) = &D_0040E780;
    M2C_FIELD(D_0040E780, void **, 4) = temp_5;
    D_0040E780 = temp_5;
    M2C_FIELD(temp_5, u8 *, 0x62) = (u8) (M2C_FIELD(temp_5, u8 *, 0x62) & 0xFE);
    return 1;
}
