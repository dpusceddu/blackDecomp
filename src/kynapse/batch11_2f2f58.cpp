#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/batch11.hpp"

// /SLUS_213.76 0x2f2f58

int ItemList::IdByName(const char* name)
{
    for (unsigned int i = 0; i < count; ++i) {
        if (_stricmp(name, items[i]->name + 4) == 0)
            return items[i]->id;
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F2FF0);
