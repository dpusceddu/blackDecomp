#include "kynapse/parameter_classes.hpp"
#include "kynapse/dimension_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void func_002E4DC8(void*, const char*, ObjectBase* (*)());
extern void* D_004504D8;
extern char D_003E4728;

ObjectBase* CreateParameter284708() {
    return new Parameter284708;
}

extern "C" void func_002D9228(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&gClassInfo2B3E98, "CEntityLength", &CreateParameter284708);
            return;
        }
        D_004504D8 = &D_003E4728;
    }
}

LengthParameter& LengthParameter::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        length = ((const LengthParameter&)other).length;
    return *this;
}

extern "C" void func_002D92F0() {
    func_002D9228(1, 0xFFFF);
}

extern "C" void func_002D9310() {
    func_002D9228(0, 0xFFFF);
}
