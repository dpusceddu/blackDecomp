#include "include_asm.h"

#include "kynapse/perception.hpp"

bool Perception::Init(ChildBuffers* config)
{
    if (!ConfigureAll(config))
        return false;
    int entities = gWorld->maxEntities;
    records = new PerceptionRecord[entities];
    if (!gPairFlags) {
        unsigned int pairs = (unsigned int)(gWorld->maxEntities * (gWorld->maxEntities - 1)) >> 1;
        if ((int)pairs > 0) {
            gPairFlags = (unsigned char*)KaimAllocate(pairs);
            memset(gPairFlags, 0, pairs);
            gPairExpiry = (float*)KaimAllocate(pairs << 2);
            memset(gPairExpiry, 0, pairs << 2);
            gPairLineExpiry = (float*)KaimAllocate(pairs << 2);
            memset(gPairLineExpiry, 0, pairs << 2);
            gPairDistances = (float*)KaimAllocate(pairs << 2);
            memset(gPairDistances, 0, pairs << 2);
        }
    }
    soundPool = (SoundPool*)gWorld->FindByClass(&gSoundPoolClass);
    computeName = GetNameTable8()->FindName("Kaim::CEntityManager::ComputeCommonInfo");
    if (computeName == -1)
        return false;
    originProperty = (AuthoredVector*)context->actor->GetAuthoredProperty(&gKeyPosition);
    axisProperty = (AuthoredVector*)context->actor->GetAuthoredProperty(&gKeyAxis);
    groupProperty = (AuthoredGroup*)context->actor->GetAuthoredProperty(&gKeyGroup);
    coneProperty = (AuthoredVector*)context->actor->GetAuthoredProperty(&gKeyCone);
    pendingCone = true;
    pendingGroup = true;
    pendingLine = true;
    Entity_ApplyC(gWorld, OnSubjectRemoved, this);
    return true;
}
