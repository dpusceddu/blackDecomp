#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_00139060();
extern void * func_00139980();
extern s32 func_00139838();
extern s32 func_001327F0();
extern s32 func_0013EC38();
extern s32 func_001354E0();
extern s32 func_0025C210();
extern s32 D_0040F4CC;
extern s32 func_0012A158();
extern void * D_0040F4D0;

void * func_00138DF8(s32 arg0, s32 arg1, s128 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *temp_17;
    void *temp_2;

    temp_17 = arg0 + 0x79A0;
    if (M2C_FIELD(temp_17, s32 *, 4) == M2C_FIELD(temp_17, s32 *, 8)) {
        func_00139060(arg0, func_00139980(temp_17));
    }
    temp_2 = func_00139980(arg0 + 0x7990);
    func_00139838(temp_17, temp_2);
    func_001327F0(temp_2, arg1, arg2, arg3, arg4, arg5, 0, -1);
    if (arg0 != 0) {
        func_0013EC38(arg0, temp_2);
        func_001354E0(temp_2, arg0);
    }
    func_0025C210(D_0040F4CC, temp_2);
    func_0012A158(D_0040F4D0, temp_2);
    return temp_2;
}
