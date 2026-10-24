// Ported from an unpublished companion project.
#include "kynapse/child_buffers.hpp"

namespace Kaim {
// /SLUS_213.76 0x2e3578
ChildBuffers* ChildBuffers::SetFirst(const char* text)
{
    KAIM_REPLACE_STRING(first)
}

// /SLUS_213.76 0x2e3630
ChildBuffers* ChildBuffers::SetSecond(const char* text)
{
    KAIM_REPLACE_STRING(second)
}

// /SLUS_213.76 0x2e36e8
ChildBuffers* ChildBuffers::SetThird(const char* text)
{
    KAIM_REPLACE_STRING(third)
}

}  // namespace Kaim
