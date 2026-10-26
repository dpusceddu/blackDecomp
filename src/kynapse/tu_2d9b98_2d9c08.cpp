#include "kynapse/parameter_classes.hpp"
#include "kynapse/action_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002DFEB0(void*, const char*, ObjectBase* (*)());
extern void* D_00450B68;
extern char D_003E3D38;

extern "C" void func_002D9C08(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002DFEB0(&gClassInfo2B5478, "CActionActivate", &CreateParameter2849BC);
            return;
        }
        D_00450B68 = &D_003E3D38;
    }
}

ActivateAction& ActivateAction::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        SetRequested(((const ActivateAction&)other).requested);
    return *this;
}

extern "C" void func_002D9CE0() {
    func_002D9C08(1, 0xFFFF);
}

extern "C" void func_002D9D00() {
    func_002D9C08(0, 0xFFFF);
}
