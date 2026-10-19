#include "kynapse/batch10.hpp"

void CreatableCache::Select(TypeInfo* type)
{
    Creatable** slot = &slots[type->id];
    if (!*slot) {
        *slot = type->create();
        (*slot)->Init(argument);
    }
    current = *slot;
}
