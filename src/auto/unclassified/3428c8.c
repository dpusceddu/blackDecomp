#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00342938(void *, void *);

s32 func_003428C8(void *arg0, s32 arg1) {
    void *temp_16;
    void *temp_3;

    temp_16 = M2C_FIELD(arg0, void **, 0x14);
    temp_3 = M2C_FIELD(temp_16, void **, 0);
    M2C_FIELD(arg0, void **, 0x14) = temp_3;
    M2C_FIELD(temp_3, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x1030) = (s32) (M2C_FIELD(arg0, s32 *, 0x1030) - 1);
    M2C_FIELD(temp_16, s32 *, 4) = 0;
    M2C_FIELD(temp_16, void **, 0) = (void *) M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, 4) = temp_16;
    M2C_FIELD(arg0, void **, 0x10) = temp_16;
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) + 1);
    func_00342938(arg0, temp_16);
    return M2C_FIELD(temp_16, s32 *, 0x1C);
}
