#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/partial/Recovered_Vtable_003DE590.h"
#include "ps2/recovered_types.h"
extern s32 func_00193980();
extern s32 * func_00181A90(void *, s32 *);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_0019A5E0(Recovered_Vtable_003DE590 *arg0) {
    func_00193980();
    M2C_FIELD(M2C_FIELD(arg0->field_0, void **, 0x694), s8 *, 0x3B) = 1;
    arg0->field_8 = func_00181A90(arg0->field_0 + 0xEC0, (s32 *)0x37);
    return func_00181F48(arg0->field_0 + 0xC80, 0, 0x16, 0.0f, 1.0f);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019A648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019A670);
