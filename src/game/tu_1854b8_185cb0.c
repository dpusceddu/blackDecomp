#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_00173640(f32 *, f32);
extern s32 func_00173690(f32 *);

s32 * func_00185CB0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 var_2;

    if (arg1 < 2) {
        var_2 = arg2 < 2;
        if (var_2 == 0) {
            var_2 = func_00173640((f32 *) ((s32 *) (((s8 *) arg0) + 0x114)), 1.0f);
        }
    } else {
        var_2 = arg2 < 2;
        if (var_2 != 0) {
            var_2 = func_00173690((f32 *) ((s32 *) (((s8 *) arg0) + 0x114)));
        }
    }
    return (s32 *) var_2;
}
