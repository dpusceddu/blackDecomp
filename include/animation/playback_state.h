#ifndef BLACK_ANIMATION_PLAYBACK_STATE_H
#define BLACK_ANIMATION_PLAYBACK_STATE_H
#include "ps2/prelude.h"

/* Inferred playback names; fields follow the USA PS2 accesses. */
typedef struct PlaybackHistory {
    void *node;
    void *bank;
    u8 unknown_08[12];
    f32 blend;
    s32 mode, subtract_blend;
    u8 unknown_20[8];
} PlaybackHistory;
typedef struct PlaybackState {
    s32 flags;
    void *collection;
    s16 skeleton;
    u8 unknown_0a[2];
    void *graph;
    s32 graph_hash;
    f32 current, previous, span;
    u8 unknown_20[0x1c];
    f32 root_rotation_w;
    f32 translation[4];
    u8 unknown_50[0x34];
    void *owner;
    PlaybackHistory history[8];
    s16 cursor;
    u8 unknown_1ca[0x786];
    s32 unknown_950;
    u8 unknown_954[12];
    f32 scale[3];
    s32 unknown_96c, revision;
    u8 unknown_974[12];
    s32 evaluated_revision;
    void *selected_clip, *scratch_bank, *bank;
    s32 unknown_990;
    void *blend_weights;
    s32 evaluation_flags;
    u8 unknown_99c[0x18];
    s32 previous_choice;
    f32 previous_coordinate;
    u8 unknown_9bc[4];
    void *pose_handler, *span_handler;
    f32 frame_scale;
} PlaybackState;
typedef struct PlaybackAllocationInit {
    s32 count, flags, alignment;
#ifdef __cplusplus
    PlaybackAllocationInit() : count(0), flags(0), alignment(0) {}
#endif
} PlaybackAllocationInit;
typedef struct PlaybackAllocatorTable {
    u8 unknown_00[8];
    s16 allocate_adjust, unknown_0a;
#ifdef __cplusplus
    void *(*allocate)(void *, s32, const PlaybackAllocationInit &);
#else
    void *(*allocate)(void *, s32, PlaybackAllocationInit *);
#endif
    s16 free_adjust, unknown_12;
    void (*free)(void *, void *, s32);
} PlaybackAllocatorTable;
typedef struct PlaybackAllocator { PlaybackAllocatorTable *vtable; } PlaybackAllocator;
typedef char PlaybackCursorOffset[(u32)&((PlaybackState *)0)->cursor == 0x1c8 ? 1 : -1];
typedef char PlaybackBankOffset[(u32)&((PlaybackState *)0)->bank == 0x98c ? 1 : -1];
typedef char PlaybackHandlerOffset[(u32)&((PlaybackState *)0)->pose_handler == 0x9c0 ? 1 : -1];
#endif
