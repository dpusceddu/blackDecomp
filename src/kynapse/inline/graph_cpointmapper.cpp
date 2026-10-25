#include "include_asm.h"

#include "kynapse/classes/Kaim_CPointMapper.hpp"
extern "C" const char *func_002E3920(void *);

int Unnamed::Kaim_CPointMapper::Function_0038E768(void *config) {
    if (config && func_002E3920(config) && *(const signed char *)func_002E3920(config) == '_') return 1;
    return 0;
}

