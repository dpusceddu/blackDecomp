#include "include_asm.h"

#include "animation/graph_runtime.h"
#ifdef NON_MATCHING
#include "animation/graph.h"
#endif
/* Inferred graph callback names; the linked symbols remain the retail address aliases. */

float *Graph_WindowClip(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) {
    InstanceView *instance = (InstanceView *)owner;
    ClipView *clip = (ClipView *)node->children[0];
    float *window = node->parameters;
    SamplingContext context;
    float spacing, span;
    int count;
    float *result;
    SamplingContext_Init(&context, owner, clip);
    if (!clip) {
        result = 0;
        goto done;
    }
    if (instance->skeletonIndex == -1)
        instance->skeletonIndex = Clip_GetSkeleton(clip);
    if (flags & 0x20) {
        result = 0;
        goto done;
    }
    if (!(flags & 8))
        Clip_Events(clip, owner, current, previous, AnimationGraph_ReadSpan(node, bank), flags);
    current += window[0];
    if (window[1] + 1.0f <= current)
        current = window[1] + 0.999f;
    spacing = window[2];
    span = AnimationGraph_ReadSpan(node, bank);
    count = Clip_GetSampleCount(clip);
    if (flags & 4)
        result = SamplingContext_Header(&context, current, previous, span, count, spacing, flags);
    else result = SamplingContext_Whole(&context, current, previous, span, count, spacing, flags);
    done:
    return result;
}


#ifdef NON_MATCHING
// Unmatched: func_0034E5C0 (404 bytes), types: recursive bind stack aggregate.
// Unmatched: func_0034E828 (220 bytes), scheduling: inverse-control call layout.
void AnimationGraph_BindInverseControl(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    int *binding = (int *)node->parameters;
    float value = AnimationEvents_Invoke(binding[1], owner);
    if (value != 0.0f) {
        *AnimationParameters_Get(bank, binding[0]) = 1.0f / value;
        if (*AnimationParameters_Get(bank, binding[0]) > 10000.0f)
            *AnimationParameters_Get(bank,
            binding[0]) = 10000.0f;
    } else *AnimationParameters_Get(bank, binding[0]) = 1000.0f;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034E828);
#endif
