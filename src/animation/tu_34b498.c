#include "include_asm.h"

#include "animation/graph.h"

float AnimationTime_Wrap(float time, float span) {
    if (time > span - 1.0f)
        time -= span * (int)(time / span);
    return time;
}

float *AnimationGraph_PoseWeightedChoice(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    return AnimationGraph_EvaluateChoice(owner, node, bank, current, previous, flags, coefficient,
        node->parameters[2], weight, AnimationGraph_SelectWeightedChild, 0);
}

float *AnimationGraph_PoseFixedControl(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    return AnimationGraph_EvaluateControlled(owner, node, bank, flags, 1, current, previous,
        node->parameters[0], coefficient, weight);
}

int AnimationGraph_SelectControlRange(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    float value = AnimationEvents_Invoke(((int *)node->parameters)[1], owner);
    int count = node->childCount;
    int i;
    AnimationGraphNode **child;
    if (!count)
        return 0;
    i = 0;
    if (count > 0) {
        child = node->children;
        do {
            float *range = (float *)(*child)->metadata;
            if (range && range[0] <= value && value <= range[1])
                return i;
            ++i;
            ++child;
        } while (i < count);
    }
    return 0;
}

float *AnimationGraph_PoseScaledChild(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    if (node->childCount <= 0)
        return 0;
    return AnimationGraph_ScaledChildImpl(owner, node->children[0], bank, current, previous, flags,
        node->parameters[0], coefficient);
}

float *AnimationGraph_PoseDiscreteChild(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    if (node->childCount <= 0)
        return 0;
    return AnimationGraph_DiscreteChildImpl(owner, node->children[0], bank, current, previous, flags,
        node->parameters[0], coefficient);
}

float *AnimationGraph_EmptyPose(void) {
    return 0;
}

float *AnimationGraph_CallbackPose(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    AnimationPoseHandler callback = *(AnimationPoseHandler *)((char *)owner + 0x9c0);
    float *pose;
    if (!callback)
        pose = 0;
    else pose = callback(owner, node, bank, current, previous, flags, coefficient, weight);
    return pose;
}

float *AnimationGraph_EvaluateNode(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    ++AnimationGraph_NodeEvaluations;
    return AnimationGraph_PoseHandlers[node->opcode & 0x3f](owner, node, bank, current, previous, flags,
        coefficient, weight);
}

float AnimationGraph_ResolveOverrideSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    SpanOverride callback = *(SpanOverride *)((char *)owner + 0x9c4);
    float result;
    if (!callback)
        result = 0.0f;
    else result = callback(owner, node, bank);
    return result;
}

float AnimationGraph_ResolveClipSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    void *clip = node->children[0];
    float span;
    if (!clip)
        return 1.0f;
    span = AnimationClip_Duration(clip);
    if (!((int *)clip)[2])
        span = (float)(int)span;
    return span;
}

float AnimationGraph_ResolveScaledPair(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    if (node->childCount < 2)
        return 1.0f;
    AnimationGraph_ResolveSpan(owner, node->children[0], bank);
    return AnimationGraph_ResolveScaledSpan(owner, node->children[1], bank, node->parameters);
}

float AnimationGraph_ResolveFirstSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    if (node->childCount <= 0)
        return 1.0f;
    return AnimationGraph_ResolveSpan(owner, node->children[0], bank);
}

float AnimationGraph_ResolveMaximumSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    float maximum = 0.0f;
    signed char initial = node->childCount;
    AnimationGraphNode **child;
    if (!initial)
        return 1.0f;
    child = node->children;
    if (initial > 0) {
        int count = initial;
        do {
            float span = AnimationGraph_ResolveSpan(owner, *child, bank);
            if (maximum < span)
                maximum = span;
            --count;
            ++child;
        } while (count);
    }
    return maximum;
}

float AnimationGraph_ResolveFixedScale(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    AnimationGraphNode *child;
    float factor, span;
    if (node->childCount <= 0)
        return 1.0f;
    child = node->children[0];
    AnimationGraph_ResolveSpan(owner, child, bank);
    factor = *node->parameters;
    if (*(int *)child->metadata == 0)
        span = (float)(int)((AnimationGraph_ReadSpan(child,
        bank) - 1.0f) * factor + 1.0f);
    else span = AnimationGraph_ReadSpan(child, bank) * factor;
    if (span == 0.0f)
        span = 1.0f;
    return span;
}

