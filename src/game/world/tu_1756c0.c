#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

extern void func_00170740(PS2LiveCollision* collision);
extern void func_00175EF8(PS2PendingCollision* pending);
extern PS2GameObjectRecord* func_00129160(PS2GameObjectManager* manager, u64 name);
extern void func_00272488(u64 name, char* text);
extern void func_001A4F70(const char* format, ...);
const char D_003F54A0[] = "Message to Level Designer\n"
                           "Physics object %s tagged for Pathfinding collision has been removed without reexporting the world view\n"
                           "Reexport the world view and save it to get rid of that message";
extern s32 func_0014C570(PS2GameObjectRecord* object);
extern void func_00175A00(PS2CollisionQueue* queue, PS2GameObjectRecord* object, s32 flag);
extern s32 func_00170D20(PS2LiveCollision* collision);
extern s32 func_00175BB0(PS2CollisionQueue* queue, PS2GameObjectRecord* object);
extern s32 func_00175BF0(void* queue, void* object);
extern s32 func_00175C30(PS2CollisionQueue* queue, PS2GameObjectRecord* object);
extern void func_00175F10(PS2PendingCollision* pending, PS2GameObjectRecord* object, s32 flag);
extern void func_00170CD8(PS2LiveCollision* collision);
extern void func_00170C90(PS2LiveCollision* collision);
extern void func_001718D0(PS2LiveCollision* collision, PS2GameObjectRecord* object, s32 index);

extern void * D_0040F4D0;
extern s32 func_0012A7C0(void *);
extern s32 func_0012AE58(void *);

// Accessed storage prefix; original class identity remains UNVERIFIED.
typedef struct {
    PS2CollisionQueue queue;
    u8 unk_280[4];
    s32 unk_284;
    s32 unk_288;
} Recovered_CollisionQueueStorage;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175750);

void func_00175980(PS2CollisionQueue* queue, u64 name, s32 flag) {
    char nameText[16];
    PS2GameObjectRecord* object = func_00129160((PS2GameObjectManager*)D_0040F4D0, name);
    if (object != NULL) {
        func_00175A00(queue, object, flag);
    } else {
        func_00272488(name, nameText);
        func_001A4F70(D_003F54A0, nameText);
    }
}
void func_00175A00(PS2CollisionQueue* queue, PS2GameObjectRecord* object, s32 flag) {
    s32 liveIndex = func_00175BB0(queue, object);
    s32 pendingIndex;
    if (liveIndex != -1) {
        PS2LiveCollision** entry = &queue->live[liveIndex];
        if (func_00170D20(*entry) != 0)
            return;
        func_00170740(*entry);
    }
    pendingIndex = func_00175BF0(queue, object);
    if (pendingIndex == -1) {
        s32 freeIndex = func_00175C30(queue, object);
        if (freeIndex != pendingIndex) func_00175F10(&queue->pending[freeIndex], object, flag);
    }
}
s32 func_00175AB8(PS2CollisionQueue* queue, PS2GameObjectRecord* object, s32 reset) {
    s32 index = 0;
    PS2PendingCollision* pending = queue->pending;
    PS2GameObjectRecord** pendingObject = &pending->object;
    PS2LiveCollision** live;
    do {
        index++;
        if (*pendingObject == object) {
            func_00175EF8(pending);
            return 1;
        }
        pending++;
        pendingObject = (PS2GameObjectRecord**)((u8*)pendingObject + sizeof(PS2PendingCollision));
    } while (index < 48);
    live = queue->live;
    index = 0;
    do {
        PS2LiveCollision* collision = *live;
        index++;
        if (collision->object == object) {
            if (reset)
                func_00170740(collision);
            else
                func_00170CD8(collision);
            return 1;
        }
        live++;
    } while (index < 16);
    return 0;
}
#ifdef NON_MATCHING
// Unmatched: loop exit and success branch layout differ.
s32 func_00175B60(PS2CollisionQueue* queue, PS2GameObjectRecord* object) {
    PS2LiveCollision** current = queue->live;
    s32 index = 0;
loop:
    {
        PS2LiveCollision* collision = *current;
        index++;
        if (collision->object == object) {
            func_001718D0(collision, object, index);
            return 1;
        }
    }
    current++;
    if (index < 16)
        goto loop;
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175B60);
#endif
s32 func_00175BB0(PS2CollisionQueue* queue, PS2GameObjectRecord* object) {
    PS2LiveCollision** current = queue->live;
    s32 index = 0;
    do {
        PS2LiveCollision* collision = *current;
        if (collision->state == 4 && collision->object == object)
            return index;
        index++;
        current++;
    } while (index < 16);
    return -1;
}

