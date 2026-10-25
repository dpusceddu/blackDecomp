// PS2 graph-manager views. RTTI supplies hierarchy/slot order; matched users
// verify the accessed prefixes. Complete base fields and unused signatures remain UNVERIFIED.
#ifndef BLACK_GRAPH_MANAGER_HPP
#define BLACK_GRAPH_MANAGER_HPP
#include "kynapse/classes/Kaim_CGraphManager.hpp"
#include "kynapse/graph/spatial.hpp"
#include "kynapse/property.hpp"
extern "C" char *func_0035D1A0(char*,const char*,unsigned int);
extern "C" int func_0035E750(const char*);
// The matched Configure consumer verifies the software-double ABI of the executable.
extern "C" double GraphAtof(const char*) __asm__("func_0035E730");
extern "C" bool func_002ECB80(unsigned int);
namespace Kaim {
struct GraphConfig {
 unsigned char unknown00[12]; char *first; unsigned char unknown10[16]; unsigned int count;
 const char *GetSecond() __asm__("func_002E3920");
 const char *GetValue() __asm__("func_002E3918");
 GraphConfig *FindBySecond(const char*) __asm__("func_002E31E0");
 const char *FindThirdBySecond(const char*) __asm__("func_002E3330");
 GraphConfig *GetChild(unsigned int) __asm__("func_002E33E0");
};
struct AdditionalEntry {unsigned char unknown00[4]; CGraphData *(*create)(void*);};
extern "C" AdditionalEntry *func_00390CF8(const char*);
struct CWorldService : CObject { virtual bool Setup(GraphConfig*);virtual bool Configure(GraphConfig*);virtual void Slot3();virtual void Slot4();virtual void *GetClassInfo();};
struct CGraphManager : CWorldService {
 struct CGraphMap : CObject {
  char name[0x80];CSpatialGraph *graph;unsigned char update;unsigned char unknown89[3];CGraphData *additional[32];int additionalCount;
  CGraphMap(const char*,CSpatialGraph*,unsigned char);
  virtual ~CGraphMap();
  static void *operator new(unsigned int n){return Allocate(n);}
 };
 virtual ~CGraphManager();
 virtual bool Setup(GraphConfig*);
 virtual bool Configure(GraphConfig*);
 virtual void Slot3();virtual void Slot4();virtual void *GetClassInfo();
 CGraphMap **items;unsigned int count,capacity;bool searchConfigured;
 CGraphManager();
 CGraphMap *LoadGraph(const char*,GraphConfig*,unsigned char) __asm__("func_002F28F8");
 bool AddGraph(const char*,CSpatialGraph*,unsigned char) __asm__("func_002F2BF8");
 bool RemoveGraph(const char*) __asm__("func_002F2FF0");
 bool ConfigureAll(GraphConfig*) __asm__("func_002E74E0");
 inline CSpatialGraph *FindGraph(const char*name){for(unsigned int i=0;i<count;++i){if(!_stricmp(name,items[i]->name))return items[i]->graph;}return 0;}
};
}


#define MANAGER_OFFSET(type, member, offset) typedef char type##_##member##_offset[(unsigned int)&((Kaim::type*)0)->member==offset?1:-1]
MANAGER_OFFSET(CGraphManager,items,4);
MANAGER_OFFSET(CGraphManager,count,8);
MANAGER_OFFSET(CGraphManager,capacity,12);
MANAGER_OFFSET(CGraphManager,searchConfigured,16);
#undef MANAGER_OFFSET
#endif
