#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00282710(void *);

s32 func_00282628(void *arg0) {
    s32 *var_2;
    s32 var_3;

    func_00282710(arg0);
    var_3 = 3;
    var_2 = (s32 *) (((s8 *) arg0) + 0x1210);
    do {
        *var_2 = 0;
        var_3 -= 1;
        var_2 = (s32 *) (((s8 *) var_2) + -4);
    } while (var_3 >= 0);
    M2C_FIELD(arg0, s16 *, 0x1218) = 0;
    return 1;
}
