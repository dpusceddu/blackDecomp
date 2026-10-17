// Ported from the companion project (an unpublished companion project).
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x2dfc38
PointerBankOwner::~PointerBankOwner()
{
    if (count) {
        for (int i = 0; i < count; ++i) {
            if (items[i])
                delete items[i];
        }
        memoryRelease(items);
    }
}

}  // namespace Kaim
