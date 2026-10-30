#include "ps2/prelude.h"

// Partial native overlay records; original class names and unused fields remain UNVERIFIED.
extern "C" void* func_00107D20(u32);
extern "C" void func_001F1C08(void*);
extern "C" void func_00107B78(void*, s32, u32, s32);
extern "C" u8 D_0040F0F0[];
struct OverlayPoint {
    union {
        struct {
            f32 x, y;
        };
        s64 bits;
    };
    OverlayPoint() {}
    OverlayPoint(f32 a, f32 b) {
        x = a;
        y = b;
    }
    OverlayPoint(const OverlayPoint& p) { bits = p.bits; }
    OverlayPoint& operator=(const OverlayPoint& p) {
        bits = p.bits;
        return *this;
    }
};
struct OverlayGroup {
    void** commands;
    s32 unknown4;
    OverlayPoint position;
    u8* states;
    f32 remaining;
    s8 count;
    u8 unknown19[7];
    OverlayGroup() {}
    void AllocateCommands() { commands = (void**)func_00107D20(40); }
    void AllocateStates() { states = (u8*)func_00107D20(10); }
    static void* operator new[](u32 size) { return func_00107D20(size); }
};
struct OverlayEntry {
    OverlayPoint position;
    s32 resource;
    f32 angle;
    OverlayEntry() {}
    static void* operator new[](u32 size) { return func_00107D20(size); }
};
struct OverlayNotification {
    u8 unknown0[0x18];
    void** commands;
    OverlayEntry* entries;
    OverlayGroup* groups;
    u8* entryFlags;
    u8* groupFlags;
};
extern "C" void func_001F36E8(OverlayNotification* self) {
    func_001F1C08(self);
    func_00107B78(D_0040F0F0, 1, 0x40, 0);
    self->groups = new OverlayGroup[8];
    func_00107B78(D_0040F0F0, 1, 0x10, 0);
    self->commands = (void**)func_00107D20(0xA0);
    self->entries = new OverlayEntry[40];
    func_00107B78(D_0040F0F0, 1, 8, 0);
    self->entryFlags = (u8*)func_00107D20(40);
    self->groupFlags = (u8*)func_00107D20(8);
    s8 i, j;
    for (i = 0; i < 40; i++) {
        self->entries[i].position = OverlayPoint(0.5f, 2.5625f);
        self->entries[i].resource = 0;
        self->entries[i].angle = 0;
        self->entryFlags[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        func_00107B78(D_0040F0F0, 1, 0x10, 0);
        self->groups[i].AllocateCommands();
        func_00107B78(D_0040F0F0, 1, 8, 0);
        self->groups[i].AllocateStates();
        self->groupFlags[i] = 0;
        for (j = 0; j < 10; j++) self->groups[i].commands[j] = 0;
    }
    func_00107B78(D_0040F0F0, 1, 0x80, 0);
}

typedef char OverlayGroupSize[sizeof(OverlayGroup) == 0x20 ? 1 : -1];
typedef char OverlayEntrySize[sizeof(OverlayEntry) == 0x10 ? 1 : -1];
