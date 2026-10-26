#ifndef BLACK_KYNAPSE_VECTOR_PARAMETERS_HPP
#define BLACK_KYNAPSE_VECTOR_PARAMETERS_HPP

#include "kynapse/parameter_assign.hpp"

// Partial assignment views of the RTTI-named entity parameters.
// UNVERIFIED: complete interfaces and uncalled inherited virtual slots.
// Coordinate frames and the orientation convention are also UNVERIFIED.
struct EyePositionParameter : ParameterRoot {
    Triple position;
    EyePositionParameter& operator=(const ParameterRoot&) __asm__("func_002D88E8");
};

struct GunPositionParameter : ParameterRoot {
    Triple position;
    GunPositionParameter& operator=(const ParameterRoot&) __asm__("func_002D8A78");
};

struct KneePositionParameter : ParameterRoot {
    Triple position;
    KneePositionParameter& operator=(const ParameterRoot&) __asm__("func_002D90C0");
};

struct TorsoOrientationParameter : ParameterRoot {
    Triple orientation;
    TorsoOrientationParameter& operator=(const ParameterRoot&) __asm__("func_002D9710");
};

#endif
