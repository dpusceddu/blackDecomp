#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Vtable_003DC9C0: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003DC9C0 {
    u8 unk_0[8];
    f32 unk_8;
    f32 unk_C;
    u8 unk_10[108];
    void * unk_7C;
    u8 unk_80[16];
    u32 unk_90;
    u8 unk_94[36];
    u8 unk_B8;
    u8 unk_B9;
    u8 unk_BA[10];
    u32 unk_C4;
} Recovered_Vtable_003DC9C0;

#include "ps2/recovered_types.h"
extern s32 func_001F2838(s32, s32, s32);
extern s32 D_0040F51C;

s32 func_0013DD18(Recovered_Vtable_003DC9C0 *arg0) {
    void *temp_2;

    if (arg0->unk_B9 != 0) {
        func_001F2838(D_0040F51C, 0, 1);
    }
    temp_2 = arg0->unk_7C;
    M2C_FIELD(temp_2, s8 *, 0x8B2) = 0;
    arg0->unk_B8 = 0;
    arg0->unk_90 = 0;
    arg0->unk_C4 = 0;
    return (s32) temp_2;
}
