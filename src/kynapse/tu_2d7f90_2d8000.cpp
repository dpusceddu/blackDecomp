#include "kynapse/parameter_assign.hpp"
#include "ps2/prelude.h"

struct ObjectBase;
ObjectBase* CreateParameter2847AC();
extern "C" void* func_002DFEB0(void*, const char*, ObjectBase* (*)());
extern char D_0044F8D8;
extern void* D_0044F9E8;
extern char D_003E3D38;

extern "C" void func_002D8000(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002DFEB0(&D_0044F8D8, "CActionShoot", &CreateParameter2847AC);
            return;
        }
        D_0044F9E8 = &D_003E3D38;
    }
}

// ParamChangedMixed is the assignment view of CActionShoot.
// UNVERIFIED: payload meanings and uncalled ParameterRoot interface slots.
ParamChangedMixed& ParamChangedMixed::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo()) {
        const ParamChangedMixed& source = (const ParamChangedMixed&)other;
        SetTriple(source.triple);
        SetD(source.d);
    }
    return *this;
}

extern "C" void func_002D80F8() {
    func_002D8000(1, 0xFFFF);
}

extern "C" void func_002D8118() {
    func_002D8000(0, 0xFFFF);
}
