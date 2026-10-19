// Brain and component prefixes inferred from PS2 access patterns and RTTI.
// Unused component slots and full component layouts remain UNVERIFIED.
#ifndef BLACK_CAMPAIGN_GRAPH_BRAIN_HPP
#define BLACK_CAMPAIGN_GRAPH_BRAIN_HPP
#include "campaign/graph/manager.hpp"
#include "campaign/graph/path_object.hpp"
namespace Kaim {
struct CBrain;
struct BrainComponent : CObject {
 virtual ~BrainComponent();
 virtual bool Configure(GraphConfig*);
 virtual void Slot2(); virtual void Slot3();
 virtual PathClassInfo *GetClassInfo();
};
struct BrainComponentClass {unsigned int unknown00;BrainComponent *(*create)(CBrain*);};
struct BrainHandlerClass {unsigned int unknown00;BrainComponent *(*create)();};
struct BrainRegistry {BrainComponentClass *items[256];int count;};
extern "C" BrainRegistry *func_0038BA30();
extern "C" BrainRegistry *func_0038C3E0();
extern "C" BrainComponentClass *func_0038C438(const char*);
extern "C" BrainComponentClass *func_0038C4D8(const char*);
inline bool BrainIsA(PathClassInfo *wanted,PathClassInfo *info){do {if(wanted==info)return true;info=info->parent;}while(info);return false;}
struct CBrain : CObject {
 CBrain(void*,BrainHandlerClass*);
 virtual ~CBrain();
 virtual void Slot1();
 virtual bool Configure(GraphConfig*);
 virtual bool ConfigureChild(GraphConfig*);
 virtual int Slot4();virtual void Slot5();
 BrainComponent **agents;int agentCount;
 BrainComponent **services;int serviceCount;
 void *owner;BrainComponent *handler;
 BrainComponent *GetAgent(PathClassInfo*) __asm__("func_002E1BC0");
 BrainComponent *FindService(PathClassInfo*) __asm__("func_002E1C58");
 BrainComponent *GetService(PathClassInfo*) __asm__("func_002E1D10");
};
}
#define BRAIN_OFFSET(member,offset) typedef char Brain_##member##_offset[(unsigned int)&((Kaim::CBrain*)0)->member==offset?1:-1]
BRAIN_OFFSET(agents,4);BRAIN_OFFSET(agentCount,8);BRAIN_OFFSET(services,12);BRAIN_OFFSET(serviceCount,16);BRAIN_OFFSET(owner,20);BRAIN_OFFSET(handler,24);
#undef BRAIN_OFFSET
#endif
