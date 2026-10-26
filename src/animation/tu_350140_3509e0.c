#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_003504C8(s32 *, void *, s32, f32);

s32 func_003509E0(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0, f32 fparg1, f32 fparg2) {
    u8 sp[56] __attribute__((aligned(16)));

    *(s32 *)(sp + 20) = arg1;
    *(s32 *)(sp + 36) = arg2;
    *(s32 *)(sp + 0) = M2C_FIELD(arg0, s32 *, 0x10);
    *(f32 *)(sp + 8) = M2C_FIELD(arg0, f32 *, 0x1C) + 1.0f;
    *(s32 *)(sp + 12) = -3;
    *(f32 *)(sp + 28) = fparg1;
    *(f32 *)(sp + 32) = fparg2;
    *(s32 *)(sp + 40) = arg3;
    *(s32 *)(sp + 4) = 0;
    *(s32 *)(sp + 16) = 0;
    *(f32 *)(sp + 24) = fparg0;
    *(s32 *)(sp + 44) = 0;
    *(s32 *)(sp + 48) = 0;
    return func_003504C8(arg0, sp, 0, fparg0);
}

#include "animation/playback_state.h"
#include "animation/instance.h"
#include "animation/transition_records.h"

extern PlaybackHistory* AnimationPlayback_PreviousHistory(PlaybackState*, int) ANIMATION_FUNCTION(003502C0);
extern float AnimationPlayback_ChangedSpan(void*, AnimationGraphNode*, AnimationParameters*, unsigned, float, float,
                                           float) ANIMATION_FUNCTION(0034EDB8);
extern BkAnimationPoseHeaderPS2* AnimationPlayback_EvaluateMotion(PlaybackState*, AnimationGraphNode*,
                                                                  AnimationParameters*, unsigned, int, int, float,
                                                                  float, float) ANIMATION_FUNCTION(00350B30);

float Graph_Advance(TransitionTiming*, float, float, float) ANIMATION_FUNCTION(00350A50);

float AnimationPlayback_RefreshSpan(PlaybackState*, AnimationGraphNode*, AnimationParameters*)
    ANIMATION_FUNCTION(00351030);

BkAnimationPoseHeaderPS2* AnimationPlayback_RootMotion(PlaybackState*, AnimationGraphNode*, AnimationParameters*, float,
                                                       float, unsigned, int) ANIMATION_FUNCTION(00350F28);

int AnimationPlayback_IsTransitionActive(PlaybackState*, int) ANIMATION_FUNCTION(00351168);

#ifdef NON_MATCHING
// Unmatched: native input-coordinate lifetime and clamp branch layout differ.
float Graph_Advance(TransitionTiming* timing, float current, float span, float delta) {
    float result = current;
    int mode = timing->mode;
    if (mode != 2) {
        if (mode == 1) {
            result = current + delta;
        } else {
            float advanced = current + delta;
            float limit = (float)((int)(current / span) + 1) * span - 1.0f;
            result = advanced;
            if (limit <= advanced) result = limit;
        }
    }
    return result;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_350140_3509e0", func_00350A50);

float AnimationGraph_ResolveScaledSpan(void* owner, AnimationGraphNode* node, AnimationParameters* bank,
                                       float* parameters) {
    const TransitionTiming* timing = (const TransitionTiming*)parameters;
    float span = AnimationGraph_ResolveSpan(owner, node, bank);
    if (timing->subtractBlend == 1) return span + timing->start + timing->blend;
    if (!(span < timing->blend)) return span + timing->start;
    return timing->blend + timing->start;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_350140_3509e0", func_00350B30);

#ifdef NON_MATCHING
// Unmatched: native final argument scheduling differs.
BkAnimationPoseHeaderPS2* AnimationPlayback_RootMotion(PlaybackState* state, AnimationGraphNode* node,
                                                       AnimationParameters* bank, float current, float previous,
                                                       unsigned flags, int historyCursor) {
    if (node->childCount <= 0 && (node->opcode & 0x80)) return 0;
    if (state->flags & 4) {
        float previousSpan = state->span;
        state->flags = (state->flags & ~4) | 0x10;
        AnimationPlayback_RefreshSpan(state, node, bank);
        current = AnimationPlayback_ChangedSpan(state, node, bank, flags, state->span, previousSpan, current);
    }
    return AnimationPlayback_EvaluateMotion(state, node, bank, flags, historyCursor, 0, current, previous, state->span);
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_350140_3509e0", func_00350F28);

#ifdef NON_MATCHING
// Unmatched: four native NOPs around floating-point divisions are absent.
float AnimationPlayback_RefreshSpan(PlaybackState* state, AnimationGraphNode* node, AnimationParameters* bank) {
    if ((node->opcode & 0x80) && node->childCount <= 0) {
        state->span = 1.0f;
    } else if (state->flags & 0x10) {
        float previousSpan = state->span;
        float span = AnimationGraph_ResolveSpan(state, node, bank);
        if (span != previousSpan) {
            float current = state->current;
            float scale = span / previousSpan;
            state->current = current + (span - previousSpan) * (float)(int)(current / state->span);
            if (!(state->flags & 0x400)) {
                PlaybackHistory* history = AnimationPlayback_PreviousHistory(state, state->cursor);
                if (history) {
                    history->destination_coordinate *= scale;
                    history->timing_start *= scale;
                    history->blend *= scale;
                }
            }
            state->flags &= ~0x400;
        }
        state->span = span;
        state->flags &= ~0x10;
    }
    return state->span;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_350140_3509e0", func_00351030);

int AnimationPlayback_IsTransitionActive(PlaybackState* state, int cursor) {
    PlaybackHistory* history = AnimationPlayback_PreviousHistory(state, cursor);
    if (!history) return 0;
    if (!history->has_timing) return 0;
    if ((state->current - history->destination_coordinate) < history->timing_start + history->blend) return 1;
    return 0;
}
