#include "kynapse/parameter_classes.hpp"
#include "kynapse/dimension_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002E4DC8(void*, const char*, ObjectBase* (*)());
extern void* D_004502A8;
extern char D_003E4728;

ObjectBase* CreateParameter284748() {
    return new Parameter284748;
}

extern "C" void func_002D8EF8(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&gClassInfo2B40C8, "CEntityHeight", &CreateParameter284748);
            return;
        }
        D_004502A8 = &D_003E4728;
    }
}

HeightParameter& HeightParameter::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        height = ((const HeightParameter&)other).height;
    return *this;
}

extern "C" void func_002D8FC0() {
    func_002D8EF8(1, 0xFFFF);
}

extern "C" void func_002D8FE0() {
    func_002D8EF8(0, 0xFFFF);
}
