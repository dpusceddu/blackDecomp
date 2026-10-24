#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00193980();
extern s8 * func_00181F48(void *, s32, s32, f32, f32);
extern s32 func_00193A60(s32 *, s32, f32);
extern f32 func_0018DD60(s32);

s32 func_00197BB0(s32 *arg0) {
    func_00193980();
    M2C_FIELD(M2C_FIELD(*arg0, void **, 0x694), s8 *, 0x35) = 1;
    func_00181F48(*arg0 + 0xC80, 0, 4, 0.0f, 1.0f);
    return func_00193A60(arg0, 0, func_0018DD60(*arg0 + 0xC94));
}
