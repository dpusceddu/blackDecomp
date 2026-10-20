// Entity ownership views; offsets follow the PS2 constructor and attribute consumers.
#ifndef BLACK_CONTEXT_BEHAVIORS_ENTITY_HPP
#define BLACK_CONTEXT_BEHAVIORS_ENTITY_HPP
#include "kynapse/alloc.hpp"
extern void (*memoryRelease)(void*);
extern "C" unsigned int strlen(const char*);
extern "C" char* strcpy(char*,const char*);
namespace KaimEntity {
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
 Iterator<T> Insert(const T& value,const Iterator<T>& before) {
  Node<T>*entry=freeHead;if(!entry)return Iterator<T>(0);
  ++activeCount;freeHead=entry->next;entry->active=1;entry->value=value;
  if(!before.node){if(!tail){tail=entry;head=entry;entry->next=0;head->previous=0;tail->previous=0;tail->next=0;return Iterator<T>(entry);}entry->previous=tail;entry->next=0;tail->next=entry;tail=entry;return Iterator<T>(entry);}
  Node<T>*previous=before.node->previous;entry->next=before.node;before.node->previous=entry;entry->previous=previous;if(previous)previous->next=entry;else head=entry;return Iterator<T>(entry);
 }
 void Remove(const Iterator<T>&it){Node<T>*n=it.node;n->active=0;if(n==head)head=n->next;if(n==tail)tail=n->previous;if(n->previous)n->previous->next=n->next;if(n->next)n->next->previous=n->previous;n->next=freeHead;freeHead=n;--activeCount;}
};
struct AttributeRegistry {char unknown00[0x400];int count;};
AttributeRegistry*GetAttributeRegistry() __asm__("func_0038CC20");
struct AttributeKey {int index;ObjectRoot*(*create)();};
struct World {char unknown00[0x14];List<Entity*>*entities;};extern World*gWorld;
struct Entity:ObjectRoot {
 char*name;Iterator<Entity*>globalNode;Iterator<Entity*>node;ObjectRoot*child;unsigned int unknown1c;int ownerId;int field24;World*owner;List<Handler*>*handlers;char unknown30[0x28];int attributeCount;ObjectRoot**attributes;
 Entity(const char*,int) __asm__("func_002E41D8");virtual ~Entity();
 void Attach(Handler*) __asm__("func_002E4860");void Detach(Handler*) __asm__("func_002E4B98");
 unsigned int GetId() __asm__("func_002E4C60");ObjectRoot*GetAttribute(AttributeKey*) __asm__("func_002E4CE0");ObjectRoot*CreateAttribute(AttributeKey*) __asm__("func_002E4D18");
 static Entity*FindById(unsigned int) __asm__("func_002E4798");
};
typedef char EntitySize[sizeof(Entity)==0x60?1:-1];
typedef char EntityAttributeCount[(unsigned int)&((Entity*)0)->attributeCount==0x58?1:-1];
}
#endif
