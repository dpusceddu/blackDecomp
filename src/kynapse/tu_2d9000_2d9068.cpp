#include "kynapse/parameter_classes.hpp"
#include "kynapse/vector_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void func_002E4DC8(void*, const char*, ObjectBase* (*)());
extern void* D_004503C0;
extern char D_003E4728;

extern "C" void func_002D9068(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&gClassInfo2B4DE8, "CEntityKneePosition", &CreateParameter2848DC);
            return;
        }
        D_004503C0 = &D_003E4728;
    }
}

KneePositionParameter& KneePositionParameter::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        position = ((const KneePositionParameter&)other).position;
    return *this;
}

extern "C" void func_002D9150() {
    func_002D9068(1, 0xFFFF);
}

extern "C" void func_002D9170() {
    func_002D9068(0, 0xFFFF);
}
