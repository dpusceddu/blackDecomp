#include "kynapse/parameter_classes.hpp"
#include "kynapse/action_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002DFEB0(void*, const char*, ObjectBase* (*)());
extern void* D_00450EB0;
extern char D_003E3D38;
extern s32 D_00450EB8;
extern s32 D_00450FD8;
extern s32 D_004510F0;

extern "C" void func_002DA0B0(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002DFEB0(&gClassInfo2B5130, "CActionVerticalSpeed", &CreateParameter28494C);
            return;
        }
        D_00450EB0 = &D_003E3D38;
    }
}

VerticalSpeedAction& VerticalSpeedAction::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        SetSpeed(((const VerticalSpeedAction&)other).speed);
    return *this;
}

extern "C" void func_002DA188() {
    func_002DA0B0(1, 0xFFFF);
}

extern "C" void func_002DA1A8() {
    func_002DA0B0(0, 0xFFFF);
}

extern "C" s32 func_002DA1C8(void) {
    if ((D_00450EB8 == -1) || (D_00450FD8 == -1) || (D_004510F0 == -1)) {
        return 0;
    }
    return 1;
}
