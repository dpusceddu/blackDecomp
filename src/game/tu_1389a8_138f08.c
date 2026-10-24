#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_00139060(void *, s64 *);
extern s32 func_00139980(void *);
extern s32 func_00139838(void *, s64 *);
extern s32 func_00135C08(s64 *);
extern s32 func_00135B80(s64 *, s32);
extern s32 func_0016E6B0(s32, s64 *);
extern void * D_0040F4D4;

s32 func_00138F08(void *arg0, s32 *arg1) {
    s32 var_2;
    void *temp_16;

    temp_16 = (void *) (((s8 *) arg0) + 0x79B0);
    var_2 = M2C_FIELD(arg1, s32 *, 0x250);
    if (var_2 != temp_16) {
        if (M2C_FIELD(temp_16, s32 *, 4) == M2C_FIELD(temp_16, s32 *, 8)) {
            func_00139060(arg0, func_00139980(temp_16));
        }
        func_00139838(temp_16, arg1);
        func_00135C08(arg1);
        func_00135B80(arg1, 1);
        var_2 = func_0016E6B0((s32) D_0040F4D4, arg1);
    }
    return var_2;
}
