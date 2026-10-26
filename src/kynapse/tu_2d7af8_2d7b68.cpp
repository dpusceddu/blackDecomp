#include "kynapse/parameter_classes.hpp"
#include "kynapse/action_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002DFEB0(void*, const char*, ObjectBase* (*)());
extern void* D_0044F6A0;
extern char D_003E3D38;

extern "C" void func_002D7B68(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002DFEB0(&gClassInfo2B4758, "CActionCrouch", &CreateParameter284808);
            return;
        }
        D_0044F6A0 = &D_003E3D38;
    }
}

CrouchAction& CrouchAction::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        SetRequested(((const CrouchAction&)other).requested);
    return *this;
}

extern "C" void func_002D7C40() {
    func_002D7B68(1, 0xFFFF);
}

extern "C" void func_002D7C60() {
    func_002D7B68(0, 0xFFFF);
}
