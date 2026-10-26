#ifndef GAME_CAMERA_SELECTION_POOL_H
#define GAME_CAMERA_SELECTION_POOL_H
#include "ps2/prelude.h"

/* Partial native views; the original class names and full member size are unknown. */
typedef struct Recovered_SelectionPool Recovered_SelectionPool;
typedef struct {
    u8 unk_00[0xA0];
    s128 position;
    u8 unk_B0[0x1A0];
    Recovered_SelectionPool* pool;
    u8 unk_254[0xA0];
    f32 lastUse;
    u8 unk_2F8[0xC];
    f32 distance;
    u8 unk_308[0x9C];
    s32 active; // UNVERIFIED: selector remains a draft.
} Recovered_SelectionMember;

struct Recovered_SelectionPool {
    s32 flags;
    s32 capacity;
    s32 count;
    Recovered_SelectionMember** members;
};

typedef char SelectionPoolWidth[sizeof(Recovered_SelectionPool) == 0x10 ? 1 : -1];
typedef char SelectionMemberPoolOffset[(u32) & ((Recovered_SelectionMember*)0)->pool == 0x250 ? 1 : -1];
typedef char SelectionMemberTimeOffset[(u32) & ((Recovered_SelectionMember*)0)->lastUse == 0x2F4 ? 1 : -1];
typedef char SelectionMemberDistanceOffset[(u32) & ((Recovered_SelectionMember*)0)->distance == 0x304 ? 1 : -1];
s32 SelectionPool_Clear(Recovered_SelectionPool* self);
s32 SelectionPool_Add(Recovered_SelectionPool* self, Recovered_SelectionMember* member);
void SelectionPool_Remove(Recovered_SelectionPool* self, Recovered_SelectionMember* member);
Recovered_SelectionMember* SelectionPool_First(Recovered_SelectionPool* self);
f32 SelectionPool_Score(Recovered_SelectionPool* self, Recovered_SelectionMember* member);

#endif
