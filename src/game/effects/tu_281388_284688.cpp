#include "include_asm.h"
#include "game/graphics/audio_provider.hpp"
struct KaimAllocator;
extern KaimAllocator* gKaimAllocator __asm__("D_003C87E8");
extern void (*gKaimAllocateHook)(void*, unsigned, unsigned) __asm__("D_003C87EC");
#include "kynapse/alloc.hpp"
extern char D_003E29F0[];
struct SmallEffect {
    void* vtable;
    unsigned unknown04;
};

extern "C" void func_00287600(void*);
extern "C" void func_00287618(void*);
// Partial serialized-object view; only the offset words below are confirmed.
struct RelocatableEffect {
    unsigned unknown00[2];
    unsigned field08, field0c, field10, field14, unknown18[2];
    unsigned field20, field24, field28, field2c, field30, field34, field38, field3c, field40, field44, field48, field4c,
        field50, field54, field58, field5c, field60, field64, field68;
};

struct RelocatableRecord {
    unsigned first, second;
};
struct RelocatableTable {
    unsigned unknown00[2];
    int count;
    RelocatableRecord** records;
};
extern "C" void func_00272730(void*);
extern "C" void func_00286CA8(void*);

#include "game/effects/dependency_graph.hpp"

static inline EffectParameter* Source(EffectInstance* item) {
    if (item == &item->definition->embedded) return &item->definition->sourceDefault;
    return &item->definition->parameters[item->definition->sourceIndices[item->index]];
}
static inline EffectParameter* Target(EffectInstance* item) {
    if (item == &item->definition->embedded) return &item->definition->targetDefault;
    return &item->definition->parameters[item->definition->targetIndices[item->index]];
}
extern "C" int func_0028A368(EffectGraph*, unsigned char, unsigned char, unsigned);

static inline unsigned long Collect(EffectGraph* self, unsigned long mask) {
    unsigned long result = 0;
    unsigned char i = 0;
    unsigned long bit = 1;
    for (; i < 63; i++, bit <<= 1) {
        if (mask & bit) result |= self->rows[i];
    }
    return result;
}

struct EffectLink {
    EffectLink *next, *previous;
};
struct EffectOwner {
    char unknown00[0x90];
    EffectLink links;
};
struct EffectAttachment {
    unsigned unknown00;
    EffectOwner* owner;
    EffectLink link;
};
extern "C" void func_002AA288(EffectOwner*);

struct RelocatableResourceE0 {
    char unknown00[0xe0];
    unsigned offset;
};

// Partial resource record views; unknown bytes and original class identities are UNVERIFIED.
struct ResourceEntryProperty {
    unsigned unknown00, offset, unknown08[2];
};
struct ResourceEntry {
    char unknown00[0x30];
    ResourceEntryProperty property;
};
struct ResourceEntries {
    unsigned count;
    char unknown04[12];
    ResourceEntry entries[1];
};
struct ResourceProperties {
    char unknown00[0x38];
    unsigned offset;
    inline void Relocate(void* base) {
        if (offset) offset += (unsigned)base;
    }
};
struct RelocatableResource {
    unsigned field00, field04, field08;
    char unknown0c[24];
    ResourceEntries* entries;
    char unknown28[12];
    ResourceProperties properties;
    unsigned links[7];
};

struct ResourceResult {
    char unknown00[0x30];
};
struct ResourceLookup {
    int count;
    void** keys;
    signed char* kinds;
    ResourceResult* results;
};
extern "C" int func_001AD2E8(void*, signed char, const char*);
extern "C" void func_001AD098(ResourceResult*);

