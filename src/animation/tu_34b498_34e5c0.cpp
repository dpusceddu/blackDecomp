#include "animation/graph_runtime.h"
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

#ifdef NONMATCHING
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

// Unmatched: choice callback live argument allocation.
float *Graph_Choice(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float duration, float weight,
    AnimationChildChooser chooser, int forceChoice) {
    InstanceView *instance = (InstanceView *)owner;
    ChoiceBinding *control = (ChoiceBinding *)node->parameters;
    float *choice = AnimationParameters_Get(bank, control->parameter);
    int choose, selected;
    float blend, childSpan, parentSpan;
    float *first, *second;
    typedef int (*ChoiceCallback)(void *, AnimationGraphNode *, AnimationParameters *, unsigned int, float);
    if ((float)node->childCount <= *choice)
        return 0;
    if (forceChoice)
        choose = 1;
    else choose = Graph_Crosses(flags, current, previous, AnimationGraph_ReadSpan(node, bank));
    if (!instance->selectedClip)
        choose = 1;
    int blending = duration > 0.0f && (float)forceChoice == 0.0f && !(flags & 0x10);
    if (choose) {
        if (blending) {
            instance->previousChoice = (int)*AnimationParameters_Get(bank, control->parameter);
            instance->previousCoordinate = previous;
        }
        selected = ((ChoiceCallback)chooser)(owner, node, bank, flags, current);
        childSpan = AnimationGraph_ReadSpan(node->children[selected], bank);
        parentSpan = AnimationGraph_ReadSpan(node, bank);
        current = Graph_ChangedSpan(owner, node, bank, flags, childSpan, parentSpan, current);
        *AnimationParameters_Get(bank, control->parameter) = (float)selected;
    }
    if (blending) {
        blend = current / duration;
        if (instance->previousChoice >= 0 && instance->previousChoice != (int)*AnimationParameters_Get(bank,
            control->parameter) && blend < 1.0f) {
            float oldTime = instance->previousCoordinate;
            first = AnimationGraph_EvaluateNode(owner, node->children[instance->previousChoice], bank, oldTime,
                oldTime, flags, rate, (1.0f - blend)*weight);
            selected = (int)*AnimationParameters_Get(bank, control->parameter);
            second = AnimationGraph_EvaluateNode(owner, node->children[selected], bank, current, previous,
                flags, rate, blend*weight);
            return Pose_Blend(owner, first, second, flags, blend);
        }
    }
    selected = (int)*AnimationParameters_Get(bank, control->parameter);
    return AnimationGraph_EvaluateNode(owner, node->children[selected], bank, current, previous, flags, rate,
        weight);
}

// Unmatched: layer pose allocation and repeated span call ordering.
float *Graph_ComposedLayers(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) {
    AnimationGraphNode *first, *second, *third;
    float delta = current - previous, aTime, bTime, cTime;
    float *a, *b, *c;
    if (node->childCount < 2)
        return 0;
    first = node->children[0];
    second = node->children[1];
    aTime = AnimationTime_Wrap(current, AnimationGraph_ReadSpan(first, bank));
    bTime = AnimationTime_Wrap(current, AnimationGraph_ReadSpan(second, bank));
    if (node->childCount >= 3) {
        third = node->children[2];
        cTime = AnimationTime_Wrap(current, AnimationGraph_ReadSpan(third, bank));
        a = AnimationGraph_EvaluateNode(owner, first, bank, aTime, aTime - delta, flags, rate, weight);
        b = AnimationGraph_EvaluateNode(owner, second, bank, bTime, bTime - delta, flags, rate, weight);
        c = AnimationGraph_EvaluateNode(owner, third, bank, cTime, cTime - delta, flags, rate, weight);
        return Pose_Compose(owner, a, Pose_Difference(owner, b, c, flags), flags);
    }
    a = AnimationGraph_EvaluateNode(owner, first, bank, aTime, aTime - delta, flags, rate, weight);
    b = AnimationGraph_EvaluateNode(owner, second, bank, bTime, bTime - delta, flags, rate, weight);
    return Pose_Compose(owner, a, b, flags);
}

// Unmatched: layer pose allocation and repeated span call ordering.
float *Graph_DifferenceLayers(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) {
    AnimationGraphNode *first, *second, *third;
    float delta = current - previous, aTime, bTime, cTime;
    float *a, *b, *c;
    if (node->childCount < 2)
        return 0;
    first = node->children[0];
    second = node->children[1];
    aTime = AnimationTime_Wrap(current, AnimationGraph_ReadSpan(first, bank));
    bTime = AnimationTime_Wrap(current, AnimationGraph_ReadSpan(second, bank));
    if (node->childCount >= 3) {
        third = node->children[2];
        cTime = AnimationTime_Wrap(current, AnimationGraph_ReadSpan(third, bank));
        a = AnimationGraph_EvaluateNode(owner, first, bank, aTime, aTime - delta, flags, rate, weight);
        b = AnimationGraph_EvaluateNode(owner, second, bank, bTime, bTime - delta, flags, rate, weight);
        c = AnimationGraph_EvaluateNode(owner, third, bank, cTime, cTime - delta, flags, rate, weight);
        return Pose_Difference(owner, a, Pose_Difference(owner, b, c, flags), flags);
    }
    a = AnimationGraph_EvaluateNode(owner, first, bank, aTime, aTime - delta, flags, rate, weight);
    b = AnimationGraph_EvaluateNode(owner, second, bank, bTime, bTime - delta, flags, rate, weight);
    return Pose_Difference(owner, a, b, flags);
}

