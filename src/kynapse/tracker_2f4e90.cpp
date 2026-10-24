// Ported from an unpublished companion project.
#include "kynapse/tracker.hpp"

// /SLUS_213.76 0x2f4e90
bool Tracker::Init(ChildBuffers* config)
{
    capacity = 0x14;
    registry = gEngine->FindByClass(&gTypeRegistryClass);
    if (!ConfigureAll(config))
        return false;
    items = (Tracked**)KaimAllocate(capacity * 4);
    for (unsigned int i = 0; i < capacity; ++i)
        items[i] = 0;
    return true;
}