float AnimationGraph_ResolveParameterScale(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) {
    AnimationGraphNode *child;
    float factor, span;
    if (node->childCount <= 0)
        return 1.0f;
    child = node->children[0];
    AnimationGraph_ResolveSpan(owner, child, bank);
    factor = *AnimationParameters_Get(bank, ((int *)node->parameters)[0]);
    if (*(int *)child->metadata == 0)
        span = (float)(int)((AnimationGraph_ReadSpan(child,
        bank) - 1.0f) * factor + 1.0f);
    else span = AnimationGraph_ReadSpan(child, bank) * factor;
    if (span == 0.0f)
        span = 1.0f;
    return span;
}

float AnimationGraph_ResolveWindowLimit(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    AnimationGraphNode *child;
    float *window;
    float limit, result;
    if (node->childCount <= 0)
        return 1.0f;
    child = node->children[0];
    AnimationGraph_ResolveSpan(owner, child, bank);
    window = node->parameters;
    limit = (window[1] - window[0]) + 1.0f;
    if (AnimationGraph_ReadSpan(child, bank) < limit)
        result = AnimationGraph_ReadSpan(child, bank);
    else result = (window[1] - window[0]) + 1.0f;
    return result;
}

float AnimationGraph_ResolveParameterBlend(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) {
    return AnimationGraph_ResolveBlendSpan(owner, node, bank, 1, *AnimationParameters_Get(bank,
        ((int *)node->parameters)[3]));
}

float AnimationGraph_ResolveFixedBlend(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    return AnimationGraph_ResolveBlendSpan(owner, node, bank, 1, node->parameters[0]);
}

float AnimationGraph_UnitSpan(void) {
    return 1.0f;
}

float AnimationGraph_ResolveAdditiveSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    float *binding = node->parameters;
    float span = AnimationGraph_ResolveSumSpan(owner, node, bank);
    return *AnimationParameters_Get(bank, ((int *)binding)[1]) * span + span;
}

float AnimationGraph_ResolveFirstPairSpan(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) {
    float span;
    if (node->childCount <= 0)
        return 1.0f;
    span = AnimationGraph_ResolveSpan(owner, node->children[0], bank);
    if (node->childCount >= 2)
        AnimationGraph_ResolveSpan(owner, node->children[1], bank);
    return span;
}

float AnimationGraph_ResolveParameterMaximum(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) {
    return AnimationGraph_ResolveBlendSpan(owner, node, bank, 0, *AnimationParameters_Get(bank,
        ((int *)node->parameters)[3]));
}

float AnimationGraph_ResolveUnitAfterChild(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) {
    AnimationGraph_ResolveFirstSpan(owner, node, bank);
    return 1.0f;
}

float AnimationGraph_ResolveSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    float span = 1.0f;
    unsigned int opcode = node->opcode & 0x3f;
    if (opcode < 26)
        span = AnimationGraph_SpanHandlers[opcode](owner, node, bank);
    if (node->spanBinding < 70)
        *AnimationParameters_Get(bank, node->spanBinding) = span;
    else node->inlineSpan = span;
    return span;
}

void AnimationGraph_BindControl(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    AnimationControlBinding *control = (AnimationControlBinding *)node->parameters;
    float value = AnimationEvents_Invoke(control->event, owner);
    *AnimationParameters_Get(bank, control->parameter) = (value - control->minimum) / control->range;
}

void AnimationGraph_BindMaximumControl(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    AnimationControlBinding *control = (AnimationControlBinding *)node->parameters;
    float value = AnimationEvents_Invoke(control->event, owner);
    *AnimationParameters_Get(bank, control->parameter) = (value - control->minimum) / control->range;
}

void AnimationGraph_BindClampedControl(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    AnimationControlBinding *control = (AnimationControlBinding *)node->parameters;
    float value = AnimationEvents_Invoke(control->event, owner);
    *AnimationParameters_Get(bank, control->parameter) = (value - control->minimum) / control->range;
    if (*AnimationParameters_Get(bank, control->parameter) < 0.0f)
        *AnimationParameters_Get(bank,
        control->parameter) = 0.0f;
    if (*AnimationParameters_Get(bank, control->parameter) > 1.0f)
        *AnimationParameters_Get(bank,
        control->parameter) = 1.0f;
}

