#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/perception.hpp"

// /SLUS_213.76 0x310120
// The record of a user (the first record when no user is given), marking the perception as read.

PerceptionRecord* Perception::GetRecord(SlotUser* user)
{
    dirtyCone = true;
    dirtyGroup = true;
    if (user) {
        int index = user->GetIndex();
        Refresh(index);
        return &records[index];
    }
    return records;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310190);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310248);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310268);
