#ifndef BLACK_ANIMATION_GRAPH_H
#define BLACK_ANIMATION_GRAPH_H

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
typedef float (*AnimationSpanHandler)(void *, AnimationGraphNode *, AnimationParameters *);
extern unsigned int AnimationGraph_NodeEvaluations __asm__("D_003D339C");
extern AnimationPoseHandler AnimationGraph_PoseHandlers[] __asm__("D_003D33A0");
extern float *AnimationParameters_Get(AnimationParameters *, int) __asm__("func_003500E0") __attribute__((section(".text.func_003500E0")));
extern float AnimationGraph_ResolveSpan(void *, AnimationGraphNode *, AnimationParameters *) __asm__("func_0034E530") __attribute__((section(".text.func_0034E530")));
extern float AnimationGraph_ResolveFirstSpan(void *, AnimationGraphNode *, AnimationParameters *) __asm__("func_0034DE98") __attribute__((section(".text.func_0034DE98")));
extern float AnimationGraph_ResolveSumSpan(void *, AnimationGraphNode *, AnimationParameters *) __asm__("func_0034DD38") __attribute__((section(".text.func_0034DD38")));
extern float AnimationGraph_ResolveBlendSpan(void *, AnimationGraphNode *, AnimationParameters *, int, float) __asm__("func_0034E220") __attribute__((section(".text.func_0034E220")));
extern float *AnimationGraph_EvaluateNode(void *, AnimationGraphNode *, AnimationParameters *, float, float, unsigned int, float, float) __asm__("func_0034D960") __attribute__((section(".text.func_0034D960")));
#endif
