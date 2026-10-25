#include "include_asm.h"

#include "kynapse/type_registry.hpp"

void CreatableCache::Select(TypeInfo* type)
{
    Creatable** slot = &slots[type->id];
    if (!*slot) {
        *slot = type->create();
        (*slot)->Init(argument);
    }
    current = *slot;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00304D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00304D60);
