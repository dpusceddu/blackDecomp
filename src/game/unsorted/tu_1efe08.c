#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00285AA8(void *);
extern s32 func_00285C60(s32, s32, s32, f32, f32, f32);

s32 func_001EFE08(void *arg0, s32 arg1, f32 fparg0) {
    func_00285AA8(arg0);
    return func_00285C60(M2C_FIELD(arg0, s32 *, 0xCBE0), 1, 0, 1.0f, 1.0f, fparg0);
}
