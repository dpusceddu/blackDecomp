// Ported from the companion project (an unpublished companion project).
#include "kynapse/parameter_assign.hpp"

// /SLUS_213.76 0x2d8770
ParamFlag& ParamFlag::operator=(const ParameterRoot& other)
{
    if (other.GetClassInfo() == GetClassInfo())
        a = ((const ParamFlag&)other).a;
    return *this;
}
