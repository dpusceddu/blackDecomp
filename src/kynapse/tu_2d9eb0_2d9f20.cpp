#include "kynapse/parameter_classes.hpp"
#include "kynapse/action_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002DFEB0(void*, const char*, ObjectBase* (*)());
extern void* D_00450D98;
extern char D_003E3D38;

extern "C" void func_002D9F20(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002DFEB0(&gClassInfo2B5248, "CActionTorsoRotate", &CreateParameter284974);
            return;
        }
        D_00450D98 = &D_003E3D38;
    }
}

TorsoRotateAction& TorsoRotateAction::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo()) {
        const TorsoRotateAction& source = (const TorsoRotateAction&)other;
        SetPrimary(source.primary);
        SetSecondary(source.secondary);
    }
    return *this;
}

extern "C" void func_002DA000() {
    func_002D9F20(1, 0xFFFF);
}

extern "C" void func_002DA020() {
    func_002D9F20(0, 0xFFFF);
}
