#include "kynapse/parameter_classes.hpp"
#include "kynapse/action_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002DFEB0(void*, const char*, ObjectBase* (*)());
extern void* D_0044FC18;
extern char D_003E3D38;

extern "C" void func_002D8330(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002DFEB0(&gClassInfo2B4528, "CActionSteering", &CreateParameter2847CC);
            return;
        }
        D_0044FC18 = &D_003E3D38;
    }
}

SteeringAction& SteeringAction::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        SetSteering(((const SteeringAction&)other).steering);
    return *this;
}

extern "C" void func_002D8408() {
    func_002D8330(1, 0xFFFF);
}

extern "C" void func_002D8428() {
    func_002D8330(0, 0xFFFF);
}
