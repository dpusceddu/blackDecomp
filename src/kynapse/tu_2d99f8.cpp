#include "kynapse/parameter_classes.hpp"
#include "kynapse/dimension_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002E4DC8(void*, const char*, ObjectBase* (*)());
extern void* D_00450A50;
extern char D_003E4728;

ObjectBase* CreateParameter2846E4() {
    return new Parameter2846E4;
}

extern "C" void func_002D9A90(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&gClassInfo2B3D80, "CEntityWidth", &CreateParameter2846E4);
            return;
        }
        D_00450A50 = &D_003E4728;
    }
}

WidthParameter& WidthParameter::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        width = ((const WidthParameter&)other).width;
    return *this;
}

extern "C" void func_002D9B58() {
    func_002D9A90(1, 0xFFFF);
}

extern "C" void func_002D9B78() {
    func_002D9A90(0, 0xFFFF);
}
