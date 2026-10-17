// Ported from the companion project (an unpublished companion project).
#include "kynapse/configure.hpp"

namespace Kaim {
// /SLUS_213.76 0x2ec9d0
bool ConfigHostB::ConfigureAll(ChildBuffers* config)
{
    if (config) {
        for (unsigned int i = 0; i < config->count; ++i) {
            if (_stricmp(config->GetChild(i)->GetSecond(), "Class")) {
                if (!ConfigureChild(config->GetChild(i)))
                    return false;
            }
        }
    }
    return true;
}

}  // namespace Kaim
