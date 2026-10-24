#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/forwarders.hpp"

// /SLUS_213.76 0x2e1280

bool Entity_Query(EntityObject* entity, int argument)
{
    if (!entity)
        return false;
    return entity->Query(argument);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E12B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E13B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E14B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E14D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1508);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1518);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1528);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1538);
