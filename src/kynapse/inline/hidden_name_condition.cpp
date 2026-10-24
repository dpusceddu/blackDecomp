#include "include_asm.h"

#include "kynapse/leaf_functions.hpp"

// The PS2 condition callback receives its context before the configuration object.

bool Kaim_IsHiddenName(void* context, const NamedObject* object)
{
    if (object && object->GetName() && *object->GetName() == '_')
        return true;
    return false;
}