struct EffectRecord {
    char unknown00[0x30];
    unsigned long mask;
    char unknown38[0x28];
};
struct EffectCollection {
    unsigned unknown00;
    EffectRecord* records;
    EffectInstance** instances;
};
struct EffectRepository {
    char unknown00[0x70];
    unsigned primaryCount, secondaryCount;
    EffectCollection *primary, *secondary;
};
struct EffectSystem {
    char unknown00[0x1140];
    EffectRepository* repository;
};
extern EffectSystem* D_0040F4D4;
static inline EffectSystem*& System() { return D_0040F4D4; }
static inline EffectRecord* RecordAt(EffectRepository* self, unsigned i) {
    if (i >= self->primaryCount) return &self->secondary->records[i - self->primaryCount];
    return &self->primary->records[i];
}
static inline EffectInstance* InstanceAt(EffectRepository* self, unsigned i) {
    if (i >= self->primaryCount) return self->secondary->instances[i - self->primaryCount];
    return self->primary->instances[i];
}
static inline unsigned RecordCount(EffectRepository* self) { return self->primaryCount + self->secondaryCount; }

#ifdef NON_MATCHING
using namespace Graphics;
using namespace Game;
extern "C" {
extern unsigned func_003107E0(void *,int,int,int);
extern void func_00319DE0(Voice *,int);
extern unsigned func_002851E0(AudioProvider *);
extern void func_00310640(void *,int,int,unsigned);
extern void func_00310590(void *,int,int,const Point3 *);
extern void func_003106F0(void *,int,int,float);
extern void func_003105E8(void *,int,int,int);
}
// Unmatched: 51 differences: flag helper and state/control-flow lifetimes.
float AudioProvider::Transition()
{
    switch(state){case 1:{
        if(count<5){
            bool pending=true;
            if(flags&0x80){if(!(flags&0x100))pending=false;}
            else pending=(voice->flags&2)!=0;
            if(pending){unsigned char old=count++;return 1.0f-(float)old/5.0f;}
            state=2;count=0;flags&=0xfff7;return 1.0f;
        }
        Voice *current=voice;
        if(current->active){
            flags|=8;
            unsigned result;
            if(!current->channel||(current->flags&2)==0)result=voice->playback;
            else result=func_003107E0(current->channel,9,2,0);
            current->playback=result;savedPlayback=result;
            func_00319DE0(voice,0);
        }
        count=0;state=2;return 0.0f;
    }
    case 2:return 0.0f;
    case 3:{
        if(flags&8){
            if(!count){func_00319DE0(voice,1);voice->playback=savedPlayback;
                if(voice->channel)func_00310640(voice->channel,9,1,savedPlayback);savedPlayback=0;}
            if(count<5){if(func_002851E0(this)){unsigned char old=count++;return (float)old/5.0f;}count=0;}else count=0;
            state=0;return 1.0f;
        }
        state=0;
    }
    }return 1.0f;
}
// Unmatched: 9 differences: floating register allocation and scheduling.
void AudioProvider::SetGain(float value)
{
    voice->gain=(int)(value*255.0f);
    if(voice->channel)func_003106F0(voice->channel,13,1,value);
}
// Unmatched: 9 differences: floating register allocation and scheduling.
void AudioProvider::SetPan(float value)
{
    voice->pan=(int)(value*127.0f);
    if(voice->channel)func_003106F0(voice->channel,12,1,value);
}
// Unmatched: 2 differences: NOP and branch displacement.
void AudioProvider::SetPlayback(unsigned value)
{
    voice->playback=value;
    if(voice->channel)func_00310640(voice->channel,9,1,value);
}
// Unmatched: 3 differences: result-register lifetime.
bool AudioProvider::IsStopped()
{
    bool result=false;
    if((((unsigned char *)&flags)[0]&1)==0)result=func_002851E0(this)==0;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00284688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002849C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00284A10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00284AE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00388DD8);
#endif

