#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/lookups.hpp"

namespace Kaim {
// /SLUS_213.76 0x2e11a0

bool Kaim_DestroyEngine(ReleasableEngine* engine)
{
    if (!engine)
        return false;
    int index = engine->slot;
    delete engine;
    gEngineSlots[index] = 0;
    gEngine = 0;
    return true;
}

}  // namespace Kaim

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1228);
