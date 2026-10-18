#ifndef BLACK_PHYSICS_SCENE_HPP
#define BLACK_PHYSICS_SCENE_HPP
#include "auto/prelude.h"
// PS2 views: offsets below follow the scene's retail loads and stores.
// Vector fourth lanes hold unrelated list payloads; do not overwrite them.
typedef long long PhysicsVec;
struct PhysicsMatrix { PhysicsVec row[4]; } __attribute__((aligned(16)));
struct PhysicsBounds { PhysicsVec low, high; } __attribute__((aligned(16)));
struct PhysicsStorageRequirement { unsigned size, alignment, unknown8, unknownC; };
struct PhysicsStorageBlock { void* memory; unsigned unknown4; PhysicsStorageBlock(){} PhysicsStorageBlock(void* p){memory=p;} };
struct PhysicsSceneLayout { unsigned pairs, treeAlignment, treeSize, solverAlignment, solverSize, total; };
struct PhysicsSceneSettings { PhysicsVec minimum, maximum; float scale; unsigned groups, instances, pairBudget, solverBodies, solverJoints, unknown38; };
struct PhysicsBitCursor {
 unsigned* word; unsigned bit;
 PhysicsBitCursor(unsigned* w,unsigned b):word(w),bit(b){}
 void Next(){if(++bit==32){++word;bit=0;}}
 int AdvanceSet(const PhysicsBitCursor* limit){
  unsigned mask=1u<<bit;
  while(!(*word&mask)){
   mask*=2;
   if(++bit==32){bit=0;mask=1;do{++word;if(word>limit->word){word=limit->word;bit=limit->bit;return 0;}}while(*word==0);}
  }
  return word<limit->word||(word==limit->word&&bit<limit->bit);
 }
 int AdvanceClear(const PhysicsBitCursor* limit){
  unsigned mask=1u<<bit;
  while(*word&mask){
   mask*=2;
   if(++bit==32){bit=0;mask=1;do{++word;if(word>limit->word){word=limit->word;bit=limit->bit;return 0;}}while(*word==~0u);}
  }
  return word<limit->word||(word==limit->word&&bit<limit->bit);
 }
};
struct PhysicsBitmap {
 unsigned* words; unsigned bitCount,wordCount;
 void Initialize(unsigned bits,unsigned* storage){bitCount=bits;wordCount=(bits+31)>>5;words=storage;}
 int Test(unsigned i)const{return (words[i>>5]>>(i&31))&1;}
 void Set(unsigned i){words[i>>5]|=1u<<(i&31);}
 void Clear(unsigned i){words[i>>5]&=~(1u<<(i&31));}
 void ClearAll(){unsigned* end=words+wordCount;for(unsigned* p=words;p!=end;++p)*p=0;}
 PhysicsBitCursor Begin()const{return PhysicsBitCursor(words,0);}
 PhysicsBitCursor End()const{return PhysicsBitCursor(words+(bitCount>>5),bitCount&31);}
 unsigned IndexOf(const PhysicsBitCursor& c)const{return (c.word-words)*32+c.bit;}
};
struct PhysicsPairNode { unsigned index; PhysicsPairNode *next,*previous,*partner; };
struct PhysicsBoundsCallback { unsigned unknown0; short adjustment,unknown6; int (*invoke)(void*,const PhysicsMatrix*,int,PhysicsBounds*); };
struct PhysicsShape { unsigned char pad00[0x58]; PhysicsBoundsCallback* worldBounds; };
static inline PhysicsVec PhysicsWithX(PhysicsVec old,PhysicsVec value){PhysicsVec r;asm("vaddx.x dstv, vf0, srcvx":"=j dstv"(r):"0"(old),"j srcv"(value));return r;}
static inline PhysicsVec PhysicsWithY(PhysicsVec old,PhysicsVec value){PhysicsVec r;asm("vmove.xyzw dstv, oldv\n\tvaddx.y dstv, vf0, srcvx":"=&j dstv"(r):"j oldv"(old),"j srcv"(value));return r;}
static inline PhysicsVec PhysicsWithZ(PhysicsVec old,PhysicsVec value){PhysicsVec r;asm("vaddx.z dstv, vf0, srcvx":"=j dstv"(r):"0"(old),"j srcv"(value));return r;}
static inline PhysicsVec PhysicsFloatBits(float f){union{float f;int i;}u;u.f=f;return (PhysicsVec)u.i;}
static inline PhysicsVec PhysicsAdd(PhysicsVec a,PhysicsVec b){PhysicsVec r;asm("vadd.xyz dstv, srca, srcb":"=j dstv"(r):"j srca"(a),"j srcb"(b));return r;}
static inline PhysicsVec PhysicsSub(PhysicsVec a,PhysicsVec b){PhysicsVec r;asm("vsub.xyz dstv, srca, srcb":"=j dstv"(r):"j srca"(a),"j srcb"(b));return r;}
static inline PhysicsVec PhysicsAddScalar(PhysicsVec a,float b){union{float f;int i;}u;u.f=b;PhysicsVec scalar=(PhysicsVec)u.i,r;asm("vaddx.xyz dstv, srca, srcbx":"=j dstv"(r):"j srca"(a),"j srcb"(scalar));return r;}
static inline PhysicsVec PhysicsSubScalar(PhysicsVec a,float b){union{float f;int i;}u;u.f=b;PhysicsVec scalar=(PhysicsVec)u.i,r;asm("vsubx.xyz dstv, srca, srcbx":"=j dstv"(r):"j srca"(a),"j srcb"(scalar));return r;}
static inline PhysicsVec PhysicsDirection(const PhysicsMatrix& m,PhysicsVec v){PhysicsVec r;asm("vmulax.xyz ACC, basisx, srcvx\n\tvmadday.xyz ACC, basisy, srcvy\n\tvmaddz.xyz dstv, basisz, srcvz":"=j dstv"(r):"j basisx"(m.row[0]),"j basisy"(m.row[1]),"j basisz"(m.row[2]),"j srcv"(v));return r;}
static inline PhysicsVec PhysicsPosition(const PhysicsMatrix& m,PhysicsVec v){PhysicsVec r;asm("vmulax.xyz ACC, basisx, srcvx\n\tvmadday.xyz ACC, basisy, srcvy\n\tvmaddaz.xyz ACC, basisz, srcvz\n\tvmaddw.xyz dstv, posv, vf0w":"=j dstv"(r):"j basisx"(m.row[0]),"j basisy"(m.row[1]),"j basisz"(m.row[2]),"j posv"(m.row[3]),"j srcv"(v));return r;}
static inline float PhysicsLane(PhysicsVec v,unsigned lane){ union{PhysicsVec vector;float f[4];}u;u.vector=v;return u.f[lane]; }
static inline float PhysicsAbs(float f){union{float f;unsigned u;}v;v.f=f;v.u&=0x7fffffff;return v.f;}
struct PhysicsSolver;
struct PhysicsBody {
 unsigned char pad00[0x20]; PhysicsVec linearStep;
 unsigned char pad30[0x1c]; PhysicsSolver* solver;
 unsigned char pad50[0x1c]; unsigned ordinal;
 unsigned char pad70[0x1c]; unsigned state;
 unsigned char pad90[0x1c]; unsigned quietFrames;
 PhysicsBody* Next()const{return *(PhysicsBody* const*)((const char*)this+0x2c);}
};
struct PhysicsSolver {
 unsigned char pad00[0x270]; PhysicsBody awakeBodies;
 unsigned char pad320[0x388-0x270-sizeof(PhysicsBody)]; float contactMargin; unsigned quietFrameLimit;
};
struct PhysicsInstance { PhysicsShape* shape; unsigned char pad04[12];PhysicsMatrix frame; const PhysicsMatrix* offset;void* definition; PhysicsBody* body;void* unknown5c;unsigned ordinal;unsigned char pad64[12]; };
struct PhysicsJoint { PhysicsInstance *a,*b;void *definition,*frame,*handle; };
struct PhysicsCompound {unsigned ordinal; void* selfMask;unsigned instanceCount;PhysicsInstance* instances;unsigned jointCount;PhysicsJoint* joints;unsigned collisionClass;};
struct PhysicsSpatialTree { PhysicsBounds bounds;unsigned objectCapacity,nodeCapacity,freeNode;void *nodes,*entries;PhysicsBounds* boxes;unsigned unknown38[2]; };
struct PhysicsCollisionPair {PhysicsInstance *second,*first;};
struct PhysicsCollisionWork {void* scratch;unsigned unknown04;void* scratchMemory;PhysicsSolver* solver;PhysicsCollisionPair* pairs;unsigned pairCapacity,pairCount,unknown1c;};
struct PhysicsCollisionDefinitions {unsigned pairCapacity,meshCount,shapeCount,workSize;void* shapeDefinitions;void* workMemory;};
struct PhysicsSpatialVisit {PhysicsBounds box;unsigned short node;unsigned char unknown22[14];};
struct PhysicsSpatialEntry {unsigned short unknown0,next,node;unsigned char octant,counted;};
struct PhysicsSpatialQuery {
 PhysicsSpatialTree* tree;unsigned unknown04[3];PhysicsBounds box;
 PhysicsSpatialVisit visits[(0x27c0-0x30)/0x30];unsigned visitCount;unsigned short stack[10];int stackDepth;unsigned nextObject;
 PhysicsSpatialQuery(PhysicsSpatialTree*,const PhysicsBounds*) __asm__("func_00334068");
 void VisitNode() __asm__("func_00333B48");
 int NextCandidate(unsigned* object){unsigned candidate=nextObject;*object=candidate;if(candidate==0xffff){--stackDepth;while(stackDepth<0){if(!visitCount)return 0;VisitNode();}*object=stack[stackDepth];}nextObject=((PhysicsSpatialEntry*)tree->entries)[*object].next;return 1;}
 int NextOverlap(unsigned* object){while(NextCandidate(object)){const PhysicsBounds* b=&tree->boxes[*object];if(PhysicsLane(b->high,0)>=PhysicsLane(box.low,0)&&PhysicsLane(box.high,0)>=PhysicsLane(b->low,0)&&PhysicsLane(b->high,1)>=PhysicsLane(box.low,1)&&PhysicsLane(box.high,1)>=PhysicsLane(b->low,1)&&PhysicsLane(b->high,2)>=PhysicsLane(box.low,2)&&PhysicsLane(box.high,2)>=PhysicsLane(b->low,2))return 1;}return 0;}
};
struct PhysicsPairMask {unsigned unknown0,stride,unknown8,bits[1];int Test(unsigned i)const{return (bits[i>>5]>>(i&31))&1;}};
struct PhysicsScene {
 float scale;unsigned islandPasses,wakeHead,awakeHead;PhysicsPairNode* freePairs;
 PhysicsCollisionDefinitions* collisionDefinitions;PhysicsSolver* solver;PhysicsCollisionWork* collisionWork;
 unsigned instanceCapacity,pairBudget,groupCapacity,pairNodeCount,groupCount,instanceCount,exclusionCount;
 PhysicsBounds* boxes;PhysicsSpatialTree* tree;PhysicsCompound** groups;PhysicsInstance** instances;
 PhysicsPairNode* pairNodes;PhysicsPairNode **shapePairs,**exclusions;unsigned *groupOf,*links;
 PhysicsBitmap groupUsed,groupPlaced,groupDirty,instanceUsed,boundsValid,instanceFixed,boundsDirty,quiet,visited,queued;
 PhysicsPairMask* groupMask;
 void AddExclusion(unsigned first,unsigned second){
  PhysicsPairNode* a=freePairs;PhysicsPairNode* b=a->next;freePairs=b->next;
  a->index=first;a->next=exclusions[first];if(a->next)a->next->previous=a;a->previous=0;exclusions[first]=a;
  b->index=second;b->next=exclusions[second];if(b->next)b->next->previous=b;b->previous=0;exclusions[second]=b;
  ++exclusionCount;
 }
 void ReleasePairNode(PhysicsPairNode* node, PhysicsPairNode**& lists){
  if(node->previous)node->previous->next=node->next;else lists[node->index]=node->next;
  if(node->next)node->next->previous=node->previous;
  node->next=freePairs;freePairs=node;
 }
 void ResetPairPools() __asm__("func_0032D108");
 void CollectAwakeBodies() __asm__("func_0032D248");
 void UpdateDirtyBounds() __asm__("func_0032D358");

