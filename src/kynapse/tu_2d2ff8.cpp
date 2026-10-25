#include "kynapse/behaviors/follower_construction.hpp"
#include "kynapse/property.hpp"
#include "kynapse/predicates.hpp"
// Accessed layout and table entries are verified; original registration type is unknown.
// Unmatched: native 648-byte unwind needs one shared recipe; callback extent must be 44 bytes, default emits 48.
struct FollowerVirtualEntry { short adjustment; unsigned short reserved; void (*function)(); };
struct __attribute__((aligned(8))) FollowerRegistrationStorage {
    unsigned char unverified00[0x110];
    FollowerVirtualEntry* classTable;
};
extern "C" {
extern FollowerVirtualEntry D_003E3130[13], D_003E2AE0[];
extern FollowerRegistrationStorage D_0044EDE8;
extern FollowerVirtualEntry* D_0044EEF8;
void* func_002DFF10(void*,FollowerBehavior::Context*);
int func_002DFF98(void*,int);
int func_002E00F0(void*,const char*,FollowerBehavior::Follower* (*)(FollowerBehavior::Context*),int,int,int);
extern int (*D_003C87E0)(void*);
int func_00360838(const char*,const char*);
long func_0035E730(const char*);
float func_00291C68(long);
float func_002E1FD0(float,const FollowerBehavior::Vec3*,void*,FollowerBehavior::Actor*,int);
FollowerBehavior::Vec3 func_002E9E88(const FollowerBehavior::Vec3*);
}
extern "C" FollowerBehavior::Follower* func_002D2FF8(FollowerBehavior::Context* context) {
    return new FollowerBehavior::FollowerConstructible(context);
}
namespace FollowerBehavior {
bool Follower::Configure(ChildBuffers* entry) {
    if (!entry) return false;
    const char* key=entry->GetSecond();
    if (!func_00360838(key,"DistFromEntity")) {
        const char* value=entry->GetValue();
        if (value) {long parsed=func_0035E730(value);Engine* engine=gEngine;limit=func_00291C68(parsed)*engine->unit;return true;}
    } else if (!func_00360838(key,"AngleFromEntity")) {
        const char* value=entry->GetValue();
        if (value) {angle=func_00291C68(func_0035E730(value));return true;}
    } else if (!func_00360838(key,"EntityToFollow")) {
        const char* value=entry->GetValue();
        if (value) {followed=((Registry*)gEngine)->FindByName(value);return true;}
    }
    return Ps2Math::Kynapse::IsPrivateProperty(entry);
}
bool Follower::Init(ChildBuffers* config) {
    arrived=false;position=gOrigin;NameTable* names=GetNames();
    nameIndex=names->FindName("CFollowerAgent::ComputeRealDistance");nextTime=0;
    float t=gEngine->unit;limit=t;distance=t;angle=180.0f;followed=0;
    if (ConfigureAll(config)) {
        target=(TargetEntity*)((Registry*)context)->FindByClass(&gTargetClass);
        property=((PropertyOwner*)context->actor)->GetProperty(&gKey);
        if (!HasTarget())goto failed;
        if (HasName())goto succeeded;
    }
failed:return false;
succeeded:return true;
}
void Follower::Refresh()
{
    if (!(followed->position == lastTarget) || !arrived) {
        if (limit != 0.0f) {
            Vec3 angles(followed->angles);
            angles.y += angle;
            angles.x = 0.0f;
            Vec3 direction = func_002E9E88(&angles);
            ComputeDistance(&direction);
            position = followed->position + (direction * distance);
            lastTarget = followed->position;
            return;
        } else {
            position = followed->position;
            arrived = true;
        }
        lastTarget = followed->position;
    }
}
}
extern "C" {
void func_002D34C0(int enabled,int phase) {
    if (phase == 0xFFFF) {
        if (enabled != 0) {
            func_002E00F0(&D_0044EDE8,"CFollowerAgent",&func_002D2FF8,0,0,0);
            return;
        }
        D_0044EEF8=D_003E2AE0;
    }
}
void* func_002D3520(void* memory,FollowerBehavior::Context* context) {
    func_002DFF10(memory,context);
    FollowerBehavior::Follower* self=(FollowerBehavior::Follower*)memory;
    self->followed=0;
    *(FollowerVirtualEntry**)self=D_003E3130;
    self->target=0;
    self->property=0;
    return self;
}
// The destruction return contract remains unverified; the observable base/free calls are retained.
int func_002D3560(void* self,int flags) {
    int result;
    *(FollowerVirtualEntry**)self=D_003E3130;
    result=func_002DFF98(self,0);
    if (flags & 1) result=D_003C87E0(self);
    return result;
}
}
bool IsSet0C::IsSet() const { if (value != 0) return true; return false; }
bool HasId2C::HasId() const { if (id != -1) return true; return false; }
namespace FollowerBehavior {
bool Follower::IsReady() {
    if (!followed) return false;
    if (limit < 0.0f) return false;
    return true;
}
bool Follower::Update() {
    bank->ClearActivation();Refresh();
    if (followed && target) {if (target->Query(&position))goto selected;return false;}
    return false;
selected:bank->Select(target->id);return true;
    return false;
}
void Follower::ComputeDistance(void* observer) {
    arrived=false;float now=gNow;
    if (nextTime<now) {
        ParameterTables* tables=(ParameterTables*)GetNames();
        if (tables->Consume(nameIndex,context->actor)) {
            float half;
            if (property)half=property->value*0.5f;
            else {float radius=0.0f;if (gEngine)radius=gEngine->unit;half=radius*0.5f;}

            distance=func_002E1FD0(limit+half,&followed->position,observer,followed,2)-half;
            if (distance<=0.0f)distance=0.0f;
            arrived=true;tables->Accumulate(nameIndex,context->actor);nextTime=now+0.1f;
        }
    }
}
}
extern "C" {
void func_002D37D8(FollowerBehavior::Follower* self,float value) {
    float scaled=value*FollowerBehavior::gEngine->unit;
    if(self->limit!=scaled) {self->limit=scaled;self->arrived=false;}
}
void func_002D3810(FollowerBehavior::Follower* self,float value) {
    if(self->angle!=value) {self->angle=value;self->arrived=false;}
}
float func_002D3838(FollowerBehavior::Follower* self) {return self->limit/FollowerBehavior::gEngine->unit;}

}

// Native eight-byte virtual entries; semantic identities of unused slots remain unverified.
extern "C" {
void func_002D35B8();void func_002D35C8();void func_00389480();void func_0038BB28();void func_003894D0();
void func_002D31F0();void func_002D30A0();void func_002D35D8();void func_002D3610();
void func_002D3300();void func_002D36A8();
FollowerVirtualEntry D_003E3130[13] __attribute__((section(".data.follower_vtable"),aligned(8))) = {
    {0,0,func_00389480},{0,0,(void (*)())func_002D3560},{0,0,func_002D31F0},
    {0,0,func_002D30A0},{0,0,func_0038BB28},{0,0,func_003894D0},
    {0,0,func_002D35D8},{0,0,func_002D3610},{0,0,func_002D35B8},
    {0,0,func_002D35C8},{0,0,func_002D3300},{0,0,func_002D36A8},{0,0,0}
};
}
extern "C" {
void func_002D3888() {func_002D34C0(1,0xFFFF);}
void func_002D38A8() {func_002D34C0(0,0xFFFF);}
}

// Image labels, including the table pointer at +0x110, alias this native storage.
extern "C" {FollowerRegistrationStorage Follower_RegistrationStorage __attribute__((aligned(8)));}

