#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/partial/Recovered_Vtable_003DC9C0.h"
#include "ps2/recovered_types.h"
extern s32 func_001F2838(s32, s32, s32);
extern s32 D_0040F51C;

s32 func_0013DD18(Recovered_Vtable_003DC9C0 *arg0) {
    void *temp_2;

    if (arg0->field_B9 != 0) {
        func_001F2838(D_0040F51C, 0, 1);
    }
    temp_2 = arg0->field_7C;
    M2C_FIELD(temp_2, s8 *, 0x8B2) = 0;
    arg0->field_B8 = 0;
    arg0->field_90 = 0;
    arg0->field_C4 = 0;
    return (s32) temp_2;
}
