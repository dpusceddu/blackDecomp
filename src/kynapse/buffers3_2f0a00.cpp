// Ported from the companion project (an unpublished companion project).
#include "kynapse/buffers3.hpp"

// /SLUS_213.76 0x2f0a00
BoundBuffers::BoundBuffers(BufferOwner* bound)
    : BoundBase(bound)
{
    handle = bound->handle;
    first = 0;
    second = 0;
    third = 0;
    count = 0;
}
