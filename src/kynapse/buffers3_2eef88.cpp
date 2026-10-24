// Ported from an unpublished companion project.
#include "kynapse/buffers3.hpp"

// /SLUS_213.76 0x2eef88
ObjectBase* CreateBoundBuffers(BufferOwner* bound)
{
    return new BoundBuffers(bound);
}
