#include "include_asm.h"

#include "kynapse/behaviors/hide.hpp"
#ifdef NON_MATCHING
#include "kynapse/hide_agent.hpp"
#endif

namespace HideViews {

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

#ifdef NON_MATCHING
using namespace HideViews;
namespace HideViews {
// Unmatched: registry/component iterator registers differ.
    bool HideAgent::SetGraph(void* id)
   {
        graph = (NodeGraph*)id;
        graphSlot = -1;
        section = 0;
        TypeList* types = (TypeList*)((ClassRegistryB*)gEngine)->FindByClass(&gTypeListClass);
        if (!types)
        return false;
        LookupService* slots = (LookupService*)((ClassRegistryB*)gEngine)->FindByClass(&gLookupClass);

        if (types->count > 0) {
            TypeEntry** cursor = types->entries;
            unsigned int i = 0;
            do {
                TypeEntry* entry = *cursor;
                if (entry->id == (int)graph) {
                    unsigned int j = 0;
                    if (entry->componentCount > 0) {

                        do {
                            if (entry->components[j]->GetClassInfo() == &gSectionClass) {
                                section = (NodeGraph*)entry->components[j];
                                break;
                            }
                            ++j;
                        }
                        while (j < entry->componentCount);
                    }
                    if (slots && !slots->Lookup(entry->key, &graphSlot))
                    graphSlot = -1;
                    return true;
                }
                ++i;
                ++cursor;
            }
            while (i < types->count);
        }
        return true;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D4148);
#endif
