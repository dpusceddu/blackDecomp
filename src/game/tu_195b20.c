#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "game/layouts/Recovered_Vtable_003DFAB8.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00193980();
extern s32 func_0017DB18(f32 *);
extern s32 func_0018DAF8(void *);
extern s32 func_001825B0(void *);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_00195B20(Recovered_Vtable_003DFAB8 *arg0) {
    func_00193980();
    func_0017DB18(arg0->field_0 + 0x650);
    if (func_0018DAF8(arg0->field_0 + 0xC94) != 0) {
        M2C_FIELD(M2C_FIELD(arg0->field_0, void **, 0x694), s8 *, 0x30) = 1;
        func_001825B0(arg0->field_0 + 0x810);
    }
    return func_00181F48(arg0->field_0 + 0xC80, 0, 0x18, 0.0f, 1.0f);
}
