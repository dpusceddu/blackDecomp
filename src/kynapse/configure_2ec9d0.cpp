#include "include_asm.h"

// Ported from an unpublished companion project.
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ECAA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ECAF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ECB30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ECB40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ECB60);
