#ifndef BLACK_ANIMATION_TRANSITION_RECORDS_H
#define BLACK_ANIMATION_TRANSITION_RECORDS_H
#include "animation/graph_runtime.h"

typedef struct PS2AnimationExpression PS2AnimationExpression;

/* Partial PS2 transition view. UNVERIFIED: field meanings, trigger conventions
 * and complete record extent; these accesses currently come from draft consumers.
 * Timing uses the existing graph transition view rather than a second layout. */
typedef struct AnimationTransitionRecord {
    int source_graph;
    float window_start, window_end;
    int trigger;
    PS2AnimationExpression* condition;
    int target_graph;
    float target_coordinate;
    TransitionTiming timing;
} AnimationTransitionRecord;

typedef char TransitionTargetOffset[(unsigned int)&((AnimationTransitionRecord*)0)->target_graph == 0x14 ? 1 : -1];
typedef char TransitionTimingOffset[(unsigned int)&((AnimationTransitionRecord*)0)->timing == 0x1c ? 1 : -1];
#endif
