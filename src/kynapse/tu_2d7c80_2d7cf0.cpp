#include "kynapse/parameter_classes.hpp"
#include "kynapse/action_parameters.hpp"
#include "ps2/prelude.h"

extern "C" void* func_002DFEB0(void*, const char*, ObjectBase* (*)());
extern void* D_0044F7B8;
extern char D_003E3D38;

extern "C" void func_002D7CF0(s32 enabled, s32 phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002DFEB0(&gClassInfo2B4640, "CActionJump", &CreateParameter2847EC);
            return;
        }
        D_0044F7B8 = &D_003E3D38;
    }
}

JumpAction& JumpAction::operator=(const ParameterRoot& other) {
    if (other.GetClassInfo() == GetClassInfo())
        SetRequested(((const JumpAction&)other).requested);
    return *this;
}

extern "C" void func_002D7DC8() {
    func_002D7CF0(1, 0xFFFF);
}

extern "C" void func_002D7DE8() {
    func_002D7CF0(0, 0xFFFF);
}