extern "C" {
void func_003105E8(void *, int, int, int);

void func_00284B28(Graphics::AudioProvider *self, int value) {
    int enabled = value != 0;
    if (enabled) self->voice->flags |= 4;
    else self->voice->flags &= 0xFB;
    if (self->voice->channel != 0) {
        func_003105E8(self->voice->channel, 10, 1, enabled);
    }
    if (value) self->flags |= 0x80;
    else self->flags &= 0xFF7F;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00286CA8);
extern "C" void func_00286DB8(RelocatableTable* self) {
    func_00272730(self);
    for (int i = 0; i < self->count; i++) {
        RelocatableRecord* record = self->records[i];
        record->first += (unsigned)self;
        record->second += (unsigned)self;
        func_00286CA8((void*)record->second);
    }
}
extern "C" void func_00287D08(RelocatableEffect* self) {
    func_00287600(self);
    if (self->field08) self->field08 += (unsigned)self;
    if (self->field0c) self->field0c += (unsigned)self;
    if (self->field10) self->field10 += (unsigned)self;
    if (self->field14) self->field14 += (unsigned)self;
}
extern "C" void func_00287D70(RelocatableEffect* self) {
    func_00287618(self);
    if (self->field20) self->field20 += (unsigned)self;
    if (self->field24) self->field24 += (unsigned)self;
    if (self->field28) self->field28 += (unsigned)self;
    if (self->field2c) self->field2c += (unsigned)self;
    if (self->field30) self->field30 += (unsigned)self;
    if (self->field34) self->field34 += (unsigned)self;
}
extern "C" void func_00287DF8(RelocatableEffect* self) {
    func_00287618(self);
    if (self->field20) self->field20 += (unsigned)self;
}
extern "C" void func_00287E30(RelocatableEffect* self) {
    func_00287618(self);
    if (self->field20) self->field20 += (unsigned)self;
}
extern "C" void func_00287E88(RelocatableEffect* self) {
    if (self->field30) self->field30 += (unsigned)self;
}
extern "C" void func_00287EC8(RelocatableEffect* self) {
    func_00287618(self);
    if (self->field20) self->field20 += (unsigned)self;
    if (self->field24) self->field24 += (unsigned)self;
    if (self->field28) self->field28 += (unsigned)self;
    if (self->field2c) self->field2c += (unsigned)self;
    if (self->field30) self->field30 += (unsigned)self;
    if (self->field34) self->field34 += (unsigned)self;
    if (self->field38) self->field38 += (unsigned)self;
    if (self->field3c) self->field3c += (unsigned)self;
    if (self->field40) self->field40 += (unsigned)self;
    if (self->field44) self->field44 += (unsigned)self;
    if (self->field48) self->field48 += (unsigned)self;
    if (self->field4c) self->field4c += (unsigned)self;
    if (self->field50) self->field50 += (unsigned)self;
    if (self->field54) self->field54 += (unsigned)self;
    if (self->field58) self->field58 += (unsigned)self;
    if (self->field5c) self->field5c += (unsigned)self;
    if (self->field60) self->field60 += (unsigned)self;
    if (self->field64) self->field64 += (unsigned)self;
    if (self->field68) self->field68 += (unsigned)self;
}
extern "C" void func_00288020(RelocatableEffect* self) {
    func_00287618(self);
    if (self->field20) self->field20 += (unsigned)self;
    if (self->field24) self->field24 += (unsigned)self;
    if (self->field28) self->field28 += (unsigned)self;
}
extern "C" void func_00288078(RelocatableEffect* self) {
    func_00287618(self);
    if (self->field20) self->field20 += (unsigned)self;
    if (self->field24) self->field24 += (unsigned)self;
}
extern "C" void func_002880C0(RelocatableEffect* self) {
    func_00287618(self);
    if (self->field20) self->field20 += (unsigned)self;
    if (self->field24) self->field24 += (unsigned)self;
}
extern "C" void func_00288108(RelocatableEffect* self) {
    func_00287618(self);
    if (self->field20) self->field20 += (unsigned)self;
    if (self->field24) self->field24 += (unsigned)self;
}
extern "C" void func_00288150(RelocatableEffect* self) {
    func_00287618(self);
    if (self->field20) self->field20 += (unsigned)self;
    if (self->field24) self->field24 += (unsigned)self;
    if (self->field28) self->field28 += (unsigned)self;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002881A8);
extern "C" void func_00288470(unsigned* self) {
    if (self[1]) self[1] += (unsigned)self;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00289DD0);
extern "C" SmallEffect* func_00289EC8(void) {
    SmallEffect* self = (SmallEffect*)KaimAllocate(sizeof(SmallEffect));
    self->vtable = D_003E29F0;
    return self;
}
extern "C" int func_00289F30(EffectGraph* self, unsigned char* values, unsigned long* rows, void* other,
                             void* context) {
    self->rows = rows;
    self->values = values;
    self->cursor = (unsigned char*)self + 0x20e;
    self->other = other;
    self->context = context;
    self->pending.Reset();
    self->history.Reset();
    self->unknown172c = 0;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00289F78);
extern "C" int func_0028A368(EffectGraph* self, unsigned char start, unsigned char end, unsigned depth) {
    if (start == end || start == 64) return 1;
    unsigned long target = (unsigned long)1 << end;
    unsigned long previous = 0;
    unsigned long current = Collect(self, self->rows[start]);
    for (unsigned i = 1; i < depth && previous != current; i++) {
        if (current & target) return 1;
        previous = current;
        current = Collect(self, current);
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028A470);
extern "C" unsigned char func_0028A478(EffectGraph* self) {
    for (unsigned char i = 0; i < 63; i++) {
        if (!((unsigned char)(self->rows[i] >> i) & 1)) {
            self->rows[i] = (unsigned long)1 << i;
            return i;
        }
    }
    return 255;
}
extern "C" void func_0028A4D8(EffectGraph* self, unsigned char index) {
    unsigned long mask = ~((unsigned long)1 << index);
    for (unsigned char i = 0; i < 63; i++) self->rows[i] &= mask;
}
extern "C" void func_0028A520(EffectGraph* self) {
    for (unsigned char i = 0; i < 63; i++) {
        if (self->rows[i] & ((unsigned long)1 << 63)) func_0028A4D8(self, i);
    }
}
extern "C" unsigned char func_0028A598(void* self, EffectInstance* item) {
    EffectObject* object = Object(item);
    if (object) return Enabled(object, item);
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028A688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028AFF8);
extern "C" void func_0028B1F0(EffectGraph* self, EffectInstance* item) {
    EffectParameter* source = Source(item);
    EffectParameter* target = Target(item);
    unsigned char from = self->values[source->offset];
    unsigned char to = self->values[target->offset];
    self->rows[from] |= (unsigned long)1 << to;
}
extern "C" void func_0028B2A8(EffectGraph* self, EffectInstance* item) {
    EffectParameter* source = Source(item);
    EffectParameter* target = Target(item);
    unsigned char from = self->values[source->offset];
    unsigned char to = self->values[target->offset];
    if (func_0028A368(self, from, to, 63)) {
        self->rows[from] |= (unsigned long)1 << 63;
        self->rows[to] |= (unsigned long)1 << 63;
        self->history.writeIndex = (self->history.writeIndex + 1) & 31;
        self->history.entries[self->history.writeIndex] = item;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028B3E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028B3E8);
extern "C" int func_0028B638(EffectGraph* self, EffectParameter* from, EffectParameter* to, unsigned maskIndex,
                             unsigned depth) {
    unsigned long* saved = self->rows;
    self->cache = *(EffectGraphRows*)saved;
    self->rows = self->cache.rows;
    unsigned long mask = (unsigned long)1 << maskIndex;
    EffectRepository* repository = System()->repository;
    for (unsigned i = 0; i < RecordCount(repository); i++) {
        EffectRecord* record = RecordAt(repository, i);
        if (record->mask & mask) {
            EffectInstance* item = InstanceAt(repository, i);
            EffectParameter* source = Source(item);
            unsigned char start = self->values[source->offset];
            EffectParameter* target = Target(item);
            unsigned char end = self->values[target->offset];
            self->rows[start] |= (unsigned long)1 << end;
        }
    }
    int result = func_0028A368(self, self->values[from->offset], self->values[to->offset], depth);
    self->rows = saved;
    return result;
}
struct SelectionEntry {
    short unknown00, priority;
    unsigned char kind, unknown05;
};
struct SelectionTable {
    char unknown00[12];
    unsigned short count, unknown0e;
    SelectionEntry* entries;
};
struct RandomState {
    unsigned first, second;
    inline unsigned Next() {
        unsigned next = (first << 16) + ((int)first >> 16) + second;
        first = next;
        second += next;
        return first;
    }
};
extern RandomState D_0040EB30;
static inline unsigned RandomWord() { return D_0040EB30.Next(); }
static inline int RandomChoice(int low, int high) {
    float minimum = (float)low;
    float maximum = (float)high + 1.0f - 0.0000152587890625f;
    unsigned next = RandomWord();
    float random = (float)next * 2.3283064365386963e-10f;
    float span = maximum - minimum;
    return (int)(minimum + span * random);
}
extern "C" SelectionEntry* func_0028BD80(SelectionTable* self, int kind) {
    int best = 0x7fffffff;
    SelectionEntry* result = 0;
    for (unsigned i = 0; i < self->count; i++) {
        bool haveBest = best <= 0x7ffffffe;
        if (self->entries[i].priority == 0 && haveBest && RandomChoice(0, 1) == 0) continue;
        SelectionEntry* entry = (SelectionEntry*)(i * sizeof(SelectionEntry) + (unsigned)self->entries);
        if (best >= entry->priority && entry->kind == kind) {
            best = entry->priority;
            result = entry;
        }
    }
    return result;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028BEB8);
extern "C" void func_0028BEC0(ResourceLookup* self) {
    int i;
    if (self->results) self->results = (ResourceResult*)((unsigned)self->results + (unsigned)self);
    if (self->keys) self->keys = (void**)((unsigned)self->keys + (unsigned)self);
    if (self->kinds) self->kinds = (signed char*)((unsigned)self->kinds + (unsigned)self);
    for (i = 0; i < self->count; i++) func_001AD098(&self->results[i]);
    for (i = 0; i < self->count; i++) {
        if (self->keys[i]) self->keys[i] = (void*)((unsigned)self->keys[i] + (unsigned)self);
    }
}
extern "C" ResourceResult* func_0028BF90(ResourceLookup* self, const char* name) {
    for (int i = 0; i < self->count; i++) {
        if (func_001AD2E8(self->keys[i], self->kinds[i], name)) return self->results + i;
    }
    return 0;
}
extern "C" void func_0028C028(RelocatableResourceE0* self) {
    if (self->offset) self->offset += (unsigned)self;
}
extern "C" void func_0028EED8(RelocatableResource* self) {
    ResourceProperties* properties = &self->properties;
    if (self->field00) self->field00 += (unsigned)self;
    if (self->field04) self->field04 += (unsigned)self;
    if (self->field08) self->field08 += (unsigned)self;
    if (self->entries) self->entries = (ResourceEntries*)((unsigned)self->entries + (unsigned)self);
    properties->Relocate(self);
    unsigned i;
    unsigned* link = self->links;
    for (i = 0; i < 7; i++, link++)
        if (*link) self->links[i] = *link + (unsigned)self;
    unsigned count = self->entries->count;
    char* cursor = (char*)self->entries->entries;
    for (i = 0; i < count; i++) {
        cursor += 0x30;
        ResourceEntryProperty* property = (ResourceEntryProperty*)cursor;
        property->offset += (unsigned)self;
        cursor += sizeof(ResourceEntryProperty);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299038);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002991B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002992C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299450);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299500);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002995B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002996B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002997B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299850);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299900);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002999E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299BA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299C70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299D90);