 void QueryDirtyGroups() __asm__("func_0032D7C0");
 void CollectIslandPairs(unsigned,unsigned,unsigned) __asm__("func_0032D990");
 void PublishSleepWake() __asm__("func_0032DCE8");
 int RebuildGroupBounds(unsigned,PhysicsBounds*) __asm__("func_0032C838");
 int UpdateShapeBounds(PhysicsInstance*,unsigned) __asm__("func_0032C5A0");
 void UpdateSpatialGroup(unsigned);
 void UpdateDirtyGroups() __asm__("func_0032D590");
 void RetireShapePairs(unsigned ordinal){while(shapePairs[ordinal]){PhysicsPairNode* node=shapePairs[ordinal];ReleasePairNode(node,shapePairs);ReleasePairNode(node->partner,shapePairs);}}
 void RetireExclusions(unsigned ordinal){while(exclusions[ordinal]){PhysicsPairNode* node=exclusions[ordinal];ReleasePairNode(node,exclusions);ReleasePairNode(node->partner,exclusions);--exclusionCount;}}
 void RegisterCompound(PhysicsCompound*,unsigned) __asm__("func_0032CB58");
 void RetireCompoundPairs(unsigned group){unsigned count=groups[group]->instanceCount;for(unsigned i=0;i<count;++i){unsigned ordinal=groups[group]->instances[i].ordinal;RetireShapePairs(ordinal);RetireExclusions(ordinal);}}
 int PairGroups(unsigned,unsigned);
 void AllocatePair(unsigned,unsigned);
 void SetCompoundUpdateMask(PhysicsCompound*,int) __asm__("func_0032E218");
 void DeregisterCompound(PhysicsCompound*) __asm__("func_0032CDE0");
 int QueryGroup(unsigned,const PhysicsBounds*) __asm__("func_0032C0D8");
};
static inline unsigned PhysicsAlignUp(unsigned n,unsigned a){return (n+a-1)&-a;}
extern "C" {
 PhysicsSceneLayout func_0032BC70(const PhysicsSceneSettings*);
 void func_0032FAF0(PhysicsCollisionWork*);
 void func_0037CE60(PhysicsSolver*,void*,unsigned,unsigned);
 PhysicsSpatialTree* func_003339A0(void*,unsigned,const PhysicsSceneSettings*);
 PhysicsSolver* func_0037C238(PhysicsStorageBlock*,unsigned,unsigned);
 void func_00334028(PhysicsStorageRequirement*,unsigned,const PhysicsBounds*);
 void func_0037CDF0(PhysicsStorageRequirement*,unsigned,unsigned);
 PhysicsBounds func_00394E20(const PhysicsBounds*,const PhysicsBounds*);
 extern PhysicsVec* D_0040E408;
 PhysicsCollisionWork* func_0032E710(PhysicsStorageBlock*,unsigned,PhysicsSolver*);
 void func_0032E2A0(PhysicsScene*,PhysicsInstance*,int);
 int func_0032C5A0(PhysicsScene*,PhysicsInstance*,unsigned);
 int func_0032C838(PhysicsScene*,unsigned,PhysicsBounds*);
 void func_00333808(PhysicsSpatialTree*,unsigned);
 void func_003333A8(PhysicsSpatialTree*,unsigned,const PhysicsBounds*);
 void func_0032C0D8(PhysicsScene*,unsigned,const PhysicsBounds*);
 void func_0037CF60(PhysicsSolver*,PhysicsBody*);
 void func_0037CFD0(PhysicsSolver*,PhysicsBody*);
 void func_0032AE70(PhysicsCompound*,PhysicsSolver*,unsigned);
 unsigned func_0032CA68(const PhysicsBitmap*);
 void func_0032D108(PhysicsScene*);
 void func_0032E218(PhysicsScene*,PhysicsCompound*,int);
 void func_0032B3B0(PhysicsCompound*,PhysicsSolver*);
 void func_0032D248(PhysicsScene*);
 void func_0032D358(PhysicsScene*);
 void func_0032D590(PhysicsScene*);
 void func_0032D7C0(PhysicsScene*);
 void func_0032D990(PhysicsScene*,unsigned,unsigned,unsigned);
 void func_0032DCE8(PhysicsScene*);
 void func_0032FAF8(PhysicsCollisionWork*);
 void func_0037C4E0(PhysicsSolver*);
}
#endif
