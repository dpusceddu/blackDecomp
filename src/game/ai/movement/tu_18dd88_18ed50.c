#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Vtable_003DDDD0: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003DDDD0 {
    u8 unk_0[4];
    s32 unk_4;
    u8 unk_8[13];
    u8 unk_15;
} Recovered_Vtable_003DDDD0;

#include "game/vtable_003dde88.h"
#include "ps2/recovered_types.h"
extern void * func_0018E458(Recovered_Vtable_003DDE88 *, void *);
extern s32 func_00188B40(void *, s32, f32, f32);
extern s8 * func_0018D7A0(void *, s32);
extern s8 * func_0018DDD8(void *);
extern s8 * func_001726A0(f32 *, s32);
extern f32 * func_0013D400(void *);
extern s8 * func_0018EE00(void *);

s8 * func_0018ED50(Recovered_Vtable_003DDDD0 *arg0, void *arg1) {
    s8 *var_2;
    void *temp_16;

    func_0018E458((Recovered_Vtable_003DDE88 *) arg0, arg1);
    temp_16 = M2C_FIELD(arg1, void **, 0x30);
    if (M2C_FIELD(temp_16, u8 *, 0x43) != 0) {
        func_00188B40(arg0->unk_4 + 0x290, 1, 1.0f, 5.0f);
    }
    if (M2C_FIELD(temp_16, u8 *, 0x42) != 0) {
        func_0018D7A0(arg0->unk_4 + 0xD10, 1);
    }
    arg0->unk_15 = 0;
    if ((func_0018DDD8(arg0->unk_4 + 0xC94) == NULL) || (var_2 = func_001726A0(func_0013D400(arg0->unk_4), (s32) arg0->unk_4), (var_2 != NULL))) {
        var_2 = func_0018EE00(arg0);
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EE00);
