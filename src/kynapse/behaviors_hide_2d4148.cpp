#include "include_asm.h"

#include "kynapse/behaviors/hide_search.hpp"
#include "kynapse/compat.hpp"
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D49A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D4B68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D5008);
