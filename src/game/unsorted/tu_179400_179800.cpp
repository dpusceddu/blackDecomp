#include "ps2/prelude.h"
#include "kynapse/alloc.hpp"
extern KaimAllocator* D_003C87E8;
extern void (*D_003C87EC)(void*, unsigned, unsigned);
/* Partial native layouts. Original class identities and field meanings are UNVERIFIED. */
struct Bound {
    virtual void Slot0();
    virtual void Configure(void*);
};
typedef struct {
    s32 unknown00;
    void* graph;
    s32 unknown08;
    Bound* bound;
    s32 unknown10;
    s32 count;
    s32 unknown18;
    void* path;
    s32 unknown20;
    void* extra;
} State;
typedef struct {
    s32 unknown00;
    void* owner;
    s32 first, second, count;
    s32 unknown14;
    u8 path[0x200];
    u8 extra;
} Definition;
extern "C" void* func_0016FA38(void);
extern "C" void* func_002F5C10(void*);
extern u8 D_003DFFE0[];
extern "C" void func_00289480(void*, void*);
extern "C" Bound* func_002F0A00(void*, void*);
extern "C" s32 func_002EF1A0(void*, void*);
extern "C" void func_00179800(State* self, Definition* definition) {
    void* graphStorage;
    void* boundStorage;
    void* graph;
    Bound* bound;
    void* request;
    void* path;
    void* extra;
    u32 tag;
    s32 count;
    request = func_0016FA38();
    graphStorage = NULL;
    tag = D_003C87E8->Allocate(0x98, &graphStorage);
    if (D_003C87EC) D_003C87EC(graphStorage, 0x98, tag);
    graph = graphStorage;
    func_002F5C10(graph);
    M2C_FIELD(graph, void**, 0) = D_003DFFE0;
    func_00289480(definition->owner, graph);
    boundStorage = NULL;
    tag = D_003C87E8->Allocate(0x1C, &boundStorage);
    if (D_003C87EC) D_003C87EC(boundStorage, 0x1C, tag);
    bound = func_002F0A00(boundStorage, graph);
    M2C_FIELD(request, s32*, 8) = definition->first;
    M2C_FIELD(request, s32*, 4) = definition->second;
    bound->Configure(request);
    func_002EF1A0(bound, request);
    count = definition->count;
    path = definition->path;
    extra = &definition->extra;
    self->bound = bound;
    self->graph = graph;
    self->path = path;
    self->extra = extra;
    self->count = count;
}
