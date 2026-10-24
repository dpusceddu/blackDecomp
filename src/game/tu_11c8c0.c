#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00382348(void *, s32);

s32 func_0011C8C0(void *arg0) {
    s32 var_5;
    void **var_3;
    void *var_4;

    var_5 = 7;
    M2C_FIELD(arg0, void **, 0x18) = NULL;
    var_4 = (void *) (((s8 *) arg0) + 0x20);
    var_3 = (void **) (((s8 *) arg0) + 0xB0);
    do {
        var_5 -= 1;
        *var_3 = M2C_FIELD(arg0, void **, 0x18);
        M2C_FIELD(arg0, void **, 0x18) = var_4;
        var_3 = (void **) (((s8 *) var_3) + 0x4F0);
        var_4 = (void *) (((s8 *) var_4) + 0x4F0);
    } while (var_5 >= 0);
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    func_00382348((void *) (((s8 *) arg0) + 0x10), 0x02B9D6F8);
    M2C_FIELD(arg0, s8 *, 0) = 0;
    return 1;
}
