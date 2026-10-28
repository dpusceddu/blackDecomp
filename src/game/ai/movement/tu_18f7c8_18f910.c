#include "ps2/prelude.h"

/* UNVERIFIED: partial views of the movement configuration and owner. */
typedef union Recovered_MovementInitVector {
    s128 raw;
    f32 lane[4];
} Recovered_MovementInitVector;
typedef struct Recovered_MovementInitConfig {
    u8 pad[0x10];
    s128 vector;
    u8 pad2[0x24];
    u64*keys[5];
    u64*lists[5];
    f32 distance, weight;
    u8 pad3[0x11];
    u8 enabled[5], counts[5];
} Recovered_MovementInitConfig;
typedef struct Recovered_MovementInitResource {
    u8 pad[0x28];
    Recovered_MovementInitConfig*config;
} Recovered_MovementInitResource;
typedef struct Recovered_MovementInitOwner {
    u8 pad[0x640];
    f32 weight;
} Recovered_MovementInitOwner;
typedef struct Recovered_MovementInitState {
    void*dispatch;
    Recovered_MovementInitOwner*owner;
    s32 status;
    u8 pad[8];
    s32 choices[5];
    s32 current;
    u64*list;
    u8 timer[4];
    f32 time;
    Recovered_MovementInitResource*resource;
    u8 count, configured, mode, pending, flag;
} Recovered_MovementInitState;

extern u8*D_0040F4D0;
extern void*D_0040F4F4;
extern void func_0018E458(void*, s32);
extern s32 func_0018DDD8(void*);
extern s32 func_00169898(void*, u64);
extern void func_00180AA0(void*, s128, s32, f32);
extern void func_00180B38(void*, f32);
extern void func_00173690(void*);
extern void func_00190020(Recovered_MovementInitState*);
extern void func_001901E0(Recovered_MovementInitState*, u8);

void func_0018F910(Recovered_MovementInitState*self, Recovered_MovementInitResource*resource) {
    Recovered_MovementInitConfig*config;
    int i;
    Recovered_MovementInitVector vector;
    u8*timer;
    func_0018E458(self, (s32)resource);
    if (func_0018DDD8((u8*)self->owner + 0xC94)) self->status = 0;
    self->resource = resource;
    config = resource->config;
    timer = self->timer;
    for (i = 4; i >= 0; i--) self->choices[i] = 0;
    self->current = 0;
    self->list = 0;
    self->count = 0;
    self->configured = 0;
    if (config->enabled[0] && config->counts[0]) {
        self->choices[0] = func_00169898(D_0040F4F4, *config->keys[0]);
        self->configured++;
    }
    if (config->enabled[1] && config->counts[1]) {
        self->choices[1] = func_00169898(D_0040F4F4, *config->keys[1]);
        self->configured++;
    }
    if (config->enabled[2] && config->counts[2]) {
        self->choices[2] = func_00169898(D_0040F4F4, *config->keys[2]);
        self->configured++;
    }
    if (config->enabled[3] && config->counts[3]) {
        self->choices[3] = func_00169898(D_0040F4F4, *config->keys[3]);
        self->configured++;
    }
    if (config->enabled[4] && config->counts[4]) {
        self->choices[4] = func_00169898(D_0040F4F4, *config->keys[4]);
        self->configured++;
    }
    vector.raw = config->vector;
    /* The fourth lane is read from the captured quadword in memory. */
    func_00180AA0((u8*)self->owner + 0xB30, vector.raw, 2, *(volatile f32*)&vector.lane[3]);
    func_00180B38((u8*)self->owner + 0xB30, config->distance);
    self->owner->weight = config->weight;
    self->pending = 0;
    self->flag = 0;
    self->time = M2C_FIELD(D_0040F4D0, f32*, 0x20);
    self->mode = 5;
    func_00173690(timer);
    if (self->configured >= 2)
        func_00190020(self);
    else
        func_001901E0(self, 0);
}
