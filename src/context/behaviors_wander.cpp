#include "context/behaviors/wander.hpp"
namespace Kaim {
bool WanderAgent::Update()
{
    bank->ClearActivation();
    if (!pending)
        return false;
    bool ok;
    if (index != 0xffffffffU) {
        FollowQuery query(vector, fieldC, fieldD);
        ok = provider->QueryTransform(&query);
    } else {
        ok = provider->Query(&vector);
    }
    if (ok) {
        bank->Select(provider->id);
        reached = provider->IsActive();
        if (reached) Refresh();
        return true;
    }
    Refresh();
    reached=false;
    return true;
}


WanderAgent* WanderAgent::Create(BehaviorContext* context) { return new WanderAgent(context); }

WanderAgent::WanderAgent(BehaviorContext* c):Behavior(c),index(0xffffffffU),fieldC(0x7fffffff),fieldD(0xffffffffU) { pending=0;provider=0; }
}
namespace Kaim {
struct GraphEntry { int unused; char name[0x80]; void* graph; };
struct GraphRegistry { int unused; GraphEntry** entries;unsigned count;
    int FindId(const char* name) __asm__("func_002F2F58");
};
struct SlotLookup : PolyRoot {
    virtual ~SlotLookup();
    virtual void Slot1();virtual void Slot2();virtual void Slot3();virtual void Slot4();virtual void Slot5();
    virtual bool Lookup(const char*,unsigned*);
};
struct RegistryView {
    GraphRegistry* FindRegistry(ClassInfo*) __asm__("func_002EC058");
    SlotLookup* FindLookup(ClassInfo*) __asm__("func_002EC058");
};
extern RegistryView* gWanderEngine;
extern ClassInfo gTypeRegistryClass,gLookupClass;
struct NavNode { int id; Vec3 position; int unused; };
struct NodeBank {
    unsigned char unknown[12];unsigned capacity;int unused;unsigned liveCount;NavNode* nodes;
    NavNode* NodeAt(unsigned ordinal) {if(ordinal>=capacity)return 0;NavNode*node=&nodes[ordinal];return node->id==-1?0:node;}
};
bool WanderAgent::Start() {
    if(!pending)return false;
    if(fieldC==0x7fffffff)Refresh();
    return true;
}
// Unmatched: Pick retains four register-allocation operand differences.

void WanderAgent::SetType(int id) {
    pending=(void*)id;
    index=0xffffffffU;
    GraphRegistry* registry=gWanderEngine->FindRegistry(&gTypeRegistryClass);
    if(registry) {
        SlotLookup* lookup=gWanderEngine->FindLookup(&gLookupClass);
        if(lookup)for(unsigned i=0;i<registry->count;++i) {
            if(registry->entries[i]->graph==pending) {
                if(!lookup->Lookup(registry->entries[i]->name,&index))index=0xffffffffU;
                return;
            }
        }
    }
}
bool WanderAgent::Configure(ChildBuffers* property) {
    if(!property)return false;
    if(!_stricmp(property->GetSecond(),"Graph")) {
        const char* name=property->GetValue();
        if(name) {
            GraphRegistry* registry=gWanderEngine->FindRegistry(&gTypeRegistryClass);
            if(!registry)return false;
            int id=registry->FindId(name);
            if(!id)return false;
            SetType(id);
            return true;
        }
    }
    return BlackPS2::Kynapse::IsPrivateProperty(property);
}
}
