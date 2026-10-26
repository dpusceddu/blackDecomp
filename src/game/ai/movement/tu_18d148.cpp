#include "include_asm.h"
#include "game/ai_mode_dispatcher.hpp"
extern "C" {
#include "game/sequence.h"
}
#include "game/actor/world_objects.hpp"
using namespace Game;
extern "C" {
extern void func_00181AD0(void*, int);
extern int func_0018DDD8(void*);
extern void func_00188B40(void*, int, float, float);
extern void func_0018AB98(void*);
extern Recovered_ModeDescriptor* func_00160458(void*, void*);
extern void* D_0040F4D4;
extern WorldObjects::World* D_0040F4D0;
int ModeDispatcher_Reset(ModeDispatcher*);
void ModeDispatcher_SetMode(ModeDispatcher*, Recovered_ModeDescriptor*);
void ModeDispatcher_ClearFlags(ModeDispatcher*);
void ModeDispatcher_SetFlag2(ModeDispatcher*);
Recovered_DispatchedMode* ModeDispatcher_ActiveMode(ModeDispatcher* self);

void ModeDispatcher_ReplaceStorageKind(ModeDispatcher* self, signed char kind) {
    Recovered_DispatchedMode* mode = ModeDispatcher_ActiveMode(self);
    if (mode) {
        if (mode->sequence) {
            if (Sequence_ClassifyStorage(mode->sequence) == kind) {
                int replace = 0;
                if (self->active == 1) {
                    if (func_0018DDD8((char*)self->owner + 0xC94)) replace = 1;
                }
                ModeDispatcher_Reset(self);
                if (replace) ModeDispatcher_SetMode(self, (Recovered_ModeDescriptor*)((char*)D_0040F4D4 + 0x22A00));
            }
        }
    }
}
#ifdef NON_MATCHING
// Unmatched: zero-case branch placement differs.
Recovered_DispatchedMode* ModeDispatcher_ActiveMode(ModeDispatcher* self) {
    if (self->active) return self->modes[self->active];
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18d148", func_0018D1F0);
#endif
}
void ModeDispatcher::Event(QueuedActionEvent* event) {
    switch ((int)event->kind) {
        case 5:
            if (flags & 2) ModeDispatcher_ClearFlags(this);
            if (flags & 1) ModeDispatcher_SetFlag2(this);
            break;
        case 4:
            if (flags & 8) ModeDispatcher_ClearFlags(this);
        case 20: *((Byte*)owner + 0xD26) = 1; break;
    }
    modes[active]->Event(event);
}
extern "C" {
int func_0018D2F8(ModeDispatcher* self, void* argument) { return self->modes[self->active]->Unknown7(argument); }
int func_0018D330(ModeDispatcher* self, void* argument) { return self->modes[self->active]->Unknown8(argument); }
int func_0018D368(ModeDispatcher* self, void* argument) { return self->modes[self->active]->Unknown9(argument); }
void ModeDispatcher_SetMode(ModeDispatcher* self, Recovered_ModeDescriptor* descriptor) {
    ModeDispatcher_Reset(self);
    if (descriptor) {
        self->active = descriptor->mode;
        self->modes[self->active]->Enter(descriptor);
        func_00181AD0((char*)self->owner + 0xEC0, 12);
    }
}
inline bool RegionHasModes(WorldObjects::Region* region) { return *(int*)region == 28; }
void ModeDispatcher_FindAndSetMode(ModeDispatcher* self, void* key) {
    Recovered_ModeDescriptor* descriptor = 0;
    if (key) {
        int i = 0;
        do {
            WorldObjects::Region* region = &D_0040F4D0->regions[(signed char)i];
            if (region && RegionHasModes(region)) {
                descriptor = func_00160458((char*)region + 0x40, key);
                if (descriptor) break;
            }
            ++i;
        } while (i < 2);
    }
    ModeDispatcher_SetMode(self, descriptor);
}
#ifdef NON_MATCHING
// Unmatched: constant lifetime adds a saved register and reorders byte stores.
int ModeDispatcher_Reset(ModeDispatcher* self) {
    if (self->active) self->modes[self->active]->Leave();
    self->active = 0;
    self->modes[0]->Enter(0);
    if (self->flags & 3) ModeDispatcher_ClearFlags(self);
    self->unk_17 = 0;
    self->unk_14 = 1;
    func_00188B40((char*)self->owner + 0x290, 1, 0.0f, 5.0f);
    *((signed char*)self->owner + 0xC7E) = 1;
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18d148", func_0018D4C8);
#endif
void ModeDispatcher_ClearBinding(ModeDispatcher* self) {
    func_0018AB98(self->unk_08);
    self->modes[self->active]->Leave();
}
int func_0018D5D0(ModeDispatcher* self) { return self->modes[self->active]->Unknown10(); }
unsigned char ModeDispatcher_IsPaused(ModeDispatcher* self) { return self->paused; }
void ModeDispatcher_Resume(ModeDispatcher* self) {
    if (self->paused) {
        self->paused = 0;
        self->modes[self->active]->enabled = 0;
        func_00181AD0((char*)self->owner + 0xEC0, 10);
    }
}
void ModeDispatcher_Pause(ModeDispatcher* self) {
    if (self->paused == 0) {
        self->paused = 1;
        func_00181AD0((char*)self->owner + 0xEC0, 9);
    }
}
void ModeDispatcher_SetParameter(ModeDispatcher* self, int value) {
    self->unk_18 = value;
    func_00181AD0((char*)self->owner + 0xEC0, 11);
}
int func_0018D6C0(ModeDispatcher* self) { return self->modes[self->active]->Unknown11(); }
int func_0018D6F8(ModeDispatcher* self, void* argument) { return self->modes[self->active]->Unknown12(argument); }
int func_0018D730(ModeDispatcher* self, void* argument) { return self->modes[self->active]->Unknown13(argument); }
int func_0018D768(ModeDispatcher* self, void* argument) { return self->modes[self->active]->Unknown14(argument); }
void ModeDispatcher_SetFlags(ModeDispatcher* self, signed char flags) {
    int notify = 0;
    if (flags != (signed char)self->flags) {
        if ((flags & 16) || (self->flags & 16)) notify = 1;
    }
    if (flags & 16)
        self->flags = 16;
    else
        self->flags = flags;
    if (notify) func_00181AD0((char*)self->owner + 0xEC0, 13);
}
void ModeDispatcher_ClearFlags(ModeDispatcher* self) {
    if (self->flags & 0xEF) {
        self->flags = 0x10;
        func_00181AD0((char*)self->owner + 0xEC0, 13);
    }
}
void ModeDispatcher_SetFlag2(ModeDispatcher* self) { self->flags = (self->flags & 0xFE) | 2; }
}
