// Ported from the companion project (an unpublished companion project).
#include "kynapse/accessors.hpp"

// /SLUS_213.76 0x2dfbf8
void ActionBank::ClearActivation()
{
    for (int i = 0; i < count; ++i) {
        Action* action = actions[i];
        if (action)
            action->active = 0;
    }
}
