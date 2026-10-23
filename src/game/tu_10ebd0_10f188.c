#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_FrontendProfilePool.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00122AF0();

s32 func_0010F188(Recovered_FrontendProfilePool *arg0) {
    Recovered_FrontendProfilePool *temp_2;
    Recovered_FrontendProfilePool *var_16;
    s32 var_17;

    var_16 = (Recovered_FrontendProfilePool *) (((s8 *) arg0) + 8);
    var_17 = 0;
    do {
        var_17 -= 1;
        func_00122AF0(var_16);
        var_16 = (Recovered_FrontendProfilePool *) (((s8 *) var_16) + 0x6A8);
    } while (var_17 >= 0);
    temp_2 = (Recovered_FrontendProfilePool *) (((s8 *) arg0) + 8);
    arg0->field_0 = (u32) temp_2;
    return (s32) temp_2;
}
