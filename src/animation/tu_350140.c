#include "include_asm.h"
#include "ps2/prelude.h"
#include "animation/playback_state.h"
#include "animation/transition_records.h"
#include "animation/parameter_bank.h"
#include "animation/expression.h"

/* Recovered_AnimationParameterBank: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_AnimationParameterBank {
    u8 unk_0[280];
    s32 unk_118;
} Recovered_AnimationParameterBank;

#include "ps2/recovered_types.h"
extern void func_00350098(Recovered_AnimationParameterBank *);

void func_00350140(s32 *arg0) {
    s32 *var_16;
    s32 temp_4;
    s32 var_17;

    var_16 = (s32 *) (((s8 *) arg0) + 0x8C);
    var_17 = 7;
    do {
        M2C_FIELD(var_16, s32 *, -4) = 0;
        var_17 -= 1;
        M2C_FIELD(var_16, s32 *, 4) = 0;
        M2C_FIELD(var_16, f32 *, 8) = 1.0f;
        M2C_FIELD(var_16, s32 *, 0xC) = 0;
        M2C_FIELD(var_16, s32 *, 0x10) = 0;
        M2C_FIELD(var_16, s32 *, 0x18) = 0;
        M2C_FIELD(var_16, s32 *, 0x14) = 1;
        M2C_FIELD(var_16, s32 *, 0x1C) = 0;
        M2C_FIELD(var_16, s16 *, 0x20) = 0;
        temp_4 = M2C_FIELD(var_16, s32 *, 0);
        var_16 = (s32 *) (((s8 *) var_16) + 0x28);
        func_00350098((Recovered_AnimationParameterBank *) temp_4);
    } while (var_17 >= 0);
    M2C_FIELD(arg0, s16 *, 0x1C8) = 0;
}

typedef struct AnimationCollectionView AnimationCollectionView;
extern void* AnimationCollection_FindGraph(AnimationCollectionView*, int) ANIMATION_FUNCTION(003432E8);
extern int AnimationCollection_TransitionCount(AnimationCollectionView*) ANIMATION_FUNCTION(00343508);
extern int* AnimationCollection_TransitionRow(AnimationCollectionView*, int) ANIMATION_FUNCTION(003433C8);

extern void AnimationParameterBank_Clear(struct AnimationParameterBank*) ANIMATION_FUNCTION(00350098);
extern void AnimationParameterBank_Copy(struct AnimationParameterBank*, const struct AnimationParameterBank*)
    ANIMATION_FUNCTION(003500A8);
extern int AnimationCollection_HasGraph(AnimationCollectionView*, int) ANIMATION_FUNCTION(00343470);

static inline AnimationGraphNode* FindGraph(PlaybackState* state, int graph) {
    return (AnimationGraphNode*)AnimationCollection_FindGraph((AnimationCollectionView*)state->collection, graph);
}

#ifdef NON_MATCHING
static inline void RecordHistory(PlaybackState* state, const TransitionTiming* timing, float coordinate,
                                 float destinationCoordinate) {
    PlaybackHistory* history = &state->history[state->cursor];
    short next;
    history->node = state->graph;
    AnimationParameterBank_Copy((struct AnimationParameterBank*)history->bank,
                                (const struct AnimationParameterBank*)state->bank);
    history->coordinate = coordinate;
    history->span = state->span;
    if (timing) {
        *(TransitionTiming*)&history->timing_start = *timing;
        history->has_timing = 1;
    } else {
        history->has_timing = 0;
    }
    history->destination_coordinate = destinationCoordinate;
    next = state->cursor + 1;
    state->cursor = next % 8;
}

#endif

void AnimationPlayback_RecordHistory(PlaybackState*, const TransitionTiming*, float, float)
    ANIMATION_FUNCTION(003501D8);
#ifdef NON_MATCHING
// Unmatched: native timing-copy scheduling and ring-index temporaries differ.
void AnimationPlayback_RecordHistory(PlaybackState* state, const TransitionTiming* timing, float coordinate,
                                     float destinationCoordinate) {
    RecordHistory(state, timing, coordinate, destinationCoordinate);
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_350140", func_003501D8);

PlaybackHistory* AnimationPlayback_PreviousHistory(PlaybackState*, int) ANIMATION_FUNCTION(003502C0);
#ifdef NON_MATCHING
// Unmatched: native signed wrap branch and return-pointer lifetime differ.
PlaybackHistory* AnimationPlayback_PreviousHistory(PlaybackState* state, int cursor) {
    PlaybackHistory* history = 0;
    --cursor;
    if (cursor < 0) cursor += 8;
    if (cursor != state->cursor) {
        history = &state->history[cursor];
        if (!history->node || !history->has_timing) history = 0;
    }
    return history;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_350140", func_003502C0);

float AnimationPlayback_TransitionCoordinate(PlaybackState*, AnimationTransitionRecord*) ANIMATION_FUNCTION(00350308);
/* Negative coordinates use the destination span; -1 preserves the current fractional phase.
 * Zero preserves the current coordinate; positive values are stored with a one-unit bias. */
