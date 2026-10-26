#include "include_asm.h"
#include "ps2/prelude.h"

#include "animation/animation_graph_node.h"
#include "animation/animation_parameters.h"
#include "ps2/recovered_types.h"
#include "animation/graph.h"
#include "animation/graph_runtime.h"
extern f32 * func_0034BC30(s32 *, Recovered_AnimationGraphNode *, Recovered_AnimationParameters *, u32, void *, s32, f32, f32, f32, f32, f32);
extern s32 func_0034C8C8(void *, Recovered_AnimationGraphNode *, Recovered_AnimationParameters *);

f32 * func_0034C968(s32 *arg0, void *arg1, s32 arg2, s32 arg3, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg1, void **, 8);
    return func_0034BC30(arg0, (Recovered_AnimationGraphNode *) arg1, arg2, arg3, func_0034C8C8, M2C_FIELD(temp_2, s32 *, 8), fparg0, fparg1, fparg2, M2C_FIELD(temp_2, f32 *, 0xC), fparg3);
}

float *AnimationGraph_PoseCappedTime(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    float time;
    AnimationGraphNode *child;
    if (node->childCount <= 0)
        return 0;
    time = current + node->parameters[0];
    child = node->children[0];
    if (time > node->parameters[1])
        time = node->parameters[1];
    return AnimationGraph_EvaluateNode(owner, child, bank, time, previous, flags, coefficient, weight);
}
float *AnimationGraph_PoseScale(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    float *scale, *pose;
    AnimationGraphNode *child;
    if (node->childCount <= 0)
        return 0;
    scale = node->parameters;
    child = node->children[0];
    ((float *)owner)[0x960 / 4] = scale[0];
    ((float *)owner)[0x964 / 4] = scale[1];
    ((float *)owner)[0x968 / 4] = scale[2];
    pose = AnimationGraph_EvaluateNode(owner, child, bank, current, previous, flags, coefficient,
        weight);
    if (pose)
        AnimationPose_Scale(pose, scale[0], scale[1], scale[2]);
    return pose;
}
float* func_0034CAE8(void* owner, AnimationGraphNode* node, AnimationParameters* bank, float current, float previous,
                     unsigned int flags, float rate, float weight) {
    AnimationGraphNode* child;
    AnimationGraphNode* first;
    AnimationGraphNode* second;
    ClipView* clip;
    if ((flags & 0x20) || node->childCount <= 0) return 0;
    child = node->children[0];
    if (!(flags & 8) && child) {
        first = child->children[0];
        if (first) {
            second = first->children[0];
            if (second) {
                clip = (ClipView*)second->children[0];
                if (clip) Clip_Events(clip, owner, current, previous, AnimationGraph_ReadSpan(node, bank), flags);
            }
        }
    }
    return AnimationGraph_EvaluateNode(owner, child, bank, current, previous, flags, rate, weight);
}

#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034CC00);
#endif
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034CE20);
#endif
#ifdef NON_MATCHING
// Unmatched: func_0034CC00 (544 bytes), types: clip/frame sampling context.
// Unmatched: func_0034CE20 (544 bytes), types: clip/frame sampling context.
// Unmatched: func_0034D040 (108 bytes), scheduling: weighted pose branch layout.
float *AnimationGraph_PoseWeight(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    float scale;
    float *result;
    float *parameters = node->parameters;
    if (node->childCount > 0) {
        scale = parameters[0];
        result = AnimationPose_ApplyWeight(owner, AnimationGraph_EvaluateNode(owner, node->children[0], bank,
            current, previous, flags, coefficient, weight), flags, scale);
    } else result = 0;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034D040);
