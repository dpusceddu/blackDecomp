#include "include_asm.h"

/* Remaining drafts in animation/tu_34b498. */
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "animation/graph_runtime.h"
#include "animation/graph.h"
#endif

extern s32 func_00347430(s32, s32, s32);
extern s32 func_0034B910();

s32 func_0034B5A8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x14);
}

void func_0034D920(s32 arg0, s32 arg1) {
    func_00347430(arg0, func_0034B910(), arg1);
}

#ifdef NON_MATCHING
// Unmatched: register allocation and division hazard scheduling.
float *Graph_SampleClip(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) {
    InstanceView *instance = (InstanceView *)owner;
    ClipView *clip = (ClipView *)node->children[0];
    SamplingContext context;
    int count;
    float span, spacing;
    if (!clip)
        return 0;
    if (instance->skeletonIndex == -1)
        instance->skeletonIndex = Clip_GetSkeleton(clip);
    SamplingContext_Init(&context, owner, (ClipView *)node->children[0]);
    count = Clip_GetSampleCount((ClipView *)node->children[0]);
    span = AnimationGraph_ReadSpan(node, bank);
    spacing = span / (float)count;
    instance->evaluationFlags |= ((ClipView *)node->children[0])->flags;
    instance->selectedClip = (ClipView *)node->children[0];
    if (flags & 4)
        return SamplingContext_Header(&context, current, previous, span, count, spacing, flags);
    return SamplingContext_Whole(&context, current, previous, span, count, spacing, flags);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34b5a8", func_0034B5B0);
#endif
#ifdef NON_MATCHING
// Unmatched: transition branch scheduling and live float allocation.
float *Graph_TimedTransition(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) {
    AnimationGraphNode *first, *second;
    TransitionTiming *timing;
    float delta = current - previous, secondTime, blend, outgoing;
    float *a, *b;
    if (node->childCount < 2)
        return 0;
    timing = (TransitionTiming *)node->parameters;
    first = node->children[0];
    second = node->children[1];
    if (current < timing->start)
        return AnimationGraph_EvaluateNode(owner, first, bank, current, previous, flags, rate, weight);
    secondTime = current - timing->start;
    if (current >= timing->start + timing->blend) {
        if (timing->subtractBlend == 1)
            secondTime -= timing->blend;
        return AnimationGraph_EvaluateNode(owner, second, bank, secondTime, secondTime - delta, flags, rate,
            weight);
    }
    blend = ((current - timing->start) + 1.0f) / (timing->blend + 1.0f);
    outgoing = Graph_Advance(timing, timing->start, AnimationGraph_ReadSpan(node, bank), current);
    if (timing->mode == 1)
        outgoing = AnimationTime_Wrap(outgoing, AnimationGraph_ReadSpan(node, bank));
    a = AnimationGraph_EvaluateNode(owner, first, bank, outgoing, outgoing - delta, flags, rate,
        weight*(1.0f - blend));
    if (timing->subtractBlend == 1)
        current = 0.0f;
    else current -= timing->start;
    b = AnimationGraph_EvaluateNode(owner, second, bank, current, current - delta, flags, rate, weight*blend);
    return Pose_Blend(owner, a, b, flags, blend);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34b5a8", func_0034B6E0);
#endif
#ifdef NON_MATCHING
// Unmatched: child cursor allocation and sequence branch layout.
float *Graph_Sequence(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) {
    int count = node->childCount, index = 0;
    float cumulative = 0.0f;
    AnimationGraphNode **children = node->children, *selected;
    if (count == 0)
        return 0;
    if (count > 0) {
        AnimationGraphNode **cursor = children;
        do {
            float end = cumulative + AnimationGraph_ReadSpan(*cursor, bank);
            if (current < end) {
                selected = children[index];
                goto dispatch;
            }
            ++index;
            ++cursor;
            cumulative = end;
        }
        while (index < count);
    }
    selected = children[index - 1];
    dispatch : return AnimationGraph_EvaluateNode(owner, selected, bank, current - cumulative,
        previous - cumulative, flags, rate, weight);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34b5a8", func_0034B910);
#endif
#ifdef NON_MATCHING
// Unmatched: weighted choice loop allocation.
int Graph_ChooseWeighted(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    InstanceView *instance = (InstanceView *)owner;
    ChoiceBinding *control = (ChoiceBinding *)node->parameters;
    int old = (int)*AnimationParameters_Get(bank, control->parameter), result = 0, index, count;
    AnimationGraphNode **child;
    float total = 0.0f, threshold, cumulative = 0.0f;
    if (control->excludePrevious && instance->evaluationFlags) {
        index = 0;
        count = node->childCount;
        child = node->children;
        if (count > 0)
            do {
            if (index != old)
                total += *(float *)(*child)->metadata;
            ++index;
            ++child;
        }
        while (index < count);
    }
    else {
        count = node->childCount;
        child = node->children;
        if (count > 0)
            do {
            AnimationGraphNode *item = *child++;
            --count;
            total += *(float *)item->metadata;
        }
        while (count);
    }
    threshold = Graph_Random()*total;
    if (control->excludePrevious && instance->evaluationFlags) {
        index = 0;
        while (index < node->childCount) {
            if (index != old)
                cumulative += *(float *)node->children[index]->metadata;
            if (threshold < cumulative) {
                result = index;
                break;
            }
            ++index;
        }
    }
    else {
        index = 0;
        if (node->childCount > 0) {
            cumulative += *(float *)node->children[0]->metadata;
            if (threshold < cumulative)
                result = 0;
            else {
                while (++index < node->childCount) {
                    cumulative += *(float *)node->children[index]->metadata;
                    if (threshold < cumulative) {
                        result = index;
                        break;
                    }
                }
            }
        }
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34b5a8", func_0034BA50);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34b5a8", func_0034BC30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34b5a8", func_0034BFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34b5a8", func_0034C0C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34b5a8", func_0034C128);
#ifdef NON_MATCHING
// Unmatched: func_0034B4E8 (192 bytes), flags: coordinate-boundary branch layout.
// Unmatched: func_0034B5B0 (304 bytes), types: clip-sampling stack object.
// Unmatched: func_0034B6E0 (556 bytes), types: transition state and floating call signatures.
// Unmatched: func_0034B910 (316 bytes), types: sequence state and floating call signatures.
// Unmatched: func_0034BA50 (476 bytes), types: weighted selection and float-to-integer conversion.
// Unmatched: func_0034BC30 (904 bytes), types: chooser callback and live floating arguments.
// Unmatched: func_0034BFE8 (224 bytes), types: control binding and floating arguments.
// Unmatched: func_0034C0C8 (92 bytes), scheduling: two division hazard NOPs.
// Unmatched: func_0034C128 (1712 bytes), types: graph blending state and stack temporaries.
// Unmatched: func_0034C7D8 (188 bytes), scheduling: three instruction differences.
float *AnimationGraph_PoseBoundControl(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    float *control = node->parameters;
    AnimationGraph_BindControl(owner, node, bank);
    return AnimationGraph_EvaluateControlled(owner, node, bank, flags, 1, current, previous,
        *AnimationParameters_Get(bank, ((int *)control)[3]), coefficient, weight);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34b5a8", func_0034C7D8);
#endif
