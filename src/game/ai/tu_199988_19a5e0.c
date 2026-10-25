#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Vtable_003DE590: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003DE590 {
    void * unk_0;
    u8 unk_4[4];
    s32 unk_8;
} Recovered_Vtable_003DE590;

#include "ps2/recovered_types.h"
extern s32 func_00193980();
extern s32 * func_00181A90(void *, s32 *);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_0019A5E0(Recovered_Vtable_003DE590 *arg0) {
    func_00193980();
    M2C_FIELD(M2C_FIELD(arg0->unk_0, void **, 0x694), s8 *, 0x3B) = 1;
    arg0->unk_8 = func_00181A90(arg0->unk_0 + 0xEC0, (s32 *)0x37);
    return func_00181F48(arg0->unk_0 + 0xC80, 0, 0x16, 0.0f, 1.0f);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019A670);
