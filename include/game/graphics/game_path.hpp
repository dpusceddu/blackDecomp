#ifndef BLACK_GAME_PATH_HPP
#define BLACK_GAME_PATH_HPP
#include "kynapse/graph/path_object.hpp"
#include "ps2/ee_types.h"
// PS2 callback and container views. The derived historical class name, complete
// allocation size and unused fields are unverified.
namespace GamePathPS2 {
struct PathAgent;
struct RouteNode { int unknown00; int identity; };
struct GameActor { char unknown00[0xc4]; int kind; };
struct MovementGate { char unknown00[0x100]; int identity; };
struct Movement {
 template<class T> inline T& At(unsigned int offset) { return *(T*)((char*)this+offset); }
 MovementGate* Gate() { return (MovementGate*)((char*)this+0x1da0); }
};
struct SegmentRecord {
 char unknown00[0x30]; unsigned long allowedActors; char unknown38[0x28];
};
struct SegmentBank { unsigned int unknown00; SegmentRecord* records; int** identities; };
struct Callback { virtual void Slot0(); virtual void Slot1(); virtual unsigned int Filter(PathAgent*,RouteNode*,unsigned int); };
struct PathObject : Kaim::CPathObject {
 unsigned int primaryCount;
 unsigned int unknown74;
 SegmentBank *primary,*secondary;
 inline SegmentRecord* Record(unsigned int index) {
  if(index>=primaryCount)return secondary->records+(index-primaryCount);
  return primary->records+index;
 }
 inline int* Identity(unsigned int index) {
  if(index>=primaryCount)return secondary->identities[index-primaryCount];
  return primary->identities[index];
 }
 int Find(RouteNode*) __asm__("func_00389060");
 int FindLinked(RouteNode*) __asm__("func_00289C10");
 void Install(MovementGate*,SegmentRecord*) __asm__("func_00289DA8");
 unsigned int CanUse(PathAgent*,RouteNode*,Callback*,unsigned int);
 int UpdateUse(PathAgent*,RouteNode*,int,unsigned char*);
};
typedef char PrimaryCountAt70[(unsigned int)&((PathObject*)0)->primaryCount==0x70?1:-1];
typedef char PrimaryBankAt78[(unsigned int)&((PathObject*)0)->primary==0x78?1:-1];
typedef char SegmentStride60[sizeof(SegmentRecord)==0x60?1:-1];
extern "C" {
 GameActor* func_00171CB0(PathAgent*);
 Movement* func_00135550(GameActor*);
 void* func_00135570(GameActor*);
 int func_00138320(void*);
 int func_0016DD68(void*,int);
 int func_0018C3C0(MovementGate*);
 void func_0018C368(MovementGate*);
 extern void* D_0040F4D4;
}
}
#endif
