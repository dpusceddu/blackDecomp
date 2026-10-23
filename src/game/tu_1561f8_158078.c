#include "auto/prelude.h"
#include "mod/weapons/state.h"

extern s32 func_0015A938(void *arg0);

s32 func_00158078(void *arg0) {
    return BkModWeaponReloadingPS2(arg0);
}

s32 func_00158088(void *arg0) {
    return ((BkModWeaponControllerPS2*)arg0)->phase == 1;
}

s32 func_00158098(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = ((BkModWeaponControllerPS2*)arg0)->phase;
    var_4 = 0;
    if ((temp_3 == 1) || (temp_3 == 8)) {
        var_4 = 1;
    }
    return var_4;
}

void func_001580C0(void *arg0) {
    func_0015A938(((BkModWeaponControllerPS2*)arg0)->primary);
}

s16 func_001580E0(void *arg0) {
    return BkModWeaponClipPS2(arg0);
}
