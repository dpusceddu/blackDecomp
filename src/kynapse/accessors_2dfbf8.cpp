#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/accessors.hpp"

// /SLUS_213.76 0x2dfbf8

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DFB00);

void ActionBank::ClearActivation()
{
    for (int i = 0; i < count; ++i) {
        Action* action = actions[i];
        if (action)
            action->active = 0;
    }
}
