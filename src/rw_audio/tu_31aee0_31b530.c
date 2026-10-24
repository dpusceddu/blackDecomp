#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_0040E1FC;
extern void * D_0040E200;

void func_0031B530(s32 arg0, void *arg1) {
    D_0040E1FC = (M2C_UNK (*)(f32 *, void *, void *, void *, void *, void *)) arg0;
    D_0040E200 = arg1;
}
