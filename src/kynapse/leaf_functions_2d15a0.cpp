#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/leaf_functions.hpp"

// /SLUS_213.76 0x2d15a0

bool Kaim_AllIdsValid()
{
    if (gIdA == -1 || gIdB == -1 || gIdC == -1 || gIdD == -1 || gIdE == -1 || gIdF == -1 || gIdG == -1)
        return false;
    return true;
}
