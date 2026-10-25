#include "include_asm.h"

#include "kynapse/behaviors/hide.hpp"
#ifdef NON_MATCHING
#include "kynapse/graph/brain.hpp"
#endif
extern const float kNearestLimit;
namespace HideViews {

void HideAgent::Reset() {
    farLimit=0;
    nearLimit=kNearestLimit;
}
}
const float kNearestLimit=3.4028234663852886e+38F;

#ifdef NON_MATCHING
using namespace Kaim;
// Unmatched: handler factory target register differs by four instructions.
CBrain::CBrain(void *ownerValue, BrainHandlerClass *handlerClass)
{
    agentCount = 0;
    serviceCount = 0;
    owner = ownerValue;
    if (func_0038BA30()->count)
        agents = (BrainComponent**)Allocate(func_0038BA30()->count * 4);
    else
        agents = 0;
    if (func_0038C3E0()->count)
        services = (BrainComponent**)Allocate(func_0038C3E0()->count * 4);
    else
        services = 0;
    if (!handlerClass->create)
        handler = 0;
    else
        handler = handlerClass->create();
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_hide_reset", func_002E1548);
#endif
#ifdef NON_MATCHING
// Unmatched: owned-array cleanup branches and pointer lifetimes differ.
CBrain::~CBrain()
{
    if (handler)
        delete handler;
    if (agents) {
        for (int i = 0; i < agentCount; ++i)
            delete agents[i];
        D_003C87E0(agents);
    }
    if (services) {
        for (int i = 0; i < serviceCount; ++i)
            delete services[i];
        D_003C87E0(services);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_hide_reset", func_002E16B8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_hide_reset", func_002E4E28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_hide_reset", func_002E52C8);
