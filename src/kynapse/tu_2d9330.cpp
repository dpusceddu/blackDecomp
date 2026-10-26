#include "kynapse/parameter_classes.hpp"
#include "kynapse/dimension_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void func_002E4DC8(void*, const char*, ObjectBase* (*)());
extern void* D_004505F0;
extern char D_003E4728;

ObjectBase* CreateParameter284728() {
    return new Parameter284728;
}

extern "C" void func_002D93C0(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&gClassInfo2B3FB0, "CEntityMaxSpeed", &CreateParameter284728);
            return;
        }
        D_004505F0 = &D_003E4728;
    }
}

MaxSpeedParameter& MaxSpeedParameter::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        maxSpeed = ((const MaxSpeedParameter&)other).maxSpeed;
    return *this;
}

extern "C" void func_002D9488() {
    func_002D93C0(1, 0xFFFF);
}

extern "C" void func_002D94A8() {
    func_002D93C0(0, 0xFFFF);
}
