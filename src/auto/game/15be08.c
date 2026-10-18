#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00156E70(void *);

void func_0015BE08(void *arg0) {
    s32 temp_2;
    void *temp_4;

    if (M2C_FIELD(arg0, s32 *, 0x38) == 0) {
        temp_4 = M2C_FIELD(arg0, void **, 0x24);
        temp_2 = M2C_FIELD((((1 - M2C_FIELD(arg0, s8 *, 0x43)) * 4) + M2C_FIELD(arg0, s32 *, 0x20)), s32 *, 0);
        if ((temp_4 != NULL) && (temp_2 != temp_4) && (temp_2 != 0)) {
            M2C_FIELD(arg0, s8 *, 0x45) = 1;
            M2C_FIELD(arg0, s32 *, 0x38) = 2;
            M2C_FIELD(arg0, s32 *, 0x3C) = 0;
            func_00156E70(temp_4);
        }
    }
}
