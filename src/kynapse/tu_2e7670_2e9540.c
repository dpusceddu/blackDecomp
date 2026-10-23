#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_ParameterTables.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

void func_002E9540(Recovered_ParameterTables *arg0, s32 arg1, f32 fparg0) {
    if ((arg1 >= 0) && ((u32) arg1 < (u32) arg0->field_8)) {
        M2C_FIELD(((arg1 * 4) + arg0->field_28), f32 *, 0) = fparg0;
    }
}

void func_002E9570(Recovered_ParameterTables *arg0, s32 arg1, f32 fparg0) {
    if ((arg1 >= 0) && ((u32) arg1 < (u32) arg0->field_8)) {
        M2C_FIELD(((arg1 * 4) + arg0->field_20), f32 *, 0) = fparg0;
    }
}

void func_002E95A0(Recovered_ParameterTables *arg0, s32 arg1, s32 arg2) {
    if ((arg1 >= 0) && ((u32) arg1 < (u32) arg0->field_8)) {
        M2C_FIELD(((arg1 * 4) + arg0->field_24), s32 *, 0) = arg2;
    }
}

void func_002E95D0(Recovered_ParameterTables *arg0, s32 arg1, f32 fparg0) {
    if ((arg1 >= 0) && ((u32) arg1 < (u32) arg0->field_4)) {
        M2C_FIELD(((arg1 * 4) + arg0->field_2C), f32 *, 0) = fparg0;
    }
}

void func_002E9600(Recovered_ParameterTables *arg0, s32 arg1, f32 fparg0) {
    if ((arg1 >= 0) && ((u32) arg1 < (u32) arg0->field_C)) {
        M2C_FIELD(((arg1 * 4) + arg0->field_30), f32 *, 0) = fparg0;
    }
}
