#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/layouts/Recovered_Vtable_003DF5D0.h"
#include "ps2/recovered_types.h"
extern s32 func_00193988();
extern s32 func_00180CC8(void *, s32);
extern s32 * func_001825B0(void *);

s32 * func_00194A38(Recovered_Vtable_003DF5D0 *arg0) {
    func_00193988();
    func_00180CC8((void *) (((s8 *) arg0->field_0) + 0xB30), 0);
    M2C_FIELD(arg0->field_0, s8 *, 0x845) = 0;
    return func_001825B0((void *) (((s8 *) arg0->field_0) + 0x810));
}
