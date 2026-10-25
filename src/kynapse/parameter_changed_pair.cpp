#include "include_asm.h"

#include "kynapse/parameter_changed_ps2.hpp"

ParamChangedPair& ParamChangedPair::operator=(const ParameterRoot& other)
{
    if (other.GetClassInfo() == GetClassInfo()) {
        const ParamChangedPair& source = (const ParamChangedPair&)other;
        SetA(source.a);
        SetB(source.b);
    }
    return *this;
}

