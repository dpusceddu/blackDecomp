#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Vtable_003DB0E8: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003DB0E8 {
    u8 unk_0[160];
    u8 unk_A0;
    u8 unk_A1;
    u8 unk_A2;
} Recovered_Vtable_003DB0E8;

#include "ps2/recovered_types.h"
extern s32 func_00118808(s32);
extern s32 func_00116F60();
extern s32 func_00118240();

s32 func_001175E8(Recovered_Vtable_003DB0E8 *arg0) {
    s32 temp_v0;

    func_00118808((s32) &arg0->unk_0[4]);
    func_00116F60(&arg0->unk_0[0x20]);
    temp_v0 = func_00118240(&arg0->unk_0[0x60]);
    arg0->unk_A2 = 0;
    arg0->unk_A0 = 0;
    arg0->unk_A1 = 0;
    return temp_v0;
}
