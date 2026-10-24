#include "include_asm.h"

#include "game/actor/mod_world.hpp"
namespace ModWorld {
extern char *effects __asm__("D_0040F4D8");
extern char *objects __asm__("D_0040F4CC");
extern World *world __asm__("D_0040F4D0");
extern void *cache __asm__("D_0040F4C4");
extern void BaseInitialize(ObjectActor*) __asm__("func_00125C60");
extern void DropSlot(void*,unsigned short) __asm__("func_001B37C8");
extern void DropEffect(void*,ObjectActor*) __asm__("func_001B61C0");
extern void AttachObject(void*,ObjectActor*,int,int) __asm__("func_0025C558");
extern void Link(World*,ObjectActor*) __asm__("func_0012A158");
struct ResourceList {char unknown00[8];int count;};
struct SceneData {char unknown00[0x398];void*level;ResourceList*effects;};
extern SceneData*LoadedSource(void*) __asm__("func_001092F8");
extern void RelocateScene(SceneData*) __asm__("func_002881A8");
extern void RelocateSection(SceneData*) __asm__("func_00288488");
extern void RegisterResource(void*,int,void*,int) __asm__("func_00108540");
extern void FixList(ResourceList*) __asm__("func_00272AA8");
extern void*ResourceAt(ResourceList*,int) __asm__("func_003822F8");
extern void FixEffect(void*) __asm__("func_001AF930");
extern void BindScene(void*,void*) __asm__("func_00160648");
extern void FinishScene() __asm__("func_0016BE10");

void ObjectActor::Initialize(Definition *data, int which)
{
    BaseInitialize(this);
    index = which;
    definition = data;
    active = 1;
    slot = 0xffff;
    kind = 0;
    effect = 0;
    unsigned long id = data->name;
    mode = 0;
    name = id;
}

int ObjectActor::Cleanup()
{
    if (slot != 0xffff) DropSlot(effects + 0x33c40, slot);
    if (effect) {
        DropEffect(effects + 0x512e0, this);
        effect = 0;
    }
    return 1;
}

Definition *ObjectActor::GetDefinition() { return definition; }
void ObjectActor::ResetSlot() { slot = 0xffff; }

Region *World::FindRegion(int requested)
{
    Region *region = regions;
    int i = 0;
again:
    ++i;
    if (region->id != requested) {
        ++region;
        if (i < 2) goto again;
        return 0;
    }
    return region;
}

void World::Activate(ObjectActor *actor, int add, int flags)
{
    if (add) AttachObject(objects, actor, flags, 8);
    Link(this, actor);
    actor->linked = 1;
}

int World::MarkSolid(TraceHit *hit, unsigned char *found)
{
    if (hit->MaterialFlags() & 0x10000000) return 1;
    *found = 1;
    return 0;
}

void World::SceneLoaded(void *request)
{
    SceneData *data = LoadedSource(request);
    RelocateScene(data);
    RegisterResource(cache, 6, data, world->level);
    RegisterResource(cache, 0, data->level, 0);
    ResourceList *list = data->effects;
    FixList(list);
    for (int i = 0; i < list->count; ++i) FixEffect(ResourceAt(list, i));
    RegisterResource(cache, 1, data->effects, 0);
    BindScene((char *)world + 0x8f0, (char *)data + 4);
    FinishScene();
}

void World::SectionLoaded(void *request)
{
    SceneData *data = LoadedSource(request);
    RelocateSection(data);
    int levelKey = (int)(((int)((unsigned char)world->level << 24) >> 8) |
                         ((unsigned char)world->section << 24)) >> 16;
    RegisterResource(cache, 11, data, levelKey);
}

int World::SelectWorldHit(QueryHit *hit, ClosestHit *out)
{
    if (hit->MaterialFlags() & 0x10000000) return 1;
    float previous = out->fraction;
    if (previous == 2 || hit->fraction < previous) {
        out->point = hit->point;
        out->normal = hit->normal;
        out->fraction = hit->fraction;
        out->mask = hit->MaterialFlags();
    }
    return 0;
}

}
// Unmatched: 0x127118 native inline aggregate/call context or register scheduling.
// Unmatched: 0x127550 native inline aggregate/call context or register scheduling.
// Unmatched: 0x1277a0 native inline aggregate/call context or register scheduling.
// Unmatched: 0x127ac8 native inline aggregate/call context or register scheduling.
// Unmatched: 0x127cf0 native inline aggregate/call context or register scheduling.
// Unmatched: 0x128008 native inline aggregate/call context or register scheduling.
// Unmatched: 0x128120 native inline aggregate/call context or register scheduling.
// Unmatched: 0x1282e0 native inline aggregate/call context or register scheduling.
// Unmatched: 0x128480 native inline aggregate/call context or register scheduling.
// Unmatched: 0x129090 native inline aggregate/call context or register scheduling.
// Unmatched: 0x129160 native inline aggregate/call context or register scheduling.
// Unmatched: 0x129240 native inline aggregate/call context or register scheduling.
// Unmatched: 0x129360 native inline aggregate/call context or register scheduling.
// Unmatched: 0x1297a0 native inline aggregate/call context or register scheduling.
// Unmatched: 0x1297e0 native inline aggregate/call context or register scheduling.
// Unmatched: 0x129de8 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12a158 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12a1e0 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12a280 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12a4d8 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12a5f8 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12a7c0 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12a918 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12ab28 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12ab90 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12ae00 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12ae58 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12b0e0 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12b328 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12b448 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12b720 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12b950 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12bb60 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12be18 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12be80 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12bfc8 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12c118 native inline aggregate/call context or register scheduling.
// Unmatched: 0x12c428 native inline aggregate/call context or register scheduling.

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001277A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00127AB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00127AC0);

#ifdef NON_MATCHING
// Unmatched: 0x127AC8 signed pool iteration, normalized-length temporaries and wide input lifetimes.
// Unmatched: 0x127CF0 corner-constructor/readback temporaries, clip iteration and submission control flow.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00127AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00127CF0);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00128008);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00128120);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001282C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001282D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001282E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00128480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00129090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00129160);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001291C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001291E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00129218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00129240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00129360);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001297A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001297E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00129DE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A0D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A1E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A280);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A4D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A5F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A7C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012AB28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012AB90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012AE00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012AE58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012B0E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012B328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012B448);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012B720);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012B950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012BB60);
