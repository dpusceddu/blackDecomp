// Ported from the companion project (an unpublished companion project).
#include "kynapse/parameter_assign.hpp"

// /SLUS_213.76 0x2d9598
ParamInt& ParamInt::operator=(const ParameterRoot& other)
{
    if (other.GetClassInfo() == GetClassInfo())
        a = ((const ParamInt&)other).a;
    return *this;
}
