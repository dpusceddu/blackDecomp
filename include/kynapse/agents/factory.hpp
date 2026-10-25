// Factory views; class identities and active offsets follow PS2 callers.
#ifndef BLACK_CONTEXT_BEHAVIORS_FACTORY_HPP
#define BLACK_CONTEXT_BEHAVIORS_FACTORY_HPP
#include "kynapse/alloc.hpp"
extern void (*memoryRelease)(void*);
extern "C" unsigned int strlen(const char*);extern "C" char*strcpy(char*,const char*);extern "C" int strcmp(const char*,const char*);extern "C" int sprintf(char*,const char*,...);
namespace KaimFactory {
struct ObjectRoot {virtual ~ObjectRoot() {} static void* operator new(unsigned int n){return KaimAllocate(n);}static void operator delete(void*p){memoryRelease(p);} };
struct Entity;
struct Handler:ObjectRoot {virtual void Slot1();virtual void Slot2();virtual void Detach(Entity*);};
template<class T> struct Node:ObjectRoot {
 T value;Node* previous;Node* next;unsigned char active;
 Node():previous(0),next(0),active(0){}
 static void* operator new[](unsigned int n){return KaimAllocate(n);}static void operator delete[](void*p){memoryRelease(p);}
};
template<class T> struct Iterator:ObjectRoot {
 Node<T>* node;Iterator(Node<T>*p=0):node(p){}virtual ~Iterator(){}
 Iterator(const Iterator&x):node(x.node){}Iterator&operator=(const Iterator&x){node=x.node;return*this;}
};
template<class T> struct List:ObjectRoot {
 Node<T>* storage;Node<T>*head;Node<T>*tail;Node<T>*freeHead;unsigned int activeCount,capacity;
 List(unsigned int n) {head=0;activeCount=0;capacity=n;freeHead=0;storage=0;tail=0;
  if(n){storage=new Node<T>[n];freeHead=storage;storage[0].previous=0;for(unsigned int i=1;i<capacity;++i){storage[i].previous=&storage[i-1];storage[i].previous->next=&storage[i];}storage[capacity-1].next=0;}
 }
 virtual ~List();
 Iterator<T> Begin(){return Iterator<T>(head);}
 Iterator<T> At(unsigned int i){if(i<capacity)return Iterator<T>(&storage[i]);return Iterator<T>(0);}
 Iterator<T> Insert(const T& value,Iterator<T> before) {
  Node<T>*entry=freeHead;if(!entry)return Iterator<T>(0);
  ++activeCount;freeHead=entry->next;entry->active=1;entry->value=value;
  if(!before.node){if(!tail){tail=entry;head=entry;entry->next=0;head->previous=0;tail->previous=0;tail->next=0;return Iterator<T>(entry);}entry->previous=tail;entry->next=0;tail->next=entry;tail=entry;return Iterator<T>(entry);}
  Node<T>*previous=before.node->previous;entry->next=before.node;before.node->previous=entry;entry->previous=previous;if(previous)previous->next=entry;else head=entry;return Iterator<T>(entry);
 }
 Iterator<T> Append(const T&value){Node<T>*entry=freeHead;if(!entry)return Iterator<T>(0);++activeCount;freeHead=entry->next;entry->active=1;entry->value=value;if(!tail){tail=entry;head=entry;entry->next=0;head->previous=0;tail->previous=0;tail->next=0;return Iterator<T>(entry);}entry->previous=tail;entry->next=0;tail->next=entry;tail=entry;return Iterator<T>(entry);}
 void Remove(const Iterator<T>&it){Node<T>*n=it.node;n->active=0;if(n==head)head=n->next;if(n==tail)tail=n->previous;if(n->previous)n->previous->next=n->next;if(n->next)n->next->previous=n->previous;n->next=freeHead;freeHead=n;--activeCount;}
};

struct ChildData:ObjectRoot {
 int unknown04,unknown08;char*first;char*second;char*third;ChildData**items;unsigned int capacity,count;
 ChildData() __asm__("func_002E3408");virtual ~ChildData();
 ChildData&operator=(const ChildData&) __asm__("func_002E2910");
 ChildData*FindByName(const char*) __asm__("func_002E31E0");ChildData*FindChild(const char*,const char*) __asm__("func_002E3100");
 const char*FindValue(const char*) __asm__("func_002E3330");const char*GetName() __asm__("func_002E3920");const char*GetValue() __asm__("func_002E3918");ChildData*GetChild(unsigned int) __asm__("func_002E33E0");ChildData*AddChild() __asm__("func_002E2D40");ChildData*AddCopy(const ChildData*) __asm__("func_002E2EF0");ChildData*SetName(const char*) __asm__("func_002E3630");ChildData*SetValue(const char*) __asm__("func_002E36E8");
};
struct TeamDefinition:ChildData {TeamDefinition(){}virtual ~TeamDefinition();};
struct EntityDefinition:ChildData {EntityDefinition(){}virtual ~EntityDefinition();};
extern const char classKey[];
struct InitConfig;
struct Team;
struct Engine:ObjectRoot {
 ObjectRoot*context;ChildData*config;float scale;unsigned int limit;List<Entity*>*entities;unsigned int maxTeam;List<Team*>*teams;ObjectRoot**services;unsigned int serviceCount,serviceCapacity;unsigned int slot;
 Engine(ObjectRoot*) __asm__("func_002EC020");virtual ~Engine();
 int Init(InitConfig*) __asm__("func_002EB450");void Update(float) __asm__("func_002EA898");int Unregister(Entity*) __asm__("func_002EAD58");
};
struct Brain:ObjectRoot {virtual void Slot1();virtual int Configure(ChildData*);};
struct Entity:ObjectRoot {
 char*name;Iterator<Entity*>globalNode,node;Brain*brain;unsigned int flags;unsigned int ownerId;ChildData*config;Engine*owner;char unknown2c[0x34];
 virtual int Configure(ChildData*);virtual void Reset(Entity*);virtual void Method3(void*);virtual void Method4(unsigned char);
 void Detach(Handler*) __asm__("func_002E4B98");
};
struct Team:ObjectRoot {
 unsigned int unknown04;List<Entity*>*entities;Iterator<Team*>node;
 virtual void Slot1();virtual void Slot2();virtual void Slot3();virtual void Slot4();virtual int Configure(ChildData*);
};
struct EntityClass {unsigned int id;Entity*(*create)(const char*,unsigned int);};
struct BrainClass {unsigned int id;Brain*(*create)(Entity*,void*);};
struct TeamClass {unsigned int id;Team*(*create)(const char*,unsigned int);};
EntityClass*FindEntityClass(const char*) __asm__("func_0038C098");BrainClass*FindBrainClass(const char*) __asm__("func_0038C138");void*FindActionClass(const char*) __asm__("func_0038C1D8");TeamClass*FindTeamClass(const char*) __asm__("func_0038C278");
struct Settings {unsigned int objectCapacity,engineSlots;};extern Settings gSettings;extern Engine**gEngineSlots;extern unsigned int gEnginesUsed;extern Engine*gEngine;extern List<Entity*>*gObjectList;extern unsigned char gCheckTable[0x5b];extern unsigned int gEntitySerial;
int IsStarted() __asm__("func_002E4188");
Engine*CreateEngine(InitConfig*,ObjectRoot*);
TeamDefinition*GetTeamDefinition(Engine*,const char*);EntityDefinition*GetEntityDefinition(Engine*,const char*);
Entity*CreateEntity(const char*,ChildData*,unsigned int,unsigned int);EntityDefinition*MakeEntityDefinition(const char*);TeamDefinition*MakeTeamDefinition(const char*);Team*CreateTeam(ChildData*,const char*,unsigned int);void DestroyTeam(Team*);void UpdateAll(float);int DestroyEntity(Entity*);void DeleteEntity(Entity*);void DeleteTeam(Team*);void ResetEntity(Entity*,Entity*);void Method3(Entity*,void*);void Method4(Entity*,unsigned char);
}
#endif