float AnimationPlayback_TransitionCoordinate(PlaybackState* state, AnimationTransitionRecord* transition) {
    float coordinate = transition->target_coordinate;
    if (coordinate < 0.0f) {
        AnimationGraphNode* graph = FindGraph(state, transition->target_graph);
        float span;
        AnimationGraph_BindPreorder(state, graph, (AnimationParameters*)state->scratch_bank);
        AnimationGraph_ResolveSpan(state, graph, (AnimationParameters*)state->scratch_bank);
        span = AnimationGraph_ReadSpan(graph, (AnimationParameters*)state->scratch_bank);
        coordinate = transition->target_coordinate;
        if (coordinate == -1.0f) {
            float fraction = state->current / state->span;
            return (fraction - (float)(int)fraction) * span;
        }
        return -coordinate * span;
    }
    if (coordinate != 0.0f) return coordinate - 1.0f;
    return state->current;
}

extern float AnimationPlayback_RefreshSpan(PlaybackState*, void*, void*) ANIMATION_FUNCTION(00351030);
void AnimationPlayback_BindGraph(PlaybackState*, int) ANIMATION_FUNCTION(00350410);
void AnimationPlayback_BindGraph(PlaybackState* state, int graphId) {
    AnimationGraphNode* graph = FindGraph(state, graphId);
    if (state->graph_hash != graphId) state->flags |= 0x20;
    state->graph_hash = graphId;
    ++state->revision;
    state->graph = graph;
    AnimationParameterBank_Clear((struct AnimationParameterBank*)state->bank);
    state->flags = (state->flags | 0x410) & ~1;
    AnimationGraph_BindPreorder(state, (AnimationGraphNode*)state->graph, (AnimationParameters*)state->bank);
    AnimationGraph_ResolveSpan(state, (AnimationGraphNode*)state->graph, (AnimationParameters*)state->bank);
    AnimationPlayback_RefreshSpan(state, state->graph, state->bank);
    state->previous_choice = -1;
}

void AnimationPlayback_ApplyTransition(PlaybackState*, AnimationTransitionRecord*, int, float)
    ANIMATION_FUNCTION(003504C8);
