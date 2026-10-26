#include "kynapse/parameter_assign.hpp"
#include "ps2/prelude.h"

extern "C" void func_002E4DC8(void*, const char*, void (*)());
extern "C" void func_002D8CD8();
extern char D_00450080;
extern void* D_00450190;
extern char D_003E4728;

extern "C" void func_002D8D40(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E4DC8(&D_00450080, "CEntityHearingAcuteness", &func_002D8CD8);
            return;
        }
        D_00450190 = &D_003E4728;
    }
}

// ParamClampedOne is the assignment view of CEntityHearingAcuteness.
// UNVERIFIED: payload semantics and uncalled ParameterRoot interface slots.
ParamClampedOne& ParamClampedOne::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo()) {
        const ParamClampedOne& source = (const ParamClampedOne&)other;
        if (source.a >= 0.0f)
            a = source.a;
        else
            a = 0.0f;
    }
    return *this;
}

extern "C" void func_002D8E20() {
    func_002D8D40(1, 0xFFFF);
}

extern "C" void func_002D8E40() {
    func_002D8D40(0, 0xFFFF);
}