#endif
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034D0B0);
#endif
extern float* func_00346510(void*, float*, float*, int);
float* func_0034D1E0(void* owner, AnimationGraphNode* node, AnimationParameters* bank, float current, float previous,
                     unsigned int flags, float rate, float weight) {
    AnimationGraphNode *first, *second;
    float secondTime;
    float *a, *b;
    if (node->childCount < 2) return 0;
    second = node->children[1];
    first = node->children[0];
    secondTime = AnimationTime_Wrap(current, AnimationGraph_ReadSpan(second, bank));
    a = AnimationGraph_EvaluateNode(owner, first, bank, current, previous, flags, rate, weight);
    b = AnimationGraph_EvaluateNode(owner, second, bank, secondTime, previous, flags | 0x40, rate, weight);
    return func_00346510(owner, a, b, flags);
}
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034D300);
#endif
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034D530);
#endif
float* func_0034D738(void* owner, AnimationGraphNode* node, AnimationParameters* bank, float current, float previous,
                     unsigned int flags, float rate, float weight) {
    AnimationControlBinding* control;
    AnimationGraphNode* child;
    float span, time;
    if (node->childCount <= 0) return 0;
    control = (AnimationControlBinding*)node->parameters;
    child = node->children[0];
    /* The control binding invokes this event again when it computes the parameter. */
    AnimationEvents_Invoke(control->event, owner);
    AnimationGraph_BindClampedControl(owner, node, bank);
    span = AnimationGraph_ReadSpan(child, bank);
    time = (span - 1.0f) * *AnimationParameters_Get(bank, control->parameter);
    return AnimationGraph_EvaluateNode(owner, child, bank, time, time, flags, rate, weight);
}
#ifdef NON_MATCHING
// Unmatched: func_0034D0B0 (304 bytes), types: pose operation signatures.
// Unmatched: func_0034D300 (556 bytes), types: repeat state and live floating arguments.
// Unmatched: func_0034D530 (516 bytes), types: inverse-control state and live floating arguments.
// Unmatched: func_0034D838 (180 bytes), final call argument scheduling differs.
float *AnimationGraph_PoseBoundMaximum(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    AnimationGraph_BindMaximumControl(owner, node, bank);
    return AnimationGraph_EvaluateControlled(owner, node, bank, flags, 0, current, previous,
        *AnimationParameters_Get(bank, ((AnimationControlBinding *)node->parameters)->parameter), coefficient, weight);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034D838);
#endif
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034D9B0);
#endif
#ifdef NON_MATCHING
// Unmatched: func_0034D9B0 (584 bytes), types: transition callback and argument order.
// Unmatched: func_0034DC30 (56 bytes), scheduling: window load order.
float AnimationGraph_ResolveWindowSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    float *window = node->parameters;
    float start, end;
    float result;
    if (!node->children[0])
        result = 1.0f;
    else {
        start = window[0];
        end = window[1];
        result = (end - start) + 1.0f;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034DC30);
#endif
#ifdef NON_MATCHING
// Unmatched: func_0034DDD0 (196 bytes), register allocation: child selection loop temporaries.
float AnimationGraph_ResolveSelectedSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    int count = node->childCount;
    int *binding = (int *)node->parameters;
    AnimationGraphNode **children, *child;
    if (!count)
        return 1.0f;
    children = node->children;
    if (count > 0) {
        AnimationGraphNode **cursor = children;
        do {
            child = *cursor++;
            AnimationGraph_ResolveSpan(owner, child, bank);
            --count;
        } while (count);
    }
    return AnimationGraph_ReadSpan(children[(int)*AnimationParameters_Get(bank, binding[0])], bank);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034DDD0);
#endif
#ifdef NON_MATCHING
// Unmatched: func_0034E220 (264 bytes), second-span register allocation differs.
float AnimationGraph_ResolveBlendSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    int interpolate, float weight) {
    float first, second;
    if (node->childCount < 2)
        return 1.0f;
    first = AnimationGraph_ResolveSpan(owner, node->children[0], bank);
    second = AnimationGraph_ResolveSpan(owner, node->children[1], bank);
    if (interpolate) {
        if (weight <= 0.0f)
            return first;
        if (weight >= 1.0f)
            return second;
        if (first != second)
            return first + (second - first)*weight;
        return first;
    }
    return first > second?first:second;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_34b498_34c968", func_0034E220);
#endif
