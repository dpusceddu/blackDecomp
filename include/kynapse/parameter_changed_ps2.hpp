#ifndef BLACK_KYNAPSE_PARAMETER_CHANGED_PS2_HPP
#define BLACK_KYNAPSE_PARAMETER_CHANGED_PS2_HPP
#include "kynapse/parameter_assign.hpp"

// PS2 parameter views: these payloads use COP1 float loads and stores.

typedef char ParameterOffset_ParamChangedInt_changed[((unsigned int)&((ParamChangedInt*)0)->changed)==0x4?1:-1];
typedef char ParameterOffset_ParamChangedInt_a[((unsigned int)&((ParamChangedInt*)0)->a)==0x8?1:-1];
typedef char ParameterOffset_ParamChangedPair_changed[((unsigned int)&((ParamChangedPair*)0)->changed)==0x4?1:-1];
typedef char ParameterOffset_ParamChangedPair_a[((unsigned int)&((ParamChangedPair*)0)->a)==0x8?1:-1];
typedef char ParameterOffset_ParamChangedPair_b[((unsigned int)&((ParamChangedPair*)0)->b)==0xc?1:-1];

#endif
