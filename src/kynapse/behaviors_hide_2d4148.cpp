#include "include_asm.h"

#include "kynapse/behaviors/hide_search.hpp"
#include "kynapse/compat.hpp"
#ifdef NON_MATCHING
#include "kynapse/hide_agent.hpp"
#endif
namespace HideSearch {

HideAgent::HideAgent(Context* context):Behavior(context),rank((unsigned)-1) {
 currentId=0x7fffffff;maxDangerous=20;graphSlot=(unsigned)-1;perception=0;provider=0;offsetProperty=0;dangerous=0;nodes=0;dangerousCount=0;graph=0;lookup=0;currentNode=0;
}
void HideAgent::Scan(const Vec3* offset)
{
    if (stage == -1 && graphSlot != -1) {
        if (mode == 1) {
            unsigned int i = 0;
            if (dangerousCount > 0) {
                do {
                    if (section) {
                        nodes[i] = NavigationGraph_QueryNode(&dangerous[i]->position, context->actor,
                                                             maxDeltaHeight, section, 0, 0);
                    } else {
                        nodes[i] = NavigationGraph_FindNearestNode(graph, &dangerous[i]->position, context->actor,
                                                                   maxDeltaHeight, 0, 0);
                    }
                    if (!nodes[i]) {
                        fresh = true;
                        hasBest = false;
                        found = false;
                        return;
                    }
                    ++i;
                } while (i < dangerousCount);
            }
        } else if (mode == 2) {
            if (section) {
                currentNode = NavigationGraph_QueryNode(&context->actor->position, context->actor, maxDeltaHeight, section,
                                                 0, 0);
            } else {
                currentNode = NavigationGraph_FindNearestNode(graph, &context->actor->position, context->actor,
                                                       maxDeltaHeight, 0, 0);
            }
            if (!currentNode) {
                fresh = true;
                hasBest = false;
                found = false;
                return;
            }
        }
    }
    unsigned int index = stage + 1;
    if (index < graph->count) {
        do {
            Candidate* candidate=graph->GetNode(index);
            if (candidate) {
                bool handled;
                if (!Consider(candidate, offset, &handled)) {
                    stage = index - 1;
                    fresh = false;
                    return;
                }
                if (handled == true)
                    break;
            }
            ++index;
        } while (index < graph->count);
    }
    fresh = true;
    stage = -1;
    bestScore = -3.4028235e38f;
    hasBest = false;
    Reset();
}


bool HideAgent::Search()
{
    bool hidden=true;
    Vec3 offset = gOrigin;
    if (offsetProperty) {
        Vec3 propertyPosition=offsetProperty->value;
        offset.y = propertyPosition.y - context->actor->position.y;
    }
    if (visibilityState == 0x101) {
        Vec3 observer = gOrigin;
        Vec3 shifted=destination+offset;
        unsigned int i = 0;
        if (dangerousCount > 0) {
            do {
                VectorProperty* property = (VectorProperty*)dangerous[i]->GetAuthoredProperty(&gKeyPosition);
                if (property) {
                    observer = Vec3(property->value);
                } else {
                    observer = dangerous[i]->position;
                }
                if (Kaim_CallHook(&observer, &shifted, dangerous[i], 1)) {
                    hidden=false;
                    break;
                }
                ++i;
            } while (i < dangerousCount);
        }
    }
    if(hidden) {
        if(found) {
            if(dangerousCount) {
                if(fresh)goto result;
            }
        }
    }
    if(graph)goto scan;
    return false;
scan: Scan(&offset);
result: return found;
}


// Unmatched: SetGraph registry and component-loop allocation.
// Unmatched: Consider retains one missing argument move.
// Unmatched: Test vector lifetimes and visibility-loop scheduling.
// Unmatched: Evaluate query temporaries and iterator allocation.
}

#ifdef NON_MATCHING
using namespace HideViews;
namespace HideViews {
// Unmatched: observer/target vector temporaries differ.
    bool HideAgent::Test(const Candidate* candidate, const Vec3* offset, bool* seen)
   {
        Vec3 observer = gOrigin;
        Vec3 target;
        target.x = candidate->position.x + offset->x;
        target.y = candidate->position.y + offset->y;
        target.z = candidate->position.z + offset->z;
        *seen = false;
        ParameterTables* tables = (ParameterTables*)GetNameTables();
        bool result;
        if (tables->Consume(checkName, context->actor)) {
            bool visible = false;
            unsigned int i = 0;
            if (dangerousCount > 0) {
                do {
                    VectorProperty* property = (VectorProperty*)dangerous[i]->GetAuthoredProperty(&gKeyPosition);
                    if (property) {
                        Vec3 position;
                        position.x = property->value.x;
                        position.y = property->value.y;
                        position.z = property->value.z;
                        observer = position;
                    }
                    else {
                        observer = dangerous[i]->position;
                    }
                    visible = Kaim_CallHook(&observer, &target, dangerous[i], 1);
                }
                while (!visible && ++i < dangerousCount);
            }
            tables->Accumulate(checkName, context->actor);
            if (!visible) {
                *seen = true;
                return true;
            }
            return true;
        }
        else {
            result = false;
        }
        return result;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_hide_2d4148", func_002D49A8);
#endif
#ifdef NON_MATCHING
namespace HideViews {
// Unmatched: controller-object lifetimes and distance-helper temporaries differ.
    bool HideAgent::Evaluate(const Candidate* candidate, const Vec3* offset, float* score, bool* handled,
    bool* proceed)
   {
        *handled = false;
        *proceed = true;
        float total = 0;
        float spare = 0;
        bool seen;
        switch (mode) {
            case 1: {
                if (graphSlot != -1) {
                    VectorController from((const int*)candidate, graphSlot);
                    for (unsigned int i = 0; i < dangerousCount; ++i) {
                        void** node = (void**)nodes[i];
                        VectorController to((const int*)node, graphSlot, true);
                        float distance;
                        provider->Rate(&distance, &from, &to);
                        total = total + distance;
                    }
                }
                else {
                    unsigned int remaining = dangerousCount;
                    Actor** cursor = dangerous;
                    while (remaining != 0) {
                        Actor* actor = *cursor++;
                        --remaining;
                        float dx = actor->position.x - candidate->position.x;
                        float dy = actor->position.y - candidate->position.y;
                        float dz = actor->position.z - candidate->position.z;
                        total = total + sqrtf(dx * dx + dy * dy + dz * dz);
                    }
                }
                if (!(total > farLimit))
                return false;
                *proceed = Test(candidate, offset, &seen);
                if (!*proceed)
                return false;
                if (!seen)
                return false;
                farLimit = total;
                *score = total;
                return true;
            }
            case 2: {
                if (graphSlot != -1) {
                    VectorController from((const int*)candidate, graphSlot);
                    VectorController to((const int*)currentNode, graphSlot);
                    provider->Rate(&total, &from, &to);
                }
                else {
                    float dx = context->actor->position.x - candidate->position.x;
                    float dy = context->actor->position.y - candidate->position.y;
                    float dz = context->actor->position.z - candidate->position.z;
                    total = dx * dx + dy * dy + dz * dz;
                }
                if (!(total < nearLimit))
                return false;
                *proceed = Test(candidate, offset, &seen);
                if (!*proceed)
                return false;
                if (!seen)
                return false;
                nearLimit = total;
                *score = 1.0f / total;
                return true;
            }
        }
        return false;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_hide_2d4148", func_002D4B68);
#endif
