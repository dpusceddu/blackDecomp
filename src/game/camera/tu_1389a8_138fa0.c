#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 * func_00139060(void *, s64 *);
extern s32 func_00139980(void *);
extern s32 func_00139838(void *, s64 *);
extern s32 func_001354E0(s64 *, void *);
extern s32 func_0025C2C8(void *, s64 *);
extern void * D_0040F4CC;
extern s32 func_00135EA8(s64 *, f32, f32);
extern s32 func_00135B80(s64 *, s32);
extern s32 func_00137F30(s64 *);
extern s32 func_0016E6B0(s32, s64 *);
extern s32 D_0040F4D4;

s32 func_00138FA0(void *arg0, s32 *arg1) {
    void *temp_16;

    temp_16 = (void *) (((s8 *) arg0) + 0x79C0);
    if (M2C_FIELD(temp_16, s32 *, 4) == M2C_FIELD(temp_16, s32 *, 8)) {
        func_00139060(arg0, func_00139980(temp_16));
    }
    func_00139838(temp_16, arg1);
    func_001354E0(arg1, NULL);
    func_0025C2C8(D_0040F4CC, arg1);
    func_00135EA8(arg1, 0.1f, 0.0f);
    func_00135B80(arg1, 2);
    func_00137F30(arg1);
    return func_0016E6B0(D_0040F4D4, arg1);
}
