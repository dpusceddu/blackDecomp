#ifndef BLACK_ANIMATION_GRAPH_H
#define BLACK_ANIMATION_GRAPH_H

#define ANIMATION_FUNCTION(address) \
    __asm__("func_" #address) __attribute__((section(".text.func_" #address)))

/* PS2 graph layout: offsets are checked against the graph dispatch and span code. */
typedef struct AnimationGraphNode AnimationGraphNode;
typedef struct AnimationParameters AnimationParameters;
struct AnimationGraphNode {
    unsigned char opcode;
    signed char childCount;
    short spanBinding;
    float inlineSpan;
    float *parameters;
    void *metadata;
    AnimationGraphNode *children[1];
};
typedef float *(*AnimationPoseHandler)(void *, AnimationGraphNode *, AnimationParameters *,
                                      float, float, unsigned int, float, float);
typedef int (*AnimationChildChooser)(void *, AnimationGraphNode *, AnimationParameters *);
typedef float (*AnimationSpanHandler)(void *, AnimationGraphNode *, AnimationParameters *);
extern unsigned int AnimationGraph_NodeEvaluations __asm__("D_003D339C");
extern AnimationPoseHandler AnimationGraph_PoseHandlers[] __asm__("D_003D33A0");
extern float *AnimationParameters_Get(AnimationParameters *, int) ANIMATION_FUNCTION(003500E0);
extern float AnimationGraph_ResolveSpan(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034E530);
extern float AnimationGraph_ResolveFirstSpan(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034DE98);
extern float AnimationGraph_ResolveSumSpan(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034DD38);
extern float AnimationGraph_ResolveBlendSpan(void *, AnimationGraphNode *, AnimationParameters *, int,
    float) ANIMATION_FUNCTION(0034E220);
extern float *AnimationGraph_EvaluateNode(void *, AnimationGraphNode *, AnimationParameters *, float, float,
    unsigned int, float, float) ANIMATION_FUNCTION(0034D960);

float AnimationTime_Wrap(float time, float span) ANIMATION_FUNCTION(0034B498);
extern float *AnimationGraph_EvaluateChoice(void *, AnimationGraphNode *, AnimationParameters *, float,
    float, unsigned int, float, float, float, AnimationChildChooser, int) ANIMATION_FUNCTION(0034BC30);
extern int AnimationGraph_SelectWeightedChild(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034BA50);
float *AnimationGraph_PoseWeightedChoice(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(0034BFB8);
extern float *AnimationGraph_EvaluateControlled(void *, AnimationGraphNode *, AnimationParameters *,
    unsigned int, int, float, float, float, float, float) ANIMATION_FUNCTION(0034C128);
float *AnimationGraph_PoseFixedControl(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(0034C898);
extern float AnimationEvents_Invoke(int, void *) ANIMATION_FUNCTION(00348A38);
int AnimationGraph_SelectControlRange(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034C8C8);
extern float *AnimationGraph_ScaledChildImpl(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(00347238);
float *AnimationGraph_PoseScaledChild(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(0034C998);
extern float *AnimationGraph_DiscreteChildImpl(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank, float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(00347280);
float *AnimationGraph_PoseDiscreteChild(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(0034C9D8);
float *AnimationGraph_EmptyPose(void) ANIMATION_FUNCTION(0034CBF8);
float *AnimationGraph_CallbackPose(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(0034D8F0);
typedef float (*SpanOverride)(void *, AnimationGraphNode *, AnimationParameters *);
float AnimationGraph_ResolveOverrideSpan(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034DBF8);
extern float AnimationClip_Duration(void *) ANIMATION_FUNCTION(003487D0);
float AnimationGraph_ResolveClipSpan(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034DC68);
extern float AnimationGraph_ReadSpan(AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034EAA0);
extern float AnimationGraph_ResolveScaledSpan(void *, AnimationGraphNode *, AnimationParameters *,
    float *) ANIMATION_FUNCTION(00350AC8);
float AnimationGraph_ResolveScaledPair(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034DCC8);
float AnimationGraph_ResolveMaximumSpan(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034DED0);
float AnimationGraph_ResolveFixedScale(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034DF70);
float AnimationGraph_ResolveParameterScale(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034E060);
float AnimationGraph_ResolveWindowLimit(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034E158);
float AnimationGraph_ResolveParameterBlend(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034E328);
float AnimationGraph_ResolveFixedBlend(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034E388);
float AnimationGraph_UnitSpan(void) ANIMATION_FUNCTION(0034E3B0);
float AnimationGraph_ResolveAdditiveSpan(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034E3C0);
float AnimationGraph_ResolveFirstPairSpan(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034E418);
float AnimationGraph_ResolveParameterMaximum(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034E4A8);
float AnimationGraph_ResolveUnitAfterChild(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034E508);
extern AnimationSpanHandler AnimationGraph_SpanHandlers[] __asm__("D_003D3408");
typedef struct AnimationControlBinding {
    int event;
    float minimum;
    float range;
    int parameter;
} AnimationControlBinding;
void AnimationGraph_BindControl(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034E758);
void AnimationGraph_BindMaximumControl(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034E7C0);
void AnimationGraph_BindClampedControl(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034E908);

typedef void (*AnimationBindHandler)(void *, AnimationGraphNode *, AnimationParameters *);
extern AnimationBindHandler AnimationGraph_BindHandlers[] __asm__("D_003D3470");
void AnimationGraph_BindPreorder(void *, AnimationGraphNode *,
    AnimationParameters *) ANIMATION_FUNCTION(0034E9E0);

float *AnimationGraph_PoseBoundControl(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(0034C7D8);
float *AnimationGraph_PoseCappedTime(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(0034CA18);
extern void AnimationPose_Scale(float *, float, float, float) ANIMATION_FUNCTION(00343BC0);
float *AnimationGraph_PoseScale(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(0034CA68);
extern float *AnimationPose_ApplyWeight(void *, float *, unsigned int, float) ANIMATION_FUNCTION(00346CB0);
float *AnimationGraph_PoseWeight(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(0034D040);

float *AnimationGraph_PoseBoundMaximum(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float coefficient,
    float weight) ANIMATION_FUNCTION(0034D838);
float AnimationGraph_ResolveWindowSpan(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034DC30);

float AnimationGraph_ResolveSelectedSpan(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034DDD0);

void AnimationGraph_BindInverseControl(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034E828);

#endif
