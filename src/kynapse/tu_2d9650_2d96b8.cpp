#include "kynapse/parameter_classes.hpp"
#include "kynapse/vector_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void func_002E4DC8(void*, const char*, ObjectBase* (*)());
extern void* D_00450820;
extern char D_003E4728;

extern "C" void func_002D96B8(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&gClassInfo2B4BB8, "CEntityTorsoOrientation", &CreateParameter28488C);
            return;
        }
        D_00450820 = &D_003E4728;
    }
}

TorsoOrientationParameter& TorsoOrientationParameter::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        orientation = ((const TorsoOrientationParameter&)other).orientation;
    return *this;
}

extern "C" void func_002D97A0() {
    func_002D96B8(1, 0xFFFF);
}

extern "C" void func_002D97C0() {
    func_002D96B8(0, 0xFFFF);
}
