#include "include_asm.h"
#include "game/graphics/audio_provider.hpp"

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

// Partial parameter, graph and attachment access views; original class identities are UNVERIFIED.
struct EffectParameter {
    unsigned offset;
    char unknown04[16];
};
struct EffectDefinition;
struct EffectInstance {
    unsigned index;
    EffectDefinition* definition;
};
struct EffectDefinition {
    char unknown00[24];
    EffectParameter* parameters;
    char unknown1c[28];
    unsigned *sourceIndices, *targetIndices;
    char unknown40[28];
    EffectInstance embedded;
    EffectParameter sourceDefault, targetDefault;
};
struct EffectGraph {
    unsigned unknown00;
    unsigned char* values;
    unsigned long* rows;
    char unknown0c[0x1698];
    EffectInstance* history[32];
    unsigned unknown1724, writeIndex;
};
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00289EC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00289F30);
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028A598);
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
        self->writeIndex = (self->writeIndex + 1) & 31;
        self->history[self->writeIndex] = item;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028B3E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028B3E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028B638);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028BD80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028BEB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028BEC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0028BF90);
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_00299EA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029B1D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029B500);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029B558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029B7F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029B868);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029B998);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029BA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029BBC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029BCC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029BCE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029BE90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029BFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029C110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_0029D4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A7930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A7B18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A7BB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002A7D50);
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C0340);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C03F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C04F8);
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C8438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002C8530);
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CE0B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_281388_284688", func_002CE0E8);
