#include "animation/arms/playback.hpp"
namespace ArmsAnimation {
static inline float Minimum(float a,float b){float out;asm("min.s %0,%1,%2":"=f"(out):"f"(a),"f"(b));return out;}
// Unmatched: Reset has three scalar-store scheduling differences; the best draft is in nonmatching/tu_34eae0_reset.c.
#ifndef MOD_ARMS_EVALUATE_ONLY
float Playback::ChangedSpan(float span,float old,float coordinate,AnimationGraphNode* node,AnimationParameters* bank,unsigned options) {
    if(span!=old) {
        int low=options&1;
        if(low)Accumulate(old-span);
        if(options&2){if((low^1)==0){}else goto adjust;}else if(low){adjust:coordinate=span-1.0f;}
        flags|=0x14;*Parameter(bank,node->spanBinding)=span;
    }
    return coordinate;
}
#endif
#ifndef MOD_ARMS_EVALUATE_ONLY
long Playback::Advance(f32 delta) {
    Playback* state=this;
    long result = 0;
    s32 flags;
    if (state->At<int>(0x998)) state->At<int>(0x0) &= ~1;
    flags = state->At<int>(0x0);
    if (!(flags & 0x81)) {
        if (state->At<void*>(0xc) != NULL) {
            s32 scan = -4;
            state->At<int>(0x0) = flags & ~2;
            if (!(flags & 8)) {
                f32 old = state->At<float>(0x14);
                s32 index = state->At<short>(0x1c8);
                PlaybackHistory *history;
                f32 current, previous;
                if (index == 0) index = 7; else --index;
                state->At<float>(0x14) += delta;
                history = state->history + index;
                if (!state->At<int>(0x998)) state->At<float>(0x14) = Minimum(state->At<float>(0x14), state->At<float>(0x1c) - 1.0f);
                if (history->subtract_blend == 1) {
                    current = Wrap(state->At<float>(0x14), state->At<float>(0x1c) + history->blend);
                    previous = Wrap(state->At<float>(0x18), state->At<float>(0x1c) + history->blend);
                } else {
                    current = Wrap(state->At<float>(0x14), state->At<float>(0x1c));
                    previous = Wrap(state->At<float>(0x18), state->At<float>(0x1c));
                }
                if (current < previous || state->At<float>(0x1c) <= delta ||
                    ((state->At<float>(0x1c) - 1.0f) - delta < state->At<float>(0x14) && !state->At<int>(0x998))) {
                    if (!state->At<int>(0x998)) {
                        state->At<float>(0x14) = old;
                        state->At<int>(0x0) |= 1;
                    } else state->At<int>(0x0) |= 7;
                    scan = -2;
                }
            } else state->At<int>(0x0) &= ~8;
            result = Scan(state, scan);
        } else state->At<float>(0x14) += delta;
    }
    return result;
}
#endif
#ifdef MOD_ARMS_EVALUATE_ONLY
Pose* Playback::Evaluate(Pose* optional_pose) {
    Playback* state=this;
    s32 flags, evaluation;
    f32 coordinate;
    f32 *scale;
    Pose *pose;
    gSubtraction = 0.0f;
    gAccumulation = 0.0f;
    flags = state->At<int>(0x0);
    evaluation = (flags >> 6) & 1;
    if (flags & 0x800) evaluation |= 0x80;
    if (flags & 0x1000) evaluation |= 4;
    if (state->At<float>(0x14) < state->At<float>(0x1c)) evaluation |= 0x10;
    state->At<short>(0x8) = -1;
    scale = (float*)((char*)state+0x960);
    scale[0] = 1.0f;
    scale[2] = 1.0f;
    scale[1] = 1.0f;
    state->At<int>(0x980) = state->At<int>(0x970);
    pose = RootMotion(state, state->At<void*>(0xc), state->At<void*>(0x98c), state->At<float>(0x14), state->At<float>(0x18), evaluation, state->At<short>(0x1c8));
    if (state->At<short>(0x8) == -1) state->At<short>(0x8) = 0;
    CopyIfPresent(optional_pose, pose);
    RefreshSpan(state, state->At<void*>(0xc), state->At<void*>(0x98c));
    if (state->At<float>(0x14) != state->At<float>(0x18)) state->At<float>(0x14) -= gSubtraction;
    coordinate = state->At<float>(0x14) + gAccumulation;
    state->At<float>(0x18) = coordinate;
    state->At<float>(0x14) = coordinate;
    return pose;
}
#endif
// Unmatched: EvaluateHeader combine removes the accumulator-to-argument copy; the best draft is in nonmatching/tu_34eae0_evaluate_header.c.
}
