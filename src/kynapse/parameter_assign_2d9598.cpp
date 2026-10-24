#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/parameter_assign.hpp"

// /SLUS_213.76 0x2d9598

ParamInt& ParamInt::operator=(const ParameterRoot& other)
{
    if (other.GetClassInfo() == GetClassInfo())
        a = ((const ParamInt&)other).a;
    return *this;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D9610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D9630);
