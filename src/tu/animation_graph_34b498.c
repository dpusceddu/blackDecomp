#include "animation/graph.h"

float AnimationTime_Wrap(float time, float span) __asm__("func_0034B498") __attribute__((section(".text.func_0034B498")));

float AnimationTime_Wrap(float time, float span)  {
    if (time>span-1.0f) time-=span*(int)(time/span);
    return time;
}

extern float *AnimationGraph_EvaluateBlend(void *, AnimationGraphNode *, AnimationParameters *, float, float, unsigned int, float, float, float, AnimationPoseHandler, int) __asm__("func_0034BC30") __attribute__((section(".text.func_0034BC30")));

extern float *AnimationGraph_PoseWeighted(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient, float weight) __asm__("func_0034BA50") __attribute__((section(".text.func_0034BA50")));

float *AnimationGraph_PoseBlend(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient, float weight) __asm__("func_0034BFB8") __attribute__((section(".text.func_0034BFB8")));

float *AnimationGraph_PoseBlend(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient, float weight)  {
    return AnimationGraph_EvaluateBlend(owner, node, bank, current, previous, flags, coefficient, node->parameters[2], weight, AnimationGraph_PoseWeighted, 0);
}

extern float *AnimationGraph_ScaledChildImpl(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient, float weight) __asm__("func_00347238") __attribute__((section(".text.func_00347238")));

float *AnimationGraph_PoseScaledChild(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient, float weight) __asm__("func_0034C998") __attribute__((section(".text.func_0034C998")));

float *AnimationGraph_PoseScaledChild(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient, float weight)  {
    if(node->childCount<=0) return 0;
    return AnimationGraph_ScaledChildImpl(owner, node->children[0], bank, current, previous, flags, node->parameters[0], coefficient);
}

extern float *AnimationGraph_DiscreteChildImpl(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient, float weight) __asm__("func_00347280") __attribute__((section(".text.func_00347280")));

float *AnimationGraph_PoseDiscreteChild(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient, float weight) __asm__("func_0034C9D8") __attribute__((section(".text.func_0034C9D8")));

float *AnimationGraph_PoseDiscreteChild(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient, float weight)  {
    if(node->childCount<=0) return 0;
    return AnimationGraph_DiscreteChildImpl(owner, node->children[0], bank, current, previous, flags, node->parameters[0], coefficient);
}

float *AnimationGraph_EvaluateNode(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient, float weight)  {
    ++AnimationGraph_NodeEvaluations;
    return AnimationGraph_PoseHandlers[node->opcode&0x3f](owner, node, bank, current, previous, flags, coefficient, weight);
}

typedef float (*SpanOverride)(void *, AnimationGraphNode *, AnimationParameters *);

float AnimationGraph_ResolveOverrideSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) __asm__("func_0034DBF8") __attribute__((section(".text.func_0034DBF8")));

float AnimationGraph_ResolveOverrideSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank)  {
    SpanOverride callback = *(SpanOverride *)((char *)owner+0x9c4);
    float result;
    if (!callback) result = 0.0f;
    else result = callback(owner, node, bank);
    return result;
}

extern float AnimationClip_Duration(void *) __asm__("func_003487D0") __attribute__((section(".text.func_003487D0")));

float AnimationGraph_ResolveClipSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) __asm__("func_0034DC68") __attribute__((section(".text.func_0034DC68")));

float AnimationGraph_ResolveClipSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank)  {
    void *clip = node->children[0];
    float span;
    if(!clip)return 1.0f;
    span = AnimationClip_Duration(clip);
    if(!((int *)clip)[2])span = (float)(int)span;
    return span;
}

extern float AnimationGraph_ReadSpan(AnimationGraphNode *, AnimationParameters *) __asm__("func_0034EAA0") __attribute__((section(".text.func_0034EAA0")));

extern float AnimationGraph_ResolveScaledSpan(void *, AnimationGraphNode *, AnimationParameters *, float *) __asm__("func_00350AC8") __attribute__((section(".text.func_00350AC8")));

float AnimationGraph_ResolveScaledPair(void *owner, AnimationGraphNode *node, AnimationParameters *bank) __asm__("func_0034DCC8") __attribute__((section(".text.func_0034DCC8")));

