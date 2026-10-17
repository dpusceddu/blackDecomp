// Ported from the companion project (an unpublished companion project).
#include "kynapse/engine_create.hpp"

namespace Kaim {
// /SLUS_213.76 0x2d8448
bool Kaim_AllClassesRegistered()
{
    if (gClassId2B4874 == -1 ||
        gClassId2B547C == -1 ||
        gClassId2B475C == -1 ||
        gClassId2B5364 == -1 ||
        gClassId2B524C == -1 ||
        gClassId2B4644 == -1 ||
        gClassId2B3B54 == -1 ||
        gClassId2B4414 == -1 ||
        gClassId2B3C6C == -1 ||
        gClassId2B452C == -1 ||
        gClassId2B5134 == -1 ||
        gClassId2B498C == -1 ||
        gClassId2B501C == -1 ||
        gClassId2B41E4 == -1 ||
        gClassId2B4F04 == -1 ||
        gClassId2B40CC == -1 ||
        gClassId2B4DEC == -1 ||
        gClassId2B3FB4 == -1 ||
        gClassId2B42FC == -1 ||
        gClassId2B4CD4 == -1 ||
        gClassId2B4BBC == -1 ||
        gClassId2B3D84 == -1 ||
        gClassId2B4AA4 == -1)
        return false;
    return true;
}

}  // namespace Kaim