#ifdef NON_MATCHING
// Unmatched: branch joins and loop alignment differ with the Sony C compiler.
// Partial decoder view; names and unobserved fields are UNVERIFIED.
struct DecodeViewDraft {
    char unknown00[0x14c];
    int state;
    char unknown150[0x34];
    int kind, enabled;
    char unknown18c[8];
    int option;
    char unknown198[4];
    int first[3], second[3];
};
extern "C" int func_00298B78(DecodeViewDraft*, int);
extern "C" void func_0029B1D0(DecodeViewDraft* self) {
    int count;
    if (self->state) {
        if (self->option) count = self->enabled ? 3 : 2;
        else count = 1;
    } else {
        if (self->kind == 3) count = self->option ? 3 : 2;
        else count = 1;
    }
    for (int i = 0; i < count; i++) {
        self->first[i] = func_00298B78(self, 0x10);
        func_00298B78(self, 1);
        self->second[i] = func_00298B78(self, 0x10);
        func_00298B78(self, 1);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029B1D0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029B558);
#ifdef NON_MATCHING
// Unmatched: six instruction-order differences with the Sony compiler; this unit uses the SN compiler.
// Partial socket and RPC buffer views; field meanings are UNVERIFIED.
struct SocketParamsDraft {
    int a, b, c, d, e;
    unsigned char name[16];
};
struct RpcBufferDraft {
    int a, b, c, d, e;
    unsigned char name[16];
    int result, arg1, arg2;
};
extern int D_003C1570, D_00445D80;
extern char D_004438C0[];
extern RpcBufferDraft D_004439C0;
extern "C" int func_0036B100(void*, unsigned, int, void*, int, void*, int, int, int);
extern "C" int func_003678A0(int);
extern "C" int func_00367880(int);
extern "C" void func_0029C110(const char*, ...);
extern "C" int func_0029B868(SocketParamsDraft* params, int arg1, int arg2) {
    if (!D_003C1570) return 0;
    func_003678A0(D_00445D80);
    RpcBufferDraft* buf = &D_004439C0;
    buf->a = params->a;
    buf->arg1 = arg1;
    buf->arg2 = arg2;
    buf->b = params->b;
    buf->c = params->c;
    buf->d = params->d;
    buf->e = params->e;
    for (int i = 0; i < 16; ++i) buf->name[i] = params->name[i];
    if (func_0036B100(D_004438C0, 0x80001301, 0, &D_004439C0, 0x90, &D_004439C0, 0x90, 0, 0) < 0) {
        func_0029C110("sceDbcCreateSocket: rpc error\n");
        func_00367880(D_00445D80);
        return 0;
    }
    int result = buf->result;
    func_00367880(D_00445D80);
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029B868);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029BCC0);
#ifdef NON_MATCHING
// Unmatched: control-flow joins and register allocation differ with the Sony compiler.
// Buffer and client field meanings are UNVERIFIED.
struct RpcRequestDraft {
    int a, b, count;
    unsigned char bytes[0x80];
    char padding[0x34];
};
struct RpcClientDraft {
    char data[0x28];
};
extern int D_00445D80, D_003C1574;
extern RpcRequestDraft D_00445B40[2];
extern RpcClientDraft D_00443938[2];
extern "C" int func_003678A0(int);
extern "C" int func_00367880(int);
extern "C" int func_0036B300(void*);
extern "C" int func_0036B100(void*, unsigned, int, void*, int, void*, int, int, int);
extern "C" void func_0029C110(const char*, ...);
extern "C" int func_0029BCE0(int a, unsigned command, int* count, const unsigned char* data) {
    if (*count > 0x80) {
        func_0029C110("libdbc: SendData2 data length too long [%d]\n", *count);
        return 0;
    }
    func_003678A0(D_00445D80);
    D_003C1574++;
    if (D_003C1574 >= 2) D_003C1574 = 0;
    RpcRequestDraft* buf = &D_00445B40[D_003C1574];
    buf->a = a;
    buf->b = command;
    buf->count = *count;
    for (int i = 0; i < *count; i++) buf->bytes[i] = data[i];
    if (func_0036B300(&D_00443938[D_003C1574]) == 1) {
        func_0029C110("dbcman : SendData2 BUSY\n");
        func_00367880(D_00445D80);
        return 0;
    }
    if (func_0036B100(&D_00443938[D_003C1574], command, 1, &D_00445B40[D_003C1574], 0x90, &D_00445B40[D_003C1574], 0x90,
                      0, 0) < 0) {
        func_0029C110("sceDbcSendData2: rpc error\n");
        func_00367880(D_00445D80);
        return 0;
    }
    func_00367880(D_00445D80);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029BCE0);
