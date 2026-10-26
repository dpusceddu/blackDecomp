#include "kynapse/parameter_classes.hpp"
#include "kynapse/action_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void func_002DFEB0(void*, const char*, ObjectBase* (*)());
extern void* D_0044F588;
extern char D_003E3D38;

extern "C" void func_002D79E0(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002DFEB0(&gClassInfo2B4870, "CActionAcceleration", &CreateParameter284828);
            return;
        }
        D_0044F588 = &D_003E3D38;
    }
}

AccelerationAction& AccelerationAction::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        SetAcceleration(((const AccelerationAction&)other).acceleration);
    return *this;
}

extern "C" void func_002D7AB8() {
    func_002D79E0(1, 0xFFFF);
}

extern "C" void func_002D7AD8() {
    func_002D79E0(0, 0xFFFF);
}
