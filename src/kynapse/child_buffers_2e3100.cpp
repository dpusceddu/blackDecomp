// Ported from the companion project (an unpublished companion project).
#include "kynapse/child_buffers.hpp"

namespace Kaim {
// /SLUS_213.76 0x2e3100
ChildBuffers* ChildBuffers::FindChild(const char* secondKey, const char* firstKey) const
{
    if (!secondKey || !firstKey)
        return 0;
    for (unsigned int i = 0; i < count; ++i) {
        if (items[i]->second && !_stricmp(items[i]->second, secondKey)) {
            if (items[i]->first && !_stricmp(items[i]->first, firstKey))
                return items[i];
        }
    }
    return 0;
}

// /SLUS_213.76 0x2e31e0
ChildBuffers* ChildBuffers::FindBySecond(const char* secondKey) const
{
    if (!secondKey)
        return 0;
    for (unsigned int i = 0; i < count; ++i) {
        if (items[i]->second && !_stricmp(items[i]->second, secondKey))
            return items[i];
    }
    return 0;
}

}  // namespace Kaim