#ifdef NON_MATCHING
// Unmatched: native selected-coordinate and timing-pointer lifetimes differ.
void AnimationPlayback_ApplyTransition(PlaybackState* state, AnimationTransitionRecord* transition,
                                       int explicitCoordinate, float coordinate) {
    float selectedCoordinate = coordinate;
    if (!explicitCoordinate) selectedCoordinate = AnimationPlayback_TransitionCoordinate(state, transition);
    if (state->flags & 2) {
        AnimationPlayback_RecordHistory(state, &transition->timing, state->previous, selectedCoordinate);
        state->flags &= ~2;
    } else {
        AnimationPlayback_RecordHistory(state, &transition->timing, state->current, selectedCoordinate);
    }
    AnimationPlayback_BindGraph(state, transition->target_graph);
    state->previous = selectedCoordinate;
    state->current = selectedCoordinate;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_350140", func_003504C8);

void AnimationPlayback_BeginGraph(PlaybackState*, int, int, float) ANIMATION_FUNCTION(00350570);
#ifdef NON_MATCHING
// Unmatched: native specialized history copy and coordinate lifetimes differ.
void AnimationPlayback_BeginGraph(PlaybackState* state, int graph, int explicitCoordinate, float coordinate) {
    float previous;
    RecordHistory(state, 0, state->current, 0.0f);
    AnimationPlayback_BindGraph(state, graph);
    if (explicitCoordinate) state->current = coordinate;
    previous = state->current;
    state->current = 0.0f;
    state->previous = previous;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_350140", func_00350570);

int AnimationPlayback_ScanTransitions(PlaybackState*, int) ANIMATION_FUNCTION(00350650);
#ifdef NON_MATCHING
// Unmatched: native filter branch layout and loop temporary lifetimes differ.
int AnimationPlayback_ScanTransitions(PlaybackState* state, int trigger) {
    int index;
    float coordinate = AnimationTime_Wrap(state->current, state->span);
    if (state->flags & 0x200) return 0;
    for (index = 0; index < AnimationCollection_TransitionCount((AnimationCollectionView*)state->collection); ++index) {
        AnimationTransitionRecord* transition = (AnimationTransitionRecord*)AnimationCollection_TransitionRow(
            (AnimationCollectionView*)state->collection, index);
        if ((transition->source_graph == -1 || transition->source_graph == state->graph_hash) &&
            AnimationCollection_HasGraph((AnimationCollectionView*)state->collection, transition->target_graph) &&
            (transition->trigger == -4 || transition->trigger == trigger) &&
            (!transition->condition || AnimationExpression_Evaluate(transition->condition, state) != 0.0f) &&
            transition->window_start <= coordinate && coordinate <= transition->window_end) {
            AnimationPlayback_ApplyTransition(state, transition, 0, 0.0f);
            return index + 1;
        }
    }
    return 0;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_350140", func_00350650);

AnimationTransitionRecord* AnimationPlayback_FindTransition(PlaybackState*, int) ANIMATION_FUNCTION(003507C0);
AnimationTransitionRecord* AnimationPlayback_FindTransition(PlaybackState* state, int graph) {
    int index;
    for (index = 0; index < AnimationCollection_TransitionCount((AnimationCollectionView*)state->collection); ++index) {
        AnimationTransitionRecord* transition = (AnimationTransitionRecord*)AnimationCollection_TransitionRow(
            (AnimationCollectionView*)state->collection, index);
        if ((transition->source_graph == -1 || transition->source_graph == state->graph_hash) &&
            transition->target_graph == graph &&
            (!transition->condition || AnimationExpression_Evaluate(transition->condition, state) != 0.0f))
            return transition;
    }
    return 0;
}

extern AnimationTransitionRecord AnimationPlayback_DefaultTransition __asm__("D_0046C5D0");
int AnimationPlayback_TryGraph(PlaybackState*, int, int, float) ANIMATION_FUNCTION(00350890);
#ifdef NON_MATCHING
// Unmatched: native default-transition store order and temporary lifetimes differ.
int AnimationPlayback_TryGraph(PlaybackState* state, int graph, int explicitCoordinate, float coordinate) {
    int index;
    AnimationTransitionRecord* transition = 0;
    float current = AnimationTime_Wrap(state->current, state->span);
    for (index = 0; index < AnimationCollection_TransitionCount((AnimationCollectionView*)state->collection); ++index) {
        AnimationTransitionRecord* candidate = (AnimationTransitionRecord*)AnimationCollection_TransitionRow(
            (AnimationCollectionView*)state->collection, index);
        if ((candidate->source_graph == -1 || candidate->source_graph == state->graph_hash) &&
            candidate->target_graph == graph && candidate->window_start <= current &&
            current <= candidate->window_end) {
            transition = candidate;
            break;
        }
    }
    if (!transition) {
        AnimationPlayback_DefaultTransition.target_coordinate = 1.0f;
        transition = &AnimationPlayback_DefaultTransition;
        transition->timing.blend = 10.0f;
        transition->target_graph = graph;
        transition->timing.start = 0.0f;
        transition->timing.subtractBlend = 0;
        transition->timing.mode = 0;
        transition->window_start = 1.0f;
    }
    AnimationPlayback_ApplyTransition(state, transition, explicitCoordinate, coordinate);
    return 1;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_350140", func_00350890);