#endif
#ifdef NON_MATCHING
// Unmatched: the buffer-index addition has reversed operands under the Sony compiler.
struct SendBufferDraft {
    int a, b, count;
    unsigned char bytes[0x2080];
};
extern char D_00443910[];
extern SendBufferDraft D_00443A80;
extern int D_00445D80;
extern "C" int func_003678A0(int);
extern "C" int func_00367880(int);
extern "C" int func_0036B300(void*);
extern "C" int func_0036B100(void*, unsigned, int, void*, int, void*, int, int, int);
extern "C" void func_0029C110(const char*, ...);
extern "C" int func_0029BE90(int a, int b, int* count, const unsigned char* bytes, int callback) {
    if (*count > 0x2080) {
        func_0029C110("libdbc: SendData3 data length too long [%d]\n", *count);
        return 0;
    }
    func_003678A0(D_00445D80);
    if (func_0036B300(D_00443910) == 1) {
        func_0029C110("dbcman : SendData3 BUSY\n");
        func_00367880(D_00445D80);
        return 0;
    }
    D_00443A80.a = a;
    D_00443A80.b = b;
    D_00443A80.count = *count;
    for (int i = 0; i < *count; i++) D_00443A80.bytes[i] = bytes[i];
    if (func_0036B100(D_00443910, 0x8000131c, 1, &D_00443A80, 0x2090, &D_00443A80, 0x2090, callback, 0) < 0) {
        func_00367880(D_00445D80);
        return 0;
    }
    func_00367880(D_00445D80);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029BE90);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029D4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A7930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A7B18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A7BB0);
