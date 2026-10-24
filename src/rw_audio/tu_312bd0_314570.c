#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern M2C_UNK * D_0040E778;
extern void * func_00318188(void *, s32 *);

void func_00314570(s32 *arg0) {
    M2C_UNK *var_16;
    M2C_UNK *var_4;

    var_16 = D_0040E778;
    if (var_16 != &D_0040E778) {
        var_4 = (M2C_UNK *) (((s8 *) var_16) + -0x10);
        do {
            func_00318188(var_4, arg0);
            var_16 = *var_16;
            var_4 = (M2C_UNK *) (((s8 *) var_16) + -0x10);
        } while (var_16 != &D_0040E778);
    }
}
