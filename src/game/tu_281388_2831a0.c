#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_0040E14C;
extern s32 func_00312EE0(void *, s32);
extern s32 func_003130A0();
extern s32 func_003250D8();
extern s32 func_0031B530(s32, void *);
extern s32 func_002832A0(void *, void *, void *, void *, void *);

s32 func_002831A0(void *arg0, void *arg1) {
    D_0040E14C = func_00312EE0(arg1, 1);
    func_003130A0();
    func_003250D8();
    func_0031B530((s32) func_002832A0, arg0);
    M2C_FIELD(arg0, s8 *, 0xCBB4) = 1;
    return 0x8000;
}
