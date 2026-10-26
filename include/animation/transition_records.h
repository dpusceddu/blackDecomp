#ifndef BLACK_ANIMATION_TRANSITION_RECORDS_H
#define BLACK_ANIMATION_TRANSITION_RECORDS_H
#include "animation/graph_runtime.h"

struct PS2AnimationExpression;

/* Partial PS2 transition view. Exact lookup and coordinate consumers confirm
 * the source graph, condition, target graph and target coordinate accesses.
 * UNVERIFIED: window/trigger conventions, timing roles and complete record extent.
 * Timing uses the existing graph transition view rather than a second layout. */
typedef struct AnimationTransitionRecord {
    int source_graph;
    float window_start, window_end;
    int trigger;
    struct PS2AnimationExpression* condition;
    int target_graph;
    float target_coordinate;
    TransitionTiming timing;
} AnimationTransitionRecord;

typedef char TransitionTargetOffset[(unsigned int)&((AnimationTransitionRecord*)0)->target_graph == 0x14 ? 1 : -1];
typedef char TransitionTimingOffset[(unsigned int)&((AnimationTransitionRecord*)0)->timing == 0x1c ? 1 : -1];
#endif
