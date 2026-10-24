#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Vtable_003DC350: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003DC350 {
    f32 unk_0;
    u8 unk_4[45];
    u8 unk_31;
    u8 unk_32;
    u8 unk_33;
    u8 unk_34;
    u8 unk_35;
    u8 unk_36[70];
    void * unk_7C;
    u8 unk_80[1116];
    u32 unk_4DC;
    u8 unk_4E0[4];
    u8 unk_4E4;
    u8 unk_4E5;
} Recovered_Vtable_003DC350;

#include "ps2/recovered_types.h"
extern s32 func_0013EE20();
extern s32 func_001414A0(void *);
extern s32 func_00140CF8(void *);
extern s32 * func_00140EA8(void *);
extern s32 func_00136818(s64 *, f32);

s32 func_00140CA0(Recovered_Vtable_003DC350 *arg0) {
    func_0013EE20();
    arg0->unk_4DC = 0;
    func_001414A0(arg0);
    func_00140CF8(arg0);
    func_00140EA8(arg0);
    return func_00136818((s32 *) arg0->unk_7C, 0.8f);
}
