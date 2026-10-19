#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001777D0(void *);

s32 func_00177148(void *arg0) {
    s32 var_3;
    void *var_2;

    M2C_FIELD(arg0, s32 *, 0x978) = 0;
    func_001777D0(arg0);
    M2C_FIELD(arg0, s32 *, 0x96C) = 0;
    var_2 = (void *) (((s8 *) arg0) + 0x980);
    M2C_FIELD(arg0, s32 *, 0x970) = 0;
    var_3 = 4;
    M2C_FIELD(arg0, s32 *, 0x974) = 0;
    do {
        M2C_FIELD(var_2, s32 *, -4) = 0;
        var_3 -= 1;
        M2C_FIELD(var_2, s32 *, 0) = 0;
        var_2 = (void *) (((s8 *) var_2) + 8);
    } while (var_3 >= 0);
    return 1;
}