#ifdef NON_MATCHING
// Unmatched: floating-point register allocation and instruction scheduling differ.
struct EffectVector3 {
    float x, y, z;
};
struct EffectMatrixRows {
    float row[3][4];
};
extern "C" EffectVector3* func_002A7D50(EffectVector3* out, const EffectVector3* v, const EffectMatrixRows* m) {
    float x = v->x, y = v->y, z = v->z;
    float ax = x * m->row[0][0], ay = x * m->row[0][1], az = x * m->row[0][2];
    float bx = y * m->row[1][0], by = y * m->row[1][1], bz = y * m->row[1][2];
    float cx = z * m->row[2][0], cy = z * m->row[2][1], cz = z * m->row[2][2];
    float rx = cx + (ax + bx), ry = cy + (ay + by), rz = cz + (az + bz);
    out->x = rx;
    out->y = ry;
    out->z = rz;
    return out;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A7D50);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A7DD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A8688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A8860);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A8DA0);
extern "C" void func_002AF778(EffectAttachment* self, EffectOwner* owner) {
    if (self->owner) {
        EffectLink* previous = self->link.previous;
        EffectLink* next = self->link.next;
        previous->next = next;
        next->previous = previous;
    }
    self->owner = owner;
    if (owner) {
        EffectLink* first = owner->links.next;
        first->previous = &self->link;
        self->link.previous = &owner->links;
        owner->links.next = &self->link;
        self->link.next = first;
        func_002AA288(owner);
    }
}
// Partial resource view; the surrounding layout and field meanings are UNVERIFIED.
struct ResourceAccessView {
    char unknown00[8];
    int value;
    char unknown0c[0x15];
    unsigned char flags21, flags22, flags23;
};
extern "C" void func_002CD640(ResourceAccessView*);
extern "C" int func_002C0340(int* out, ResourceAccessView* resource, unsigned flags) {
    if (resource->flags23 & 0x60) {
        if (!(resource->flags21 & 0x80)) {
            if ((flags & 1) && !(resource->flags21 & 0x40)) func_002CD640(resource);
            *out = resource->value;
            if (flags & 1) resource->flags22 |= 0x10;
            if (flags & 2) resource->flags22 |= 8;
            return 1;
        }
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C03F8);
#ifdef NON_MATCHING
// Unmatched: GP-relative access and branch layout differ under -G8.
struct ResourceQueryDraft {
    char unknown00[4];
    int valid;
    char unknown08[0x1b];
    unsigned char flags23;
};
extern unsigned D_0040E688;
extern "C" int func_002C04F8(int* out, ResourceQueryDraft* resource) {
    unsigned char* ptr = (unsigned char*)((unsigned)resource + D_0040E688);
    if (resource->valid) {
        if (resource->flags23 & 0x80) {
            if (ptr)
                *out = 1 + (ptr[0x16] >> 2);
            else
                *out = 1;
        } else
            *out = 1;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C04F8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C0558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C05F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C0670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C06D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C0760);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C07B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C66A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C6828);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C7760);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C7C20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C7FB0);
