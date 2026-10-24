// Ported from an unpublished companion project.
#include "kynapse/child_buffers.hpp"

namespace Kaim {
// /SLUS_213.76 0x2e3330
const char* ChildBuffers::FindThirdBySecond(const char* secondKey) const
{
    if (!secondKey)
        return 0;
    for (unsigned int i = 0; i < count; ++i) {
        if (items[i]->second && !_stricmp(items[i]->second, secondKey))
            return items[i]->third;
    }
    return 0;
}

// /SLUS_213.76 0x2e33e0
ChildBuffers* ChildBuffers::GetChild(unsigned int index) const
{
    if (index >= count)
        return 0;
    return items[index];
}

}  // namespace Kaim
