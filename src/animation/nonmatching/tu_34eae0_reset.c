#ifdef NONMATCHING
// Unmatched: member-store scheduling differs.
#include "animation/playback_state.h"
void func_0034EAE0(PlaybackState *state, void *collection, void *owner) {
    f32 *scale = state->scale;
    state->flags = 8;
    state->collection = collection;
    state->skeleton = -1;
    state->owner = owner;
    state->previous_choice = -1;
    state->previous_coordinate = -1.0f;
    state->graph = NULL;
    state->graph_hash = -1;
    state->cursor = -1;
    state->current = 0.0f;
    state->previous = -1.0f;
    state->span = 1.0f;
    state->unknown_950 = 0;
    state->evaluation_flags = 0;
    scale[0] = 1.0f;
    scale[2] = 1.0f;
    scale[1] = 1.0f;
    state->root_rotation_w = 1.0f;
    state->bank = NULL;
    state->scratch_bank = NULL;
    state->blend_weights = NULL;
    state->revision = 0;
    state->evaluated_revision = 0;
    state->pose_handler = NULL;
    state->span_handler = NULL;
    state->frame_scale = 1.0f;
    state->translation[0] = 0.0f;
    state->translation[1] = 0.0f;
    state->translation[2] = 0.0f;
    state->translation[3] = 1.0f;
    *(s32 *)((u8 *)state+0x30) = 0;
    *(s32 *)((u8 *)state+0x34) = 0;
    *(s32 *)((u8 *)state+0x38) = 0;
}
#endif
