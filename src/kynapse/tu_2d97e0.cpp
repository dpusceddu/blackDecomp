#include "kynapse/parameter_classes.hpp"
#include "kynapse/parameter_assign.hpp"
#include "ps2/prelude.h"

extern "C" void func_002E4DC8(void*, const char*, ObjectBase* (*)());
extern void* D_00450938;
extern char D_003E4728;
extern "C" void SetVisualAngle(ParamClamped*, float) __asm__("func_002D9970");

ObjectBase* CreateParameter2848B4() {
    return new Parameter2848B4;
}

extern "C" void func_002D9880(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&gClassInfo2B4CD0, "CEntityVisualAcuteness", &CreateParameter2848B4);
            return;
        }
        D_00450938 = &D_003E4728;
    }
}

// ParamClamped is the assignment view of CEntityVisualAcuteness: a is range, b is angle.
// UNVERIFIED: uncalled slots in the partial ParameterRoot interface.
ParamClamped& ParamClamped::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo()) {
        const ParamClamped& source = (const ParamClamped&)other;
        if (source.a >= 0.0f)
            a = source.a;
        else
            a = 0.0f;
        SetVisualAngle(this, source.b);
    }
    return *this;
}

extern "C" void SetVisualAngle(ParamClamped* parameter, float angle) {
    float limit = 0.0f;
    if (angle < 0.0f) {
        parameter->b = limit;
        return;
    }
    limit = 360.0f;
    if (!(angle > 360.0f)) {
        parameter->b = angle;
        return;
    }
    parameter->b = limit;
}

extern "C" void func_002D99B8() {
    func_002D9880(1, 0xFFFF);
}

extern "C" void func_002D99D8() {
    func_002D9880(0, 0xFFFF);
}
