#include "kynapse/parameter_classes.hpp"
#include "kynapse/vector_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002E4DC8(void*, const char*, ObjectBase* (*)());
extern void* D_0044FF60;
extern char D_003E4728;

extern "C" void func_002D8A20(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&gClassInfo2B41E0, "CEntityGunPosition", &CreateParameter284768);
            return;
        }
        D_0044FF60 = &D_003E4728;
    }
}

GunPositionParameter& GunPositionParameter::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        position = ((const GunPositionParameter&)other).position;
    return *this;
}

extern "C" void func_002D8B08() {
    func_002D8A20(1, 0xFFFF);
}

extern "C" void func_002D8B28() {
    func_002D8A20(0, 0xFFFF);
}
