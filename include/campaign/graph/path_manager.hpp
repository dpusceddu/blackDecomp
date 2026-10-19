// PS2 path-object manager prefix. RTTI supplies the hierarchy; exact users verify
// the accessed fields. Unused virtual signatures and complete types remain UNVERIFIED.
#ifndef BLACK_CAMPAIGN_GRAPH_PATH_MANAGER_HPP
#define BLACK_CAMPAIGN_GRAPH_PATH_MANAGER_HPP
#include "campaign/graph/manager.hpp"
#include "campaign/graph/path_object.hpp"
namespace Kaim {
struct PathVector {
 float x,y,z;
 PathVector& operator=(const PathVector& v){x=v.x;y=v.y;z=v.z;return *this;}
};
struct CPointPair : CObject {
 CPointPair() {}
 virtual ~CPointPair();
 PathVector from,to;
 CPointPair& operator=(const CPointPair& p){from=p.from;to=p.to;return *this;}
 static void *operator new[](unsigned int n){return Allocate(n);}
 static void operator delete[](void *p){D_003C87E0(p);}
};
typedef void (*PathListener)(void*,void*);
extern PathListener *pathListenerFunctions __asm__("D_003CBA40");
extern void **pathListenerData __asm__("D_003CBA44");
extern void **pathListenerOwners __asm__("D_003CBA48");
extern unsigned int pathListenerCount __asm__("D_003CBA4C");
extern unsigned int pathListenerCapacity __asm__("D_003CBA50");
extern PathClassInfo pathObjectClass __asm__("D_004524A0");
extern PathClassInfo pathTypeRegistryClass __asm__("D_00452158");
struct CPathObjectManager : CWorldService {
 virtual ~CPathObjectManager();
 virtual bool Setup(GraphConfig*);
 virtual bool Configure(GraphConfig*);
 CPathObject **items;unsigned int count;PathTypeRegistry *registry;unsigned int capacity;
 CPointPair *segments;unsigned int segmentCount;
 unsigned int GetSegments(CPointPair**) __asm__("func_002F4F80");
 bool Add(CPathObject*) __asm__("func_002F51B0");
 bool Remove(CPathObject*) __asm__("func_002F5968");
 void AddListener(PathListener,void*,void*) __asm__("func_002F5348");
 void RemoveListener(PathListener,void*,void*) __asm__("func_002F5A40");
 void NotifyListeners(void*,void*) __asm__("func_002F5AE0");
};
inline bool IsPathObject(PathClassInfo *info){do {if(&pathObjectClass==info)return true;info=info->parent;}while(info);return false;}
}
extern "C" void func_002F5868(Kaim::CPathObject*,Kaim::CPathObjectManager*);
extern "C" void func_002F58E8(Kaim::CPathObject*,Kaim::CPathObjectManager*);
extern "C" void func_002E1058(void*,void*,void*);
extern "C" void func_002E1098(void*,void*,void*);
typedef char PathManagerItemsAt4[(unsigned int)&((Kaim::CPathObjectManager*)0)->items==4?1:-1];
typedef char PathManagerSegmentsAt20[(unsigned int)&((Kaim::CPathObjectManager*)0)->segments==20?1:-1];
typedef char PathPairSize28[sizeof(Kaim::CPointPair)==28?1:-1];
#endif
