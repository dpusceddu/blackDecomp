#include "include_asm.h"

#include "kynapse/behaviors/hide.hpp"

namespace HideRecovery {

bool HideAgent::Init(ChildBuffers* config)
{
    destination = gOrigin;
    allHidden = false;
    active = false;
    dangerousCount = 0;
    found = false;
    fresh = true;
    stage = -1;
    farLimit = 0;
    nearLimit = 3.4028235e38f;
    hasBest = false;
    bestScore = -3.4028235e38f;
    maxDeltaHeight = gEngine->unit;
    NameTable* names = GetNameTables();
    computeName = names->FindName("CHideAgent::ComputeDestination");
    nextTime = 0;
    checkName = names->FindName("CHideAgent::CheckPositionVisible");
    graph = 0;
    mode = 2;
    if (!ConfigureAll(config)) return false;
    provider = (TargetEntity*)((ClassRegistryA*)context)->FindByClass(&gTargetClass);
    perception = ((ClassRegistryA*)context)->FindByClass(&gPerceptionClass);
    lookup = (LookupService*)((ClassRegistryB*)gEngine)->FindByClass(&gLookupClass);
    offsetProperty = (VectorProperty*)context->actor->GetAuthoredProperty(&gKeyPosition);
    if (!Prepare()) return false;
    if (!Validate()) return false;
    if (maxDangerous > 0) {
        dangerous = (Actor**)KaimAllocate(maxDangerous * 4);
        nodes = (void**)KaimAllocate(maxDangerous << 2);
    }
    return true;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D4148);
