#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00280100(s32, void *);
extern void * D_0040F510;
extern f32 func_001DFE38(void *);

s32 func_001E0480(void *arg0) {
    s32 *var_16;
    s32 var_20;
    void **var_17;
    void **var_18;
    void *temp_3;
    void *temp_5;
    void *temp_5_2;

    var_17 = (void **) (((s8 *) arg0) + 0x50);
    var_16 = (s32 *) (((s8 *) arg0) + 0x30);
    var_18 = var_17;
    var_20 = 7;
    do {
        if (*var_16 != 0) {
            temp_3 = *var_17;
            M2C_FIELD(temp_3, M2C_UNK (**)(void *), 0x1C)((void *) (((s8 *) var_18) + M2C_FIELD(temp_3, s16 *, 0x18)));
            *var_16 = 0;
        }
        var_18 = (void **) (((s8 *) var_18) + 0x10);
        var_17 = (void **) (((s8 *) var_17) + 0x10);
        var_20 -= 1;
        var_16 = (s32 *) (((s8 *) var_16) + 4);
    } while (var_20 >= 0);
    temp_5 = M2C_FIELD(arg0, void **, 0x241C);
    if (temp_5 != NULL) {
        func_00280100((s32) D_0040F510, temp_5);
        M2C_FIELD(arg0, void **, 0x241C) = NULL;
    }
    temp_5_2 = M2C_FIELD(arg0, void **, 0x2420);
    if (temp_5_2 != NULL) {
        func_00280100((s32) D_0040F510, temp_5_2);
        M2C_FIELD(arg0, void **, 0x2420) = NULL;
    }
    M2C_FIELD(arg0, s32 *, 0x2434) = 0;
    M2C_FIELD(arg0, s32 *, 0x2438) = 0;
    func_001DFE38(arg0);
    return 1;
}
