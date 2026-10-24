#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00286220(void *, void *, void *, f32, f32, f32, f32, f32, f32);

s32 func_002860F0(void *arg0, void *arg1, void *arg2, f32 fparg0) {
    return func_00286220(arg0, arg1, arg2, fparg0, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
}
