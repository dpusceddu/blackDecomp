#include "auto/prelude.h"
#include "mod/weapons/shot.h"

void func_001632F8(BkModDelayedShotPS2 *arg0, s32 arg1, s32 arg2, s128 arg3, s128 arg4, s8 arg5, f32 fparg0, f32 fparg1) {
    arg0->direction = arg4;
    arg0->weapon = (BkModWeaponInstancePS2*)arg1;
    arg0->flags = arg5;
    arg0->distance = fparg1;
    arg0->active = 1;
    arg0->point = arg3;
    arg0->remaining = (f32) (fparg0 / 144.0f);
}
