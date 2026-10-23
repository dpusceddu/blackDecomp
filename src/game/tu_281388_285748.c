#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern M2C_UNK D_003E26B0;
extern void * func_00281B50(void *);
extern s32 func_00284BF0(void *, void *, void *);
extern s32 func_00280FE0(void *, void *);

void * func_00285748(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    u8 sp[16] __attribute__((aligned(16)));
    void *var_16;
    void *var_5;

    *(M2C_UNK * *)(sp + 0) = &D_003E26B0;
    *(u8 *)(sp + 4) = 0;
    var_16 = func_00281B50(arg1);
    if (var_16 != NULL) {
        var_5 = var_16;
        if (func_00284BF0(var_16, arg2, M2C_FIELD(arg1, void **, 0x186C)) == 0) {
            var_16 = NULL;
            M2C_FIELD(arg1, s32 *, 0x182C) = (s32) (M2C_FIELD(arg1, s32 *, 0x182C) + 1);
            goto block_3;
        }
    } else {
block_3:
        var_5 = var_16;
    }
    func_00280FE0(sp, var_5);
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E26B0;
    M2C_FIELD(arg0, u8 *, 4) = *(u8 *)(sp + 4);
    M2C_FIELD(arg0, s32 *, 8) = *(s32 *)(sp + 8);
    M2C_FIELD(arg0, s32 *, 0xC) = *(s32 *)(sp + 12);
    return arg0;
}
