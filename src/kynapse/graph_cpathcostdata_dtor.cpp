#include "include_asm.h"

#include "kynapse/graph/tables.hpp"

Kaim::CPathCostData::~CPathCostData()
{
    if (table) D_003C87E0(table);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F4330);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F4350);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F4370);
