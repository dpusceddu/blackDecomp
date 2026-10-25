#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Vtable_003DD980: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003DD980 {
    u8 unk_0[4];
    void * unk_4;
} Recovered_Vtable_003DD980;

#include "game/vtable_003dde88.h"
#include "ps2/recovered_types.h"
extern void * func_0018E458(Recovered_Vtable_003DDE88 *, void *);
extern s128 func_00190C18(void *);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_00190BC0(Recovered_Vtable_003DD980 *arg0, s32 arg1) {
    func_0018E458((Recovered_Vtable_003DDE88 *) arg0, arg1);
    M2C_FIELD(arg0->unk_4, s8 *, 0xD24) = 0;
    func_00190C18(arg0);
    return func_00181F48(arg0->unk_4 + 0xC80, 0, 0x27, 0.0f, 2.0f);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_190a68_190bc0", func_00190C18);
