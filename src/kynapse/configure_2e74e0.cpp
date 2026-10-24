#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/configure.hpp"

namespace Kaim {
// /SLUS_213.76 0x2e74e0

bool ConfigHost::ConfigureAll(ChildBuffers* config)
{
    for (unsigned int i = 0; i < config->count; ++i) {
        if (_stricmp(config->GetChild(i)->GetSecond(), "Class")) {
            if (!Configure(config->GetChild(i)))
                return false;
        }
    }
    return true;
}

}  // namespace Kaim