#ifdef NON_MATCHING
// Unmatched: byte-load ordering and register allocation differ.
extern "C" int func_002C8438(unsigned* out, const unsigned char* in, int type) {
    switch (type & 0xf00) {
    case 0:
    case 0x100:
        *out = ((in[2] << 7) & 0x7c00) | ((in[1] << 2) & 0x3e0) | (in[0] >> 3) | ((in[3] << 8) & 0x8000);
        break;
    case 0x500:
        *out = (in[2] << 16) | (in[1] << 8) | in[0] | ((in[3] * 0x808081u) & 0xff000000u);
        break;
    case 0x600:
        *out = in[0] | ((in[1] << 8) | 0x80000000u) | (in[2] << 16);
        break;
    default: return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C8438);
#endif
#ifdef NON_MATCHING
// Unmatched: byte stores are scheduled in a different order.
extern "C" int func_002C8530(unsigned char* out, const unsigned* in, int type) {
    unsigned value = *in;
    switch (type & 0xf00) {
        case 0:
        case 0x100:
            out[2] = (value >> 7) & 0xf8;
            out[1] = (value >> 2) & 0xf8;
            out[0] = value << 3;
            if (value & 0x8000)
                out[3] = 0xff;
            else
                out[3] = 0;
            break;
        case 0x500:
            out[2] = value >> 16;
            out[1] = value >> 8;
            out[0] = value;
            out[3] = (value & 0xff000000u) / 0x808080u;
            break;
        case 0x600: {
            unsigned b = value >> 16;
            unsigned g = value >> 8;
            out[1] = g;
            out[3] = 0xff;
            out[2] = b;
            out[0] = value;
        } break;
        default: return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C8530);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C8618);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CB3D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CB660);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CB858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CBA90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CBDF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CC700);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CCC48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CCD48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CCE80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CD230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CD640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CD840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CDB28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CDD70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CDEA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CDF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CE010);
// Partial global state view; its class and unobserved fields are UNVERIFIED.
struct EffectGlobalState {
    int flag;
    char unknown04[20];
    int state;
};
extern EffectGlobalState D_003C4080;

extern "C" int func_002CE0B8(unsigned value) {
    if (D_003C4080.state == -1) {
        D_003C4080.flag = value < 1;
        return 1;
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CE0E8);
