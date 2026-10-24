#include "include_asm.h"

#include "kynapse/perception.hpp"

void Perception::ClearRequests()
{
    dirtyCone = false;
    dirtyGroup = false;
}
