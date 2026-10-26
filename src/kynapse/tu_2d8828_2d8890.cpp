#include "kynapse/parameter_classes.hpp"
#include "kynapse/vector_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002E4DC8(void*, const char*, ObjectBase* (*)());
extern void* D_0044FE48;
extern char D_003E4728;

extern "C" void func_002D8890(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&gClassInfo2B4988, "CEntityEyePosition", &CreateParameter28484C);
            return;
        }
        D_0044FE48 = &D_003E4728;
    }
}

EyePositionParameter& EyePositionParameter::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        position = ((const EyePositionParameter&)other).position;
    return *this;
}

extern "C" void func_002D8978() {
    func_002D8890(1, 0xFFFF);
}

extern "C" void func_002D8998() {
    func_002D8890(0, 0xFFFF);
}
