// Ported from the companion project (an unpublished companion project).
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x2e37a0
void ChildBuffers::DeleteChildren()
{
    if (count > 0) {
        for (unsigned int i = 0; i < count; ++i) {
            if (items[i])
                delete items[i];
        }
        count = 0;
    }
}

}  // namespace Kaim
