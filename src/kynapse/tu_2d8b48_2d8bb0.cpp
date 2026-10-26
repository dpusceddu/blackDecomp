#include "kynapse/parameter_classes.hpp"
#include "kynapse/vector_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002E4DC8(void*, const char*, ObjectBase* (*)());
extern void* D_00450078;
extern char D_003E4728;

extern "C" void func_002D8BB0(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&gClassInfo2B5018, "CEntityHeadDirection", &CreateParameter284928);
            return;
        }
        D_00450078 = &D_003E4728;
    }
}

HeadDirectionParameter& HeadDirectionParameter::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        direction = ((const HeadDirectionParameter&)other).direction;
    return *this;
}

extern "C" void func_002D8C98() {
    func_002D8BB0(1, 0xFFFF);
}

extern "C" void func_002D8CB8() {
    func_002D8BB0(0, 0xFFFF);
}
