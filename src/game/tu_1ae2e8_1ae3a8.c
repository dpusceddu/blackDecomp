#include "auto/prelude.h"
#include "game/actor/render_state.h"

extern void func_0027B2C8(void *), func_001C6608(void *), func_001B0A20(void *);
extern void func_001B0068(void *), func_001B0FC8(void *);
extern void func_002A90E8(void *), func_002A9140(void *, int, int);
extern void func_0026A6F0(void *), func_0026A7A0(void), func_0027B260(void *);
extern int func_001AEA18(void *, int);

int func_001AE3A8(char *actor) {
    func_0027B2C8(actor + 0xd360);
    func_0027B2C8(actor + 0xd400);
    func_0027B2C8(actor + 0xd4a0);
    func_001C6608(actor + 0xd170);
    func_001B0A20(actor + 0xd290);
    func_001B0068(actor + 0xcbe0);
    func_001B0FC8(actor + 0xd350);
    return 1;
}

void func_001AE538(BkActorRenderPS2 *actor) {
    func_002A90E8(actor->resource->geometry);
    actor->resource = 0;
}

void func_001AE570(s32 actor) {
    int buffer = actor + 0xd360;
    void **geometry = (void **)((char *)buffer + 0x58);
    func_002A9140(*geometry, 0, 1);
}

void func_001AE5A0(BkActorRenderPS2 *actor) {
    func_0026A6F0(actor->resource);
}

void func_001AE5C8(void) {
    func_0026A7A0();
}

void func_001AE8F0(BkActorRenderPS2 *actor) {
    func_0027B260(&actor->buffers[1]);
    func_0027B260(&actor->buffers[2]);
    func_0027B260(&actor->buffers[0]);
}

int func_001AE9F8(BkActorRenderPS2 *actor) {
    return func_001AEA18(actor, 0);
}