s32 func_00175BF0(void *arg0, void *arg1) {
    s32 var_3;
    void *var_4;

    var_4 = arg0 + 0x44;
    var_3 = 0;
loop_1:
    if (M2C_FIELD(var_4, u8 *, -4) != 0) {
        goto block_3;
    }
    var_3 += 1;
    goto block_8;
block_3:
    if (M2C_FIELD(var_4, s32 *, 0) == arg1) {
        goto block_6;
    }
    var_3 += 1;
    goto block_8;
block_6:
    return var_3;
block_8:
    var_4 += 0xC;
    if (var_3 < 0x30) {
        goto loop_1;
    }
    return -1;
}

s32 func_00175C30(PS2CollisionQueue* arg0, PS2GameObjectRecord* unused) {
    s32 var_3;
    u8 *var_4;

    var_4 = (u8*)arg0 + 0x40;
    var_3 = 0;
loop_1:
    if (*var_4 != 0) {
        var_3 += 1;
        var_4 += 0xC;
        if (var_3 >= 0x30) {
            return -1;
        }
        goto loop_1;
    }
    return var_3;
}

#ifdef NON_MATCHING
// Unmatched: live-array and selection-index registers differ.
// UNVERIFIED: the ordering key and flag fields are only read by this draft.
typedef struct {
    u8 unk_00[0x70];
    PS2GameObjectRecord* object;
    f32 unk_74;
    u8 unk_78;
    u8 unk_79[3];
    s32 state;
} Recovered_CollisionCandidate;

s32 func_00175C60(Recovered_CollisionCandidate** cursor) {
    s32 best = -1;
    s32 index = 0;
    Recovered_CollisionCandidate** live = cursor;
    do {
        if ((*cursor)->state == 0)
            return index;
        index++;
        cursor++;
    } while (index < 16);

    index = 0;
    cursor = live;
    do {
        Recovered_CollisionCandidate* collision = *cursor;
        if (collision->state == 4 && (best == -1 || collision->unk_74 < live[best]->unk_74))
            best = index;
        index++;
        cursor++;
    } while (index < 16);
    if (best != -1)
        return best;

    index = 0;
    cursor = live;
    do {
        Recovered_CollisionCandidate* collision = *cursor;
        if (collision->unk_78 == 0 && (best == -1 || collision->unk_74 < live[best]->unk_74))
            best = index;
        index++;
        cursor++;
    } while (index < 16);
    if (best != -1)
        return best;

    index = 0;
    cursor = live;
    do {
        Recovered_CollisionCandidate* collision = *cursor;
        if (best == -1 || collision->unk_74 < live[best]->unk_74)
            best = index;
        index++;
        cursor++;
    } while (index < 16);
    return best;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175C60);
#endif
s32 func_00175DB8(Recovered_CollisionQueueStorage* storage, s32 group) {
    PS2CollisionQueue* queue = &storage->queue;
    PS2LiveCollision** live = queue->live;
    s32 remaining = 15;
    PS2PendingCollision* pending;
    PS2GameObjectRecord** pendingObject;
    s32 more;
    do {
        PS2GameObjectRecord* object = (*live)->object;
        if (object != NULL && group == func_0014C570(object))
            func_00170740(*live);
        live++;
        remaining--;
    } while (remaining >= 0);
    pending = queue->pending;
    pendingObject = &pending->object;
    do {
        PS2GameObjectRecord* object = *pendingObject;
        if (object != NULL && group == func_0014C570(object))
            func_00175EF8(pending);
        pendingObject = (PS2GameObjectRecord**)((u8*)pendingObject + sizeof(PS2PendingCollision));
        more = (s32)pendingObject < (s32)&storage->unk_284;
        pending++;
    } while (more);
    return more;
}
#ifdef NON_MATCHING
// Unmatched: live-pointer and queue registers differ.
void func_00175E80(PS2CollisionQueue* queue) {
    PS2LiveCollision** current;
    PS2LiveCollision* collision;
    PS2GameObjectRecord* object;
    s32 remaining;
    current = queue->live;
    remaining = 15;
    collision = *current;
loop:
    remaining--;
    current++;
    object = collision->object;
    if (object != NULL) {
        func_00170740(collision);
        func_00175A00(queue, object, 0);
    }
    if (remaining >= 0) {
        collision = *current;
        goto loop;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175E80);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175EF8);

void func_00175F10(PS2PendingCollision* arg0, PS2GameObjectRecord* arg1, s32 arg2) {
    M2C_FIELD(arg0, s8 *, 1) = arg2;
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, PS2GameObjectRecord**, 4) = arg1;
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
}

void func_00175F38(void) {

}

s32 func_00175F40(void) {
    return 1;
}

s32 func_00175F48(void) {
    return 1;
}

s32 func_00175F50(void) {
    return func_0012A7C0(D_0040F4D0) != 0;
}

s32 func_00175F78(void) {
    return func_0012AE58(D_0040F4D0) != 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00175FA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/world/tu_1756c0", func_00176258);
