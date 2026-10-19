#ifndef BLACK_CAMPAIGN_GRAPH_PATH_OBJECT_HPP
#define BLACK_CAMPAIGN_GRAPH_PATH_OBJECT_HPP
#include "campaign/graph/tables.hpp"
#include "classes/kynapse/Kaim_CPathObject.hpp"
#include "classes/kynapse/Kaim_CPathObject_CLinkedEdge.hpp"
namespace Kaim {
struct PathClassInfo { unsigned char unknown00[0x108]; PathClassInfo *parent; };
struct PathPropertyBag;
struct PathPropertySlot { int index; PathPropertyBag *bag; };
struct PathPropertyBag {
 unsigned char unknown00[0x50]; void **values;
 unsigned char unknown54[8]; PathPropertySlot primary;
 unsigned char unknown64[0x30]; void *primaryValue;
};
inline void *GetPathSlot(PathPropertySlot *slot) {
 PathPropertyBag *bag=slot->bag;
 if(slot==&bag->primary)return bag->primaryValue;
 if(bag->values)return bag->values[slot->index];
 return 0;
}
inline bool HasPathSlot(PathPropertySlot *slot) { return GetPathSlot(slot)!=0; }
inline void SetPathSlot(PathPropertySlot *slot,void *value) {
 PathPropertyBag *bag=slot->bag;
 if(slot==&bag->primary)bag->primaryValue=value;
 else if(bag->values)bag->values[slot->index]=value;
}
struct PathTypeEntry { unsigned char unknown00[0x84];int typeId;unsigned char mirrored; };
struct PathTypeRegistry {
 unsigned char unknown00[4];PathTypeEntry **entries;unsigned int count;
 bool HasId(int) __asm__("func_002F3208");
};
// Callback prefix and slot 2 are verified by the matched forwarding method.
struct PathCallback {
 virtual void Slot0(); virtual void Slot1();
 virtual unsigned int Filter(unsigned int,unsigned int,unsigned int);
};
struct CEntity : CObject {
 virtual ~CEntity();
 virtual bool Init(ChildBuffers *);
 virtual void Slot2();
 virtual PathClassInfo *GetClassInfo();
 virtual void Slot4();
 unsigned char unknown04[0x5c];
};
struct CPathObject : CEntity {
 struct CLinkedEdge : CObject {
  CLinkedEdge():id(0),slot(0),previous(0) {}
  virtual ~CLinkedEdge();
  static void *operator new[](unsigned int size) { return Allocate(size); }
  static void operator delete[](void *p) { D_003C87E0(p); }
  int id;PathPropertySlot *slot;void *previous;
 };
 virtual ~CPathObject();
 virtual bool Init(ChildBuffers *);
 virtual unsigned int Slot5(unsigned int,unsigned int,PathCallback*,unsigned int);virtual void Slot6();virtual void Slot7();virtual void Slot8();virtual void Slot9();
 virtual void Notify(void *);
 virtual void Slot11();virtual void Slot12();virtual void Slot13();
 virtual bool Claim(int,PathPropertySlot *);
 virtual bool Release(int,PathPropertySlot *);
 virtual void Replay();
 virtual void OnRelease(int,PathPropertySlot *);
 virtual void OnType(int);
 CLinkedEdge *elements;
 unsigned int elementCount;
 void *listeners;
 unsigned int capacity;
};
#define PATH_OFFSET(type,member,offset) typedef char type##_##member##_offset[(unsigned int)&((type*)0)->member==offset?1:-1]
PATH_OFFSET(CPathObject,elements,0x60);
PATH_OFFSET(CPathObject,elementCount,0x64);
PATH_OFFSET(CPathObject,listeners,0x68);
PATH_OFFSET(CPathObject,capacity,0x6c);
typedef char LinkedEdge_id_offset[(unsigned int)&((CPathObject::CLinkedEdge*)0)->id==4?1:-1];
#undef PATH_OFFSET
// Full base fields, complete allocation sizes and unused virtual signatures are UNVERIFIED.
}
extern "C" void *func_002EC058(void *,const void *);
extern "C" int func_0035E750(const char *);
#endif
