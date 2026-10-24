#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/parameter_assign.hpp"

// /SLUS_213.76 0x2d8770

ParamFlag& ParamFlag::operator=(const ParameterRoot& other)
{
    if (other.GetClassInfo() == GetClassInfo())
        a = ((const ParamFlag&)other).a;
    return *this;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D87E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D8808);
