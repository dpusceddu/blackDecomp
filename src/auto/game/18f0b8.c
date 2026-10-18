#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_Vtable_003DDD18.h"
#include "recovered/Recovered_Vtable_003DDE88.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_0018E458(Recovered_Vtable_003DDE88 *, void *);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_0018F0B8(Recovered_Vtable_003DDD18 *arg0, s32 arg1) {
    func_0018E458((Recovered_Vtable_003DDE88 *) arg0, arg1);
    return func_00181F48(arg0->field_4 + 0xC80, 0, 0x24, 0.0f, 2.0f);
}
