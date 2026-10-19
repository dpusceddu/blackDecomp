#include "kynapse/parameter_changed_ps2.hpp"

ParamChangedInt& ParamChangedInt::operator=(const ParameterRoot& other)
{
    if (other.GetClassInfo() == GetClassInfo())
        SetA(((const ParamChangedInt&)other).a);
    return *this;
}
