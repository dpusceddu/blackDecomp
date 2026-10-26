#include "kynapse/parameter_classes.hpp"
#include "kynapse/action_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void func_002DFEB0(void*, const char*, ObjectBase* (*)());
extern void* D_0044F8D0;
extern char D_003E3D38;

extern "C" void func_002D7E78(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002DFEB0(&gClassInfo2B3B50, "CActionRotate", &CreateParameter2846A0);
            return;
        }
        D_0044F8D0 = &D_003E3D38;
    }
}

RotateAction& RotateAction::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        SetRotation(((const RotateAction&)other).rotation);
    return *this;
}

extern "C" void func_002D7F50() {
    func_002D7E78(1, 0xFFFF);
}

extern "C" void func_002D7F70() {
    func_002D7E78(0, 0xFFFF);
}
