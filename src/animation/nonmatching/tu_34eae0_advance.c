#ifdef NONMATCHING
// Unmatched: float copy and history-index scheduling differ; full body score 6.
#include "animation/playback_state.h"
extern f32 func_0034B498(f32, f32);
extern s32 func_00350650(PlaybackState *, s32);
static __inline__ f32 Playback_Min(f32 left, f32 right) {
    f32 result;
    __asm__("min.s %0,%1,%2" : "=f"(result) : "f"(left), "f"(right));
    return result;
}
s32 func_0034EE90(PlaybackState *state, f32 delta) {
    s32 result = 0;
    s32 flags;
    if (state->evaluation_flags) state->flags &= ~1;
    flags = state->flags;
    if (!(flags & 0x81)) {
        if (state->graph != NULL) {
            s32 scan = -4;
            state->flags = flags & ~2;
            if (!(flags & 8)) {
                f32 old = state->current;
                s32 index = state->cursor;
                PlaybackHistory *history;
                f32 current, previous;
                if (index == 0) index = 7; else --index;
                state->current = old + delta;
                history = state->history + index;
                if (!state->evaluation_flags) state->current = Playback_Min(state->current, state->span - 1.0f);
                if (history->subtract_blend == 1) {
                    current = func_0034B498(state->current, state->span + history->blend);
                    previous = func_0034B498(state->previous, state->span + history->blend);
                } else {
                    current = func_0034B498(state->current, state->span);
                    previous = func_0034B498(state->previous, state->span);
                }
                if (current < previous || state->span <= delta ||
                    ((state->span - 1.0f) - delta < state->current && !state->evaluation_flags)) {
                    if (!state->evaluation_flags) {
                        state->current = old;
                        state->flags |= 1;
                    } else state->flags |= 7;
                    scan = -2;
                }
            } else state->flags &= ~8;
            result = func_00350650(state, scan);
        } else state->current += delta;
    }
    return result;
}
#endif
