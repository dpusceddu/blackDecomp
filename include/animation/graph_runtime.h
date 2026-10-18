#ifndef BLACK_ANIMATION_GRAPH_RUNTIME_H
#define BLACK_ANIMATION_GRAPH_RUNTIME_H
#include "animation/graph.h"

/* Names and payload views are inferred. Only offsets used by matching functions are verified. */

typedef struct ClipView {
    unsigned char unknown00[8];
    int flags;
    unsigned char unknown0c[8];
    int sampleCount;
} ClipView;
typedef struct InstanceView {
    unsigned int flags;
    unsigned char unknown04[4];
    short skeletonIndex;
    unsigned char unknown0a[0x984-0xa];
    ClipView *selectedClip;
    unsigned char unknown988[0x994-0x988];
    void *blendWeights;
    unsigned int evaluationFlags;
    unsigned char unknown99c[0x9b4-0x99c];
    int previousChoice;
    float previousCoordinate;
} InstanceView;
typedef struct SamplingContext {
    void *owner;
    ClipView *clip;
} SamplingContext;
typedef struct TransitionTiming {
    float start, blend;
    int mode, subtractBlend;
} TransitionTiming;
typedef struct ChoiceBinding {
    int parameter, excludePrevious;
} ChoiceBinding;
typedef struct RepeatBinding {
    int unused, parameter;
    float minimum, maximum;
} RepeatBinding;
typedef struct OverlayBinding {
    int first, second;
    float weight;
} OverlayBinding;
extern SamplingContext *SamplingContext_Init(SamplingContext *, void *, ClipView *) __asm__("func_0034F420");
extern int Clip_GetSkeleton(ClipView *) __asm__("func_003487E0");
extern int Clip_GetSampleCount(ClipView *) __asm__("func_0034B5A8");
extern float *SamplingContext_Header(SamplingContext *, float, float, float, int, float,
    unsigned int) __asm__("func_0034F668");
extern float *SamplingContext_Whole(SamplingContext *, float, float, float, int, float,
    unsigned int) __asm__("func_0034F430");
extern void Clip_Events(ClipView *, void *, float, float, float, unsigned int) __asm__("func_003487F0");
extern int Graph_Crosses(unsigned int, float, float, float) __asm__("func_0034B4E8");
extern float Graph_Advance(TransitionTiming *, float, float, float) __asm__("func_00350A50");
extern float *Pose_Blend(void *, float *, float *, unsigned int, float) __asm__("func_00346230");
extern float *Pose_Compose(void *, float *, float *, unsigned int) __asm__("func_00346668");
extern float *Pose_Difference(void *, float *, float *, unsigned int) __asm__("func_00346940");
extern float Graph_ChangedSpan(void *, AnimationGraphNode *, AnimationParameters *, unsigned int, float, float,
    float) __asm__("func_0034EDB8");
extern float Graph_ScaleTime(void *, AnimationGraphNode *, unsigned int, float, float, float,
    float) __asm__("func_0034C0C8");
extern float Graph_Random(void) __asm__("func_00351A08");
extern void BlendWeights_Push(void *, float) __asm__("func_00351AE0");
extern void BlendWeights_Pop(void *) __asm__("func_00351AD0");

extern float *Graph_Sequence(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) __asm__("func_0034B910");

/* The software-double helper ABI carries binary64 bits in one 64-bit GPR. */
typedef long SoftDouble;
extern SoftDouble SoftDouble_FromFloat(float) __asm__("func_00291F58");
extern int SoftDouble_Compare(SoftDouble, SoftDouble) __asm__("func_002919F8");
extern SoftDouble SoftDouble_Subtract(SoftDouble, SoftDouble) __asm__("func_00291468");

extern float *Pose_WeightOrdered(void *, float *, float, unsigned int) __asm__("func_00346CB0");
float *Graph_SampleClip(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) ANIMATION_FUNCTION(0034B5B0);
float *Graph_TimedTransition(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) ANIMATION_FUNCTION(0034B6E0);
float *Graph_Sequence(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) ANIMATION_FUNCTION(0034B910);
int Graph_ChooseWeighted(void *owner, AnimationGraphNode *node,
    AnimationParameters *bank) ANIMATION_FUNCTION(0034BA50);
float *Graph_Choice(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float duration, float weight,
    AnimationChildChooser chooser, int forceChoice) ANIMATION_FUNCTION(0034BC30);
float *Graph_ComposedLayers(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) ANIMATION_FUNCTION(0034CC00);
float *Graph_DifferenceLayers(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) ANIMATION_FUNCTION(0034CE20);
float *Graph_EventWeight(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) ANIMATION_FUNCTION(0034D0B0);
float *Graph_RandomRepeat(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) ANIMATION_FUNCTION(0034D300);
float *Graph_InverseControlScale(void *owner, AnimationGraphNode *node, AnimationParameters *bank,
    float current, float previous, unsigned int flags, float rate, float weight) ANIMATION_FUNCTION(0034D530);
float *Graph_Overlay(void *owner, AnimationGraphNode *node, AnimationParameters *bank, OverlayBinding *overlay,
    unsigned int flags, float previous, float rate, float weight) ANIMATION_FUNCTION(0034D9B0);
float *Graph_WindowClip(void *owner, AnimationGraphNode *node, AnimationParameters *bank, float current,
    float previous, unsigned int flags, float rate, float weight) ANIMATION_FUNCTION(0034E5C0);

#endif
