#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/partial/Recovered_Vtable_003DDC60.h"
#include "game/partial/Recovered_Vtable_003DDE88.h"
#include "ps2/recovered_types.h"
extern s32 func_001830A0(void *);
extern void * func_0018E458(Recovered_Vtable_003DDE88 *, void *);
extern s32 func_001830C0(s32 *, s32);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_0018F2E0(Recovered_Vtable_003DDC60 *arg0, void *arg1) {
    func_001830A0(arg0->field_4 + 0xD10);
    func_0018E458((Recovered_Vtable_003DDE88 *) arg0, arg1);
    func_001830C0(arg0->field_4 + 0xD10, (s32) (arg1 + 0x28));
    return func_00181F48(arg0->field_4 + 0xC80, 0, 0, 0.0f, 2.0f);
}
