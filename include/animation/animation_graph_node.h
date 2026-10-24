#ifndef BLACK_ANIMATION_ANIMATION_GRAPH_NODE_H
#define BLACK_ANIMATION_ANIMATION_GRAPH_NODE_H
#include "ps2/prelude.h"

/* Recovered_AnimationGraphNode: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_AnimationGraphNode {
    u8 unk_0;
    s8 unk_1;
    s16 unk_2;
    f32 unk_4;
    void * unk_8;
    u8 unk_C[4];
    void * unk_10;
    void * unk_14;
    void * unk_18;
    void * unk_1C;
    void * unk_20;
    void * unk_24;
    void * unk_28;
    void * unk_2C;
    s32 unk_30;
} Recovered_AnimationGraphNode;
#endif