// Unmatched: two missing division hazard NOPs.
float *Graph_EventWeight(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) {
    AnimationControlBinding *control = (AnimationControlBinding *)node->parameters;
    AnimationGraphNode *child;
    float value;
    float *pose;
    if (node->childCount <= 0)
        return 0;
    child = node->children[0];
    value = (AnimationEvents_Invoke(control->event, owner) - control->minimum) / control->range;
    if (value <= 0.0f)
        value = 0.0f;
    else if (value > 1.0f)
        value = 1.0f;
    pose = AnimationGraph_EvaluateNode(owner, child, bank, current, previous, flags, rate, weight);
    return Pose_WeightOrdered(owner, pose, value, flags);
}

// Unmatched: repeat arithmetic scheduling and live span reads.
float *Graph_RandomRepeat(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) {
    RepeatBinding *settings = (RepeatBinding *)node->parameters;
    float old, random, span, a, b, period, boundarySpan;
    boundarySpan = AnimationGraph_ReadSpan(node, bank);
    if (Graph_Crosses(flags, current, previous, boundarySpan)) {
        old = *AnimationParameters_Get(bank, settings->parameter);
        if (settings->minimum < settings->maximum) {
            float *destination = AnimationParameters_Get(bank, settings->parameter);
            random = Graph_Random();
            *destination = ((settings->maximum - settings->minimum)*random + random) + settings->minimum;
        }
        else *AnimationParameters_Get(bank, settings->parameter) = settings->minimum;
        if (*AnimationParameters_Get(bank, settings->parameter) != old) {
            a = AnimationGraph_ReadSpan(node, bank) / (old + 1.0f);
            b = AnimationGraph_ReadSpan(node, bank);
            span = a*(b + 1.0f);
            current = Graph_ChangedSpan(owner, node, bank, flags, span, AnimationGraph_ReadSpan(node, bank),
                current);
            *AnimationParameters_Get(bank, node->spanBinding) = span;
        }
    }
    a = AnimationGraph_ReadSpan(node, bank);
    b = AnimationGraph_ReadSpan(node, bank);
    period = a / (b + 1.0f);
    current = AnimationTime_Wrap(current, period);
    previous = AnimationTime_Wrap(previous, period);
    return Graph_Sequence(owner, node, bank, current, previous, flags, rate, weight);
}

// Unmatched: span rescaling allocation and dispatch scheduling.
float *Graph_InverseControlScale(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float rate, float weight) {
    AnimationGraphNode *child;
    int *control;
    float span, childSpan, scaled;
    float *pose;
    if (node->childCount <= 0)
        return 0;
    control = (int *)node->parameters;
    child = node->children[0];
    if (control[2] || Graph_Crosses(flags, current, previous, AnimationGraph_ReadSpan(node, bank)))
        AnimationGraph_BindInverseControl(owner, node, bank);
    if (*(int *)child->metadata == 0) {
        childSpan = AnimationGraph_ReadSpan(child, bank);
        span = (float)(int)((childSpan - 1.0f)* *AnimationParameters_Get(bank, control[0]) + 1.0f);
    }
    else {
        childSpan = AnimationGraph_ReadSpan(child, bank);
        span = childSpan* *AnimationParameters_Get(bank, control[0]);
    }
    if (span == 0.0f)
        span = 1.0f;
    scaled = Graph_ScaleTime(owner, node, flags, AnimationGraph_ReadSpan(node, bank), span, current, rate);
    pose = AnimationGraph_ScaledChildImpl(owner, child, bank, scaled, previous, flags,
        *AnimationParameters_Get(bank, control[0]), rate);
    Graph_ChangedSpan(owner, node, bank, flags, span, AnimationGraph_ReadSpan(node, bank), scaled);
    return pose;
}

// Unmatched: software-double temporary and constant register allocation.
float *Graph_Overlay(void *owner, AnimationGraphNode *node, AnimationParameters *bank, OverlayBinding *overlay,
    unsigned int flags, float previous, float rate, float weight) {
    InstanceView *instance = (InstanceView *)owner;
    float blend = overlay->weight, complement;
    SoftDouble magnitude;
    float *first, *second;
    if (instance->flags & 0x01000000)
        blend = blend > 0.5f ? 1.0f : 0.0f;
    magnitude = SoftDouble_FromFloat(0.0f - blend);
    if (SoftDouble_Compare(magnitude, 0) < 0)
        magnitude = SoftDouble_Subtract(0, magnitude);
    if (SoftDouble_Compare(magnitude, 0x3f50624de0000000L) < 0)
        return AnimationGraph_EvaluateNode(owner, node, bank, (float)overlay->first, previous, flags, rate,
            weight);
    complement = 1.0f - blend;
    magnitude = SoftDouble_FromFloat(complement);
    if (SoftDouble_Compare(magnitude, 0) < 0)
        magnitude = SoftDouble_Subtract(0, magnitude);
    if (SoftDouble_Compare(magnitude, 0x3f50624de0000000L) < 0)
        return AnimationGraph_EvaluateNode(owner, node, bank, (float)overlay->second, previous, flags, rate,
            weight);
    first = AnimationGraph_EvaluateNode(owner, node, bank, (float)overlay->first, previous, flags, rate,
        weight*complement);
    second = AnimationGraph_EvaluateNode(owner, node, bank, (float)overlay->second, previous, flags, rate,
        weight*blend);
    if (first && second)
        return Pose_Blend(owner, first, second, flags, blend);
    return 0;
}

// Unmatched: func_0034C128, controlled blend live span reads and weight-stack lifetimes.
#endif
