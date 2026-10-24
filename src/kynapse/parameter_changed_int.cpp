#include "include_asm.h"

#include "kynapse/parameter_changed_ps2.hpp"

ParamChangedInt& ParamChangedInt::operator=(const ParameterRoot& other)
{
    if (other.GetClassInfo() == GetClassInfo())
        SetA(((const ParamChangedInt&)other).a);
    return *this;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D8280);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D82A0);
