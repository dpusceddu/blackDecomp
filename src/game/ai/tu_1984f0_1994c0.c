#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/partial/Recovered_Vtable_003DF170.h"
#include "ps2/recovered_types.h"
extern s32 func_00198568();

s32 func_001994C0(Recovered_Vtable_003DF170 *arg0) {
    void *temp_2;

    func_00198568();
    temp_2 = arg0->field_0;
    M2C_FIELD(M2C_FIELD(temp_2, void **, 0x694), s8 *, 0x30) = 0;
    return (s32) temp_2;
}