float AnimationGraph_ResolveScaledPair(void *owner, AnimationGraphNode *node, AnimationParameters *bank)  {
    if(node->childCount<2) return 1.0f;
    AnimationGraph_ResolveSpan(owner, node->children[0], bank);
    return AnimationGraph_ResolveScaledSpan(owner, node->children[1], bank, node->parameters);
}

float AnimationGraph_ResolveFirstSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank)  {
    if (node->childCount<=0) return 1.0f;
    return AnimationGraph_ResolveSpan(owner, node->children[0], bank);
}

extern float AnimationGraph_ReadSpan(AnimationGraphNode *, AnimationParameters *) __asm__("func_0034EAA0") __attribute__((section(".text.func_0034EAA0")));

float AnimationGraph_ResolveFixedScale(void *owner, AnimationGraphNode *node, AnimationParameters *bank) __asm__("func_0034DF70") __attribute__((section(".text.func_0034DF70")));

float AnimationGraph_ResolveFixedScale(void *owner, AnimationGraphNode *node, AnimationParameters *bank)  {
    AnimationGraphNode *child;
    float factor, span;
    if(node->childCount<=0)return 1.0f;
    child = node->children[0];
    AnimationGraph_ResolveSpan(owner, child, bank);
    factor = *node->parameters;
    if(*(int *)child->metadata==0)span = (float)(int)((AnimationGraph_ReadSpan(child, bank)-1.0f)*factor+1.0f);
    else span = AnimationGraph_ReadSpan(child, bank)*factor;
    if(span==0.0f)span = 1.0f;
    return span;
}

extern float AnimationGraph_ReadSpan(AnimationGraphNode *, AnimationParameters *) __asm__("func_0034EAA0") __attribute__((section(".text.func_0034EAA0")));

float AnimationGraph_ResolveParameterScale(void *owner, AnimationGraphNode *node, AnimationParameters *bank) __asm__("func_0034E060") __attribute__((section(".text.func_0034E060")));

float AnimationGraph_ResolveParameterScale(void *owner, AnimationGraphNode *node, AnimationParameters *bank)  {
    AnimationGraphNode *child;
    float factor, span;
    if(node->childCount<=0)return 1.0f;
    child = node->children[0];
    AnimationGraph_ResolveSpan(owner, child, bank);
    factor = *AnimationParameters_Get(bank, ((int *)node->parameters)[0]);
    if(*(int *)child->metadata==0)span = (float)(int)((AnimationGraph_ReadSpan(child, bank)-1.0f)*factor+1.0f);
    else span = AnimationGraph_ReadSpan(child, bank)*factor;
    if(span==0.0f)span = 1.0f;
    return span;
}

void AnimationGraph_BindFixed(void *owner, AnimationGraphNode *node, AnimationParameters *bank) __asm__("func_0034E388") __attribute__((section(".text.func_0034E388")));

void AnimationGraph_BindFixed(void *owner, AnimationGraphNode *node, AnimationParameters *bank)  {
    AnimationGraph_ResolveBlendSpan(owner, node, bank, 1, node->parameters[0]);
}

float AnimationGraph_ResolveAdditiveSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank) __asm__("func_0034E3C0") __attribute__((section(".text.func_0034E3C0")));

float AnimationGraph_ResolveAdditiveSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank)  {
    float *binding = node->parameters;
    float span = AnimationGraph_ResolveSumSpan(owner, node, bank);
    return *AnimationParameters_Get(bank, ((int *)binding)[1])*span+span;
}

extern AnimationSpanHandler AnimationGraph_SpanHandlers[] __asm__("D_003D3408");

float AnimationGraph_ResolveSpan(void *owner, AnimationGraphNode *node, AnimationParameters *bank)  {
    float span = 1.0f;
    unsigned int opcode = node->opcode&0x3f;
    if(opcode<26) span = AnimationGraph_SpanHandlers[opcode](owner, node, bank);
    if(node->spanBinding<70) *AnimationParameters_Get(bank, node->spanBinding) = span;
    else node->inlineSpan = span;
    return span;
}
