#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/layouts/Recovered_Vtable_003DC350.h"
#include "ps2/recovered_types.h"
extern s32 func_0013EE20();
extern s32 func_001414A0(void *);
extern s32 func_00140CF8(void *);
extern s32 * func_00140EA8(void *);
extern s32 func_00136818(s64 *, f32);

s32 func_00140CA0(Recovered_Vtable_003DC350 *arg0) {
    func_0013EE20();
    arg0->field_4DC = 0;
    func_001414A0(arg0);
    func_00140CF8(arg0);
    func_00140EA8(arg0);
    return func_00136818((s32 *) arg0->field_7C, 0.8f);
}
