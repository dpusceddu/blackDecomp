#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_Vtable_003DD980.h"
#include "recovered/Recovered_Vtable_003DDE88.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_0018E458(Recovered_Vtable_003DDE88 *, void *);
extern s128 func_00190C18(void *);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_00190BC0(Recovered_Vtable_003DD980 *arg0, s32 arg1) {
    func_0018E458((Recovered_Vtable_003DDE88 *) arg0, arg1);
    M2C_FIELD(arg0->field_4, s8 *, 0xD24) = 0;
    func_00190C18(arg0);
    return func_00181F48(arg0->field_4 + 0xC80, 0, 0x27, 0.0f, 2.0f);
}
