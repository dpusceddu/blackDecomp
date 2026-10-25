#include "animation/views/playback.hpp"
namespace AnimationViews {
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
// Unmatched: EvaluateHeader combine removes the accumulator-to-argument copy.
}
