#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_Vtable_003DE590.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00193980();
extern s32 * func_00181A90(void *, s32 *);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_0019A5E0(Recovered_Vtable_003DE590 *arg0) {
    func_00193980();
    M2C_FIELD(M2C_FIELD(arg0->field_0, void **, 0x694), s8 *, 0x3B) = 1;
    arg0->field_8 = func_00181A90(arg0->field_0 + 0xEC0, (s32 *)0x37);
    return func_00181F48(arg0->field_0 + 0xC80, 0, 0x16, 0.0f, 1.0f);
}