float AnimationGraph_ReadSpan(AnimationGraphNode *node, AnimationParameters *bank) {
    int binding = node->spanBinding;
    if (binding >= 70) {
        if (bank)
            return node->inlineSpan;
        else
            return node->inlineSpan;
    }
    return *AnimationParameters_Get(bank, binding);
}

float AnimationGraph_ResolveSumSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    float sum = 0.0f;
    signed char initial = node->childCount;
    AnimationGraphNode **child;
    if (!initial)
        return 1.0f;
    child = node->children;
    if (initial > 0) {
        int count = initial;
        do {
            AnimationGraphNode *current = *child++;
            --count;
            sum += AnimationGraph_ResolveSpan(owner, current, bank);
        } while (count);
    }
    return sum;
}

void AnimationGraph_BindPreorder(void *owner, AnimationGraphNode *node, AnimationParameters *bank) {
    unsigned int opcode = node->opcode & 0x3f;
    if (opcode < 26) {
        AnimationBindHandler handler = AnimationGraph_BindHandlers[opcode];
        if (handler)
            handler(owner, node, bank);
        if (opcode) {
            int i = 0;
            if (node->childCount > 0) {
                AnimationGraphNode **child = node->children;
                do {
                    ++i;
                    AnimationGraph_BindPreorder(owner, *child, bank);
                    ++child;
                } while (i < node->childCount);
            }
        }
    }
}

#ifdef NONMATCHING

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

// Unmatched: func_0034C968 (48 bytes), scheduling: argument load order.

// Unmatched: func_0034CA18 (80 bytes), scheduling: capped-time dispatch.

float *AnimationGraph_PoseCappedTime(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    float time;
    if (node->childCount <= 0)
        return 0;
    time = current + node->parameters[0];
    if (time > node->parameters[1])
        time = node->parameters[1];
    return AnimationGraph_EvaluateNode(owner, node->children[0], bank, time, previous, flags, coefficient,
        weight);
}

// Unmatched: func_0034CA68 (128 bytes), scheduling: scale-state stores and dispatch.

float *AnimationGraph_PoseScale(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    float *scale, *pose;
    if (node->childCount <= 0)
        return 0;
    scale = node->parameters;
    ((float *)owner)[0x960 / 4] = scale[0];
    ((float *)owner)[0x964 / 4] = scale[1];
    ((float *)owner)[0x968 / 4] = scale[2];
    pose = AnimationGraph_EvaluateNode(owner, node->children[0], bank, current, previous, flags, coefficient,
        weight);
    if (pose)
        AnimationPose_Scale(pose, scale[0], scale[1], scale[2]);
    return pose;
}

// Unmatched: func_0034CAE8 (272 bytes), types: clip-event callback argument order.

// Unmatched: func_0034CC00 (544 bytes), types: clip/frame sampling context.

// Unmatched: func_0034CE20 (544 bytes), types: clip/frame sampling context.

// Unmatched: func_0034D040 (108 bytes), scheduling: weighted pose branch layout.

float *AnimationGraph_PoseWeight(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    float scale;
    float *result;
    if (node->childCount > 0) {
        scale = node->parameters[0];
        result = AnimationPose_ApplyWeight(owner, AnimationGraph_EvaluateNode(owner, node->children[0], bank,
            current, previous, flags, coefficient, weight), flags, scale);
    } else result = 0;
    return result;
}

// Unmatched: func_0034D0B0 (304 bytes), types: pose operation signatures.

// Unmatched: func_0034D1E0 (288 bytes), types: dual-child pose operation signatures.

// Unmatched: func_0034D300 (556 bytes), types: repeat state and live floating arguments.

// Unmatched: func_0034D530 (516 bytes), types: inverse-control state and live floating arguments.

// Unmatched: func_0034D738 (256 bytes), types: event and span call signatures.

// Unmatched: func_0034D838 (180 bytes), register allocation: parameter-control temporaries.

float *AnimationGraph_PoseBoundMaximum(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient, float weight) {
    float *control = node->parameters;
    AnimationGraph_BindMaximumControl(owner, node, bank);
    return AnimationGraph_EvaluateControlled(owner, node, bank, flags, 0, current, previous,
        *AnimationParameters_Get(bank, ((int *)control)[3]), coefficient, weight);
}

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

// Unmatched: func_0034E220 (264 bytes), scheduling: blend-span branch layout.

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
        if (first == second)
            return first;
        return first + (second - first)*weight;
    }
    return first > second?first:second;
}

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

#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034B4E8);
