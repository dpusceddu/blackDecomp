#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/type_registry.hpp"

// /SLUS_213.76 0x2f30e8

Component* TypeRegistry::Find(int typeId, ClassInfo* wanted)
{
    for (unsigned int i = 0; i < count; ++i) {
        if (entries[i]->typeId == typeId) {
            for (unsigned int j = 0; j < entries[i]->componentCount; ++j) {
                if (wanted == entries[i]->components[j]->GetClassInfo())
                    return entries[i]->components[j];
            }
        }
    }
    return 0;
}
