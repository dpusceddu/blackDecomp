// PS2 GotoAgent receiver offsets and native virtual interfaces.
#ifndef BLACK_CONTEXT_BEHAVIORS_GOTO_HPP
#define BLACK_CONTEXT_BEHAVIORS_GOTO_HPP
#include "kynapse/alloc.hpp"
extern void (*memoryRelease)(void*);
namespace KaimGoto {
struct Vec3 {
 float x,y,z;
 Vec3& operator=(const Vec3& v){x=v.x;y=v.y;z=v.z;return *this;}
 bool operator!=(const Vec3& v)const{return !(v.x==x && v.y==y && v.z==z);}
 
};
extern Vec3 origin;
struct ClassInfo;
extern ClassInfo targetClass;
struct ActionBank {
 virtual void Slot0();virtual void Select(int);
 void ClearActivation() __asm__("func_002DFBF8");
};
struct EntityRoot {virtual void Slot0();};
struct TargetEntity:EntityRoot {
 virtual void Slot0();virtual void Slot1();virtual void Slot2();virtual void Slot3();virtual void Slot4();
 virtual int Query(Vec3*);virtual void Slot6();virtual void Slot7();virtual void Slot8();virtual void Slot9();virtual bool IsActive();virtual void Stop();
 char unknown04[4];int id;
};
struct ClassRegistry {TargetEntity* FindByClass(ClassInfo*) __asm__("func_002E1C58");};
struct ChildBuffers;
struct ObjectRoot {virtual ~ObjectRoot();};
struct Agent:ObjectRoot {
 virtual ~Agent();
 ActionBank* bank;ClassRegistry* context;
 // This agent-family traversal is distinct from the other configurable-object copy.
 int ConfigureAll(ChildBuffers*) __asm__("func_002E0018");
 static void* operator new(unsigned int size){return KaimAllocate(size);}
 static void operator delete(void* block){memoryRelease(block);}
};
struct GotoAgent:Agent {
 GotoAgent(ClassRegistry*) __asm__("func_002D39D0");
 virtual ~GotoAgent();
 virtual int Init(ChildBuffers*) __asm__("func_002D3A78");
 virtual void Slot2();virtual void Slot3();virtual void Slot4();virtual void Slot5();
 virtual bool Update() __asm__("func_002D3B08");
 virtual int Prepare();
 TargetEntity* target;unsigned char active;char unknown11[3];unsigned int field14;Vec3 destination;
 void Stop() __asm__("func_002D3BA8");
 void SetDestination(const Vec3&) __asm__("func_002D3BD8");
};
#define CHECK_OFFSET(T,m,o) typedef char T##m[(unsigned int)&((T*)0)->m==o?1:-1]
CHECK_OFFSET(Agent,bank,4);CHECK_OFFSET(Agent,context,8);CHECK_OFFSET(GotoAgent,target,0xc);CHECK_OFFSET(GotoAgent,active,0x10);CHECK_OFFSET(GotoAgent,field14,0x14);CHECK_OFFSET(GotoAgent,destination,0x18);CHECK_OFFSET(TargetEntity,id,8);
#undef CHECK_OFFSET
typedef char GotoSize[sizeof(GotoAgent)==0x24?1:-1];
}
#endif
