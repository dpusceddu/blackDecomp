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


INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034B4E8);
