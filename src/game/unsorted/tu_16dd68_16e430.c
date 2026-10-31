#include "ps2/prelude.h"
extern void func_0013DAB0(s32);
extern void func_00172700(void*);
extern s32 func_001771F0(void*);
extern void func_00175E80(void*);
extern void func_0017BA38(void*);
extern void func_0017B240(s32);
extern u8* func_00179698(void*, s32);
extern u64* func_001796B0(void*, s32);
extern void* func_001796C8(void*, s32);
extern s32 func_00289F30(void*, u8*, u64*, void*, void*);
extern void* func_00179668(void*, s32);
extern s32 func_00289698(void*, void*);
extern void* func_0016DD68(void*, s32);
extern void* D_0040F4D4;

s32 func_0016E430(void* self) {
    void *collisionQueue, *channels, *selection, *commands, *graph;
    u8* values;
    u64* rows;
    void* other;
    s32 remaining;
    s32 memberRemaining;
    void** member;
    void* runtime;
    u8* actor = (u8*)self + 0x2B00;
    remaining = 15;
    do {
        if (M2C_FIELD(actor, u8*, 0x78)) func_0013DAB0((s32)actor);
        --remaining;
        actor += 0x1FD0;
    } while (remaining >= 0);
    channels = (u8*)self + 0x78;
    collisionQueue = (u8*)self + 0xA48;
    selection = (u8*)self + 0x1290;
    commands = (u8*)self + 0x1150;
    graph = (u8*)self + 0x13D0;
    member = (void**)((u8*)self + 0x22B20);
    memberRemaining = 1;
    do {
        void* object = *member;
        --memberRemaining;
        ++member;
        func_00172700(object);
    } while (memberRemaining >= 0);
    func_001771F0(channels);
    func_00175E80(collisionQueue);
    func_0017BA38(selection);
    func_0017B240((s32)commands);
    values = func_00179698(self, 1);
    rows = func_001796B0(self, 1);
    other = func_001796C8(self, 1);
    func_00289F30(graph, values, rows, other, func_00179668(self, 1));
    runtime = D_0040F4D4;
    return func_00289698(M2C_FIELD(runtime, void**, 0x1140), func_0016DD68(self, 1));
}
