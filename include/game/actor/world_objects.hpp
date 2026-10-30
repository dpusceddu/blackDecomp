#ifndef BLACK_MOD_CAMERA_WORLD_HPP
#define BLACK_MOD_CAMERA_WORLD_HPP
#include "game/camera/aim.hpp"
#include "game/weapons/instance.hpp"
#include "ps2/matrix.hpp"
#include "ps2/ee_types.h"
namespace WorldObjects {
using Game::Vec;
using Game::Position4;
struct ObjectActor; struct World; struct Definition;
// Access/ABI views of this medium-confidence object range; historical names and
// complete inheritance remain unknown. Field widths follow PS2 accesses.
struct Name { unsigned low,high; Name& operator=(unsigned long value){ *(unsigned long*)this=value;return *this;} };
struct ActorPrefix { Name name; char unknown08[8]; };
class ActorInterface: public ActorPrefix {public:
 virtual void V0(); virtual void V1(); virtual void V2(); virtual int Release();
 virtual void V4(); virtual int OnState(int); virtual void V6(); virtual void V7();
 virtual void V8(); virtual void V9(); virtual void V10(); virtual void V11();
 virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
 virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
 virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
 virtual int CanDetach();
};
struct ResourcePart { void* value; void* kind; char unknown08[8]; void* vertices; int count; char unknown18[8]; Position4 minimum,maximum; };
struct Breakable { Vec direction,point; char unknown20[0x50]; };
struct BreakableSet { Breakable* records; short count; unsigned short flags; unsigned char* active; char unknown0c[4]; void* query; };
struct Definition { Position4 local; ResourcePart* parts; unsigned count; BreakableSet* breaks; char unknown1c[4]; unsigned long name; };
class ObjectActor: public ActorInterface {public:
 char unknown14[0xc];Position4 spatial;void* anchor;void* owner;char unknown38[0x18];float radius;char unknown54[0xc];
 Position4 local; Position4 world[4]; ObjectActor* next; void* linkage;char unknownb8[4];void* animation;int unknownc0;int kind;char unknownc8[8];
 Definition* definition;void* effect;unsigned short slot;unsigned char active,index;unsigned flags;unsigned char settings[10];signed char a,b,c;unsigned char mode;char unknownee[0x4e];
 unsigned char linked;char unknown13d[3];int pickupKind,identity;unsigned char pickupIndex;char unknown149[3];float age;char unknown150[2];unsigned char behavior;signed char phase;unsigned char blocked;char unknown155[0xb];
 void Initialize(Definition*,int); int Cleanup(); Definition* GetDefinition(); void ResetSlot(); int Enable();
};
struct Player: public ObjectActor {char unknown160[0x760];};
struct Catalog {char unknown00[8];void* names;void* ammo;void* pickup;};
class ObjectPool {public:
 ObjectActor actors[64];void** handles;unsigned char occupied[64];Catalog* catalog;char unknown5848[8];signed char phase;
 inline ObjectActor& At(unsigned char index){return actors[index];}
 ObjectActor* Allocate();void* Resource(unsigned char);
};
struct CollisionCell {char unknown00[0x40];void* world;char unknown44[0x1c];};
struct Region {char unknown00[8];int id;void* geometry;void* data;char unknown14[0x24];signed char active;char unknown39[0x6c7];CollisionCell cells[4];};
struct ActorNode {char unknown00[0x34];ObjectActor* actor;};
struct QueryMaterial {char unknown00[4];unsigned flags;};
typedef Weapons::WorldCollision QueryHit;
// Closest-hit result view; unused fields remain UNVERIFIED.
struct ClosestHit {Position4 point,normal;float fraction;unsigned unknown24,mask,unknown2c;Position4 extra;};
typedef Weapons::WorldCollision TraceHit;
struct FrameConfig {char unknown00[0x20208];int playerCount;};
class World {public:
 char unknown00[0x30];Player players[2];char unknown11b0[0x3770];char space[0x70];Region regions[2];
 void* collision;void* collection;void* transform;void* helper;int state,exitState,transition;signed char level,section,which;char unknown5aaf;int current;void* levelInfo;
 char unknown5ab8[4];unsigned char queues[2][8];char controller[0x34];char effects[0x1a4];ObjectActor* first;
 Region* FindRegion(int);void Activate(ObjectActor*,int,int);void Unlink(ObjectActor*);int RegionReady(int);void LoadActors();void UnloadActors();
 static int SetNodeState(ActorNode*,int);static int VisitBreakable(ActorNode*,int,void*);
 static int MarkSolid(TraceHit*,unsigned char*);static int SelectWorldHit(QueryHit*,ClosestHit*);
 static void SceneLoaded(void*);static void SectionLoaded(void*);
};
typedef char ActorSize[sizeof(ObjectActor)==0x160?1:-1];
typedef char RegionSize[sizeof(Region)==0x880?1:-1];
typedef char WorldRegions[(unsigned)&((World*)0)->regions==0x4990?1:-1];
typedef char PoolCatalog[(unsigned)&((ObjectPool*)0)->catalog==0x5844?1:-1];
typedef char WorldFirst[(unsigned)&((World*)0)->first==0x5ca4?1:-1];
}
#endif
