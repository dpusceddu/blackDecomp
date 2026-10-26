#ifndef BLACK_KYNAPSE_DIMENSION_PARAMETERS_HPP
#define BLACK_KYNAPSE_DIMENSION_PARAMETERS_HPP

#include "kynapse/parameter_assign.hpp"

// Partial assignment views of the RTTI-named entity parameters.
// UNVERIFIED: complete interfaces and uncalled inherited virtual slots.
struct HeightParameter : ParameterRoot {
    float height;
    HeightParameter& operator=(const ParameterRoot&) __asm__("func_002D8F50");
};

struct LengthParameter : ParameterRoot {
    float length;
    LengthParameter& operator=(const ParameterRoot&) __asm__("func_002D9280");
};

struct MaxSpeedParameter : ParameterRoot {
    float maxSpeed;
    MaxSpeedParameter& operator=(const ParameterRoot&) __asm__("func_002D9418");
};

struct WidthParameter : ParameterRoot {
    float width;
    WidthParameter& operator=(const ParameterRoot&) __asm__("func_002D9AE8");
};

#endif
