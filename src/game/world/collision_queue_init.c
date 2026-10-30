#include "ps2/prelude.h"
#include "ps2/recovered_types.h"
extern void func_00170740(PS2LiveCollision*);
extern void func_00175EF8(PS2PendingCollision*);
// UNVERIFIED: the complete storage layout and original class identity remain unknown.
typedef struct {
    PS2CollisionQueue queue;
    u8 unk_280[4];
    s32 unk_284;
    s32 unk_288;
} Recovered_CollisionQueueStorage;

s32 func_001756C0(Recovered_CollisionQueueStorage* storage, PS2LiveCollision** source) {
    PS2CollisionQueue* queue = &storage->queue;
    PS2LiveCollision** current = queue->live;
    PS2PendingCollision* pending;
    s32 remaining = 15;
    do {
        PS2LiveCollision* collision = *source;
        remaining--;
        source++;
        *current = collision;
        func_00170740(collision);
        current++;
    } while (remaining >= 0);
    pending = queue->pending;
    remaining = 47;
    do {
        func_00175EF8(pending);
        remaining--;
        pending++;
    } while (remaining >= 0);
    storage->unk_284 = 0;
    storage->unk_288 = 0;
    return 1;
}

extern void func_00170C90(PS2LiveCollision*);
s32 func_00175930(PS2CollisionQueue* queue) {
    PS2LiveCollision** current = queue->live;
    s32 remaining;
    for (remaining = 15; remaining >= 0; remaining--, current++) func_00170C90(*current);
    return 1;
}
