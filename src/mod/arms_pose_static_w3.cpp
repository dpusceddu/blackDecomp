#include "animation/pose_campaign.hpp"

inline void* operator new[](unsigned, void* storage) { return storage; }

namespace ArmsPose {

void Cache::Construct(int initialize, int priority)
{
    if (priority == 0xffff && initialize) new(slots) Slot[28];
}

}
