#include "include_asm.h"

// Scene storage, broadphase pools and bitmap iteration; PS2 member offsets are in scene.hpp.
#include "physics/scene.hpp"

#ifdef FULL_TU_CONTEXT
// Each alignment stage is kept in the storage-size expression before array sizes are added.
static inline unsigned SceneStorageAlign(unsigned bytes, unsigned alignment)
{
    return (bytes + (alignment - 1u)) & -alignment;
}

extern "C" PhysicsSceneLayout func_0032BC70(const PhysicsSceneSettings* settings)
{
    PhysicsSceneLayout layout;
    PhysicsStorageRequirement tree;
    PhysicsBounds bounds;
    PhysicsStorageRequirement solver;
    func_00334028(&tree, settings->groups, &bounds);
    func_0037CDF0(&solver, settings->solverBodies, settings->solverJoints);

    unsigned size = (SceneStorageAlign(
        SceneStorageAlign((settings->instances << 5) + 256, tree.alignment) + tree.size,
        solver.alignment) + solver.size + 127) & 0xffffff80UL;
    unsigned pairs = settings->pairBudget + settings->solverJoints;
    unsigned total = size + settings->groups * 4 + settings->instances * 4 + pairs * 32
        + settings->instances * 4 + settings->instances * 4
        + settings->instances * 4 + settings->instances * 4
        + ((settings->groups + 31) >> 5) * 12
        + ((settings->instances + 31) >> 5) * 28;
    layout.pairs = pairs * 2;
    layout.treeAlignment = tree.alignment;
    layout.treeSize = tree.size;
    layout.total = total;
    layout.solverAlignment = solver.alignment;
    layout.solverSize = solver.size;
    return layout;
}
#endif

#ifdef FULL_TU_CONTEXT
inline void* operator new(unsigned int, void* memory) throw() { return memory; }
// Unmatched: 124 differences and three words short in storage/bitmap allocation; artificial inputs still disagree on ordered call argument banks.
extern "C" PhysicsScene* func_0032BDC0(PhysicsStorageBlock* storage, const PhysicsSceneSettings* settings)
{
    PhysicsSceneLayout layout = func_0032BC70(settings);
    PhysicsScene* scene = static_cast<PhysicsScene*>(storage->memory);
    scene->islandPasses = 100;
    scene->wakeHead = ~0u;
    scene->awakeHead = ~0u;
    scene->scale = settings->scale;
    scene->groupMask = 0;
    scene->instanceCapacity = settings->instances;
    scene->pairBudget = settings->pairBudget;
    scene->groupCapacity = settings->groups;
    scene->boxes = reinterpret_cast<PhysicsBounds*>(reinterpret_cast<char*>(scene) + 0x100);
    scene->pairNodeCount = layout.pairs;
    unsigned int offset = SceneStorageAlign((settings->instances << 5) + 256, layout.treeAlignment);
    PhysicsSpatialTree* tree = reinterpret_cast<PhysicsSpatialTree*>(reinterpret_cast<char*>(scene) + offset);
    offset += layout.treeSize;
    scene->tree = new(tree) PhysicsSpatialTree(settings->groups,settings);
    offset = SceneStorageAlign(offset, layout.solverAlignment);
    PhysicsStorageBlock solverStorage(reinterpret_cast<char*>(scene) + offset);
    offset += layout.solverSize;
    scene->solver = func_0037C238(&solverStorage,settings->solverBodies,settings->solverJoints);
    scene->collisionWork = 0;
    scene->solver->contactMargin = settings->scale * 0.2f;
    offset = (offset + 127) & 0xffffff80UL;
    scene->groups = reinterpret_cast<PhysicsCompound**>(reinterpret_cast<char*>(scene) + offset);
    offset += settings->groups * 4;
    scene->instances = reinterpret_cast<PhysicsInstance**>(reinterpret_cast<char*>(scene) + offset);
    offset += settings->instances * 4;
    scene->pairNodes = reinterpret_cast<PhysicsPairNode*>(reinterpret_cast<char*>(scene) + offset);
    offset += layout.pairs * 16;
    scene->shapePairs = reinterpret_cast<PhysicsPairNode**>(reinterpret_cast<char*>(scene) + offset);
    offset += settings->instances * 4;
    scene->exclusions = reinterpret_cast<PhysicsPairNode**>(reinterpret_cast<char*>(scene) + offset);
    offset += settings->instances * 4;
    scene->groupOf = reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(scene) + offset);
    offset += settings->instances * 4;
    scene->links = reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(scene) + offset);
    offset += settings->instances * 4;
    unsigned int* bits = reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(scene) + offset);
    unsigned int groupWords = (settings->groups + 31) >> 5;
    unsigned int instanceWords = (settings->instances + 31) >> 5;
    scene->groupUsed.Initialize(settings->groups, bits);
    bits += groupWords;
    scene->groupPlaced.Initialize(settings->groups, bits);
    bits += groupWords;
    scene->groupDirty.Initialize(settings->groups, bits);
    bits += groupWords;
    scene->instanceUsed.Initialize(settings->instances, bits);
    bits += instanceWords;
    scene->boundsValid.Initialize(settings->instances, bits);
    bits += instanceWords;
    scene->instanceFixed.Initialize(settings->instances, bits);
    bits += instanceWords;
    scene->boundsDirty.Initialize(settings->instances, bits);
    bits += instanceWords;
    scene->quiet.Initialize(settings->instances, bits);
    bits += instanceWords;
    scene->visited.Initialize(settings->instances, bits);
    bits += instanceWords;
    scene->queued.Initialize(settings->instances, bits);
    scene->ResetPairPools();
    return scene;
}
#endif

#ifdef FULL_TU_CONTEXT
// Packed-overlap and XYZ separation operations.
static inline float SceneVectorX(PhysicsVec v){float result;asm("qmfc2.ni bitsr, inputv":"=r bitsr"(result):"j inputv"(v));return result;}
static inline PhysicsVec SceneBoxGap(const PhysicsBounds& a,const PhysicsBounds& b){PhysicsVec low=b.low,high=a.low;
 asm("vsub.xyz lowv, lowv, ahigh\n\tvsub.xyz highv, highv, bhigh\n\tvmax.xyz highv, highv, lowv":"+&j lowv"(low),"+j highv"(high):"j ahigh"(a.high),"j bhigh"(b.high));return high;}
union SceneGapLaneView{PhysicsVec native;volatile float lane[4];};
static inline float SceneGapLane(PhysicsVec value,SceneGapLaneView& view,unsigned lane){asm volatile("sqc2 nativev,0(address)":"=m"(view):"j nativev"(value),"r address"(&view));return view.lane[lane];}
static inline float Separation(const PhysicsBounds& a,const PhysicsBounds& b){
 PhysicsVec gap=SceneBoxGap(a,b);
 SceneGapLaneView yView,zView;
 float x=SceneVectorX(gap),y=SceneGapLane(gap,yView,1),z=SceneGapLane(gap,zView,2);
 float xy=x>y?x:y;return xy>z?xy:z;
}

inline void PhysicsScene::AllocatePair(unsigned first,unsigned second){PhysicsPairNode* a=freePairs;PhysicsPairNode* b=a->next;freePairs=b->next;a->index=first;a->Insert(shapePairs[first]);b->index=second;b->Insert(shapePairs[second]);}

inline int PhysicsScene::PairGroups(unsigned int first, unsigned int second)
{
    float margin = solver->contactMargin;
    PhysicsCompound* compound = groups[first];
    unsigned int firstCount = compound->instanceCount;
    unsigned int secondCount = groups[second]->instanceCount;
    int pairs = 0;
    PhysicsPairMask* selfMask = 0;
    if (groupMask) {
        unsigned int firstClass = groups[first]->collisionClass;
        unsigned int secondClass = groups[second]->collisionClass;
        if(firstClass<secondClass?groupMask->Test(firstClass*groupMask->stride+secondClass):groupMask->Test(secondClass*groupMask->stride+firstClass))return 0;
    }
    if (first == second)
        selfMask = (PhysicsPairMask*)groups[second]->selfMask;
    for (unsigned int i = 0; i < firstCount; ++i) {
        unsigned int a = groups[first]->instances[i].ordinal;
        if (!boundsValid.Test(a))
            continue;
        for (unsigned int j = 0; j < secondCount; ++j) {
            unsigned int b = groups[second]->instances[j].ordinal;
            if (a == b)
                continue;
            if (selfMask && selfMask->Test(selfMask->stride * i + j))
                continue;
            if (!boundsValid.Test(b))
                continue;
            if (margin > Separation(boxes[a],boxes[b]) && freePairs && freePairs->next) {
                AllocatePair(a, b);
                ++pairs;
            }
        }
    }
    return pairs;
}

// Unmatched: 121 differences and one word short in original mask/pair-loop allocation; official recorded replay passes 4/178 because call argument banks differ.
int PhysicsScene::QueryGroup(unsigned int group, const PhysicsBounds* box)
{
    float margin = solver->contactMargin;
    PhysicsBounds grown;
    grown.low = PhysicsSubScalar(box->low,margin);
    grown.high = PhysicsAddScalar(box->high,margin);
    int pairs = 0;
    PhysicsSpatialQuery query(tree, &grown);
    unsigned int other;
    while (query.NextOverlap(&other)) {
        if (other >= group || !groupDirty.Test(other))
            pairs += PairGroups(group, other);
    }
    return pairs;
}
#endif

#ifdef FULL_TU_CONTEXT
// Unmatched: body/frame-copy scheduling and scalar-lane address allocation (18 differing instructions).
static inline PhysicsVec SceneMatrixDirection(const PhysicsMatrix& m,const PhysicsVec& v){PhysicsVec r;asm("vmulax.xyz ACC, basisx, srcvx\n\tvmadday.xyz ACC, basisy, srcvy\n\tvmaddz.xyz dstv, basisz, srcvz":"=j dstv"(r):"j basisx"(m.row[0]),"j basisy"(m.row[1]),"j basisz"(m.row[2]),"j srcv"(v));return r;}
static inline PhysicsVec SceneMatrixPosition(const PhysicsMatrix& m,const PhysicsVec& v){PhysicsVec r;asm("vmulax.xyz ACC, basisx, srcvx\n\tvmadday.xyz ACC, basisy, srcvy\n\tvmaddaz.xyz ACC, basisz, srcvz\n\tvmaddw.xyz dstv, posv, vf0w":"=j dstv"(r):"j basisx"(m.row[0]),"j basisy"(m.row[1]),"j basisz"(m.row[2]),"j posv"(m.row[3]),"j srcv"(v));return r;}
static inline PhysicsMatrix SceneMatrixProduct(const PhysicsMatrix& left,const PhysicsMatrix& right) return result; {
 result.row[0]=SceneMatrixDirection(left,right.row[0]);
 result.row[1]=SceneMatrixDirection(left,right.row[1]);
 result.row[2]=SceneMatrixDirection(left,right.row[2]);
 result.row[3]=SceneMatrixPosition(left,right.row[3]);
}
static inline float SceneX(PhysicsVec vector){
 int word;asm("qmfc2.ni %0, input":"=r"(word):"j input"(vector));
 union{int word;float scalar;}value;value.word=word;return value.scalar;
}
static inline int SceneWord(float scalar){union{float scalar;int word;}value;value.scalar=scalar;return value.word;}
static inline float SceneFloat(unsigned word){union{float scalar;unsigned word;}value;value.word=word;return value.scalar;}
static inline int SceneXWord(PhysicsVec vector){float word;asm("qmfc2.ni %0, input":"=r"(word):"j input"(vector));return SceneWord(word);}
union SceneScalar{int word;float scalar;};
static inline float SceneAbsWord(volatile SceneScalar& value,int word){value.word=word;value.word&=0x7fffffff;return value.scalar;}
static inline PhysicsMatrix SceneBodyFrame(const PhysicsBody* body) return result; {
 result.row[0]=body->rowX;result.row[1]=body->rowY;result.row[2]=body->rowZ;result.row[3]=body->position;
}
static inline const PhysicsMatrix& MatrixView(const PhysicsMatrix& matrix){return matrix;}
static inline const PhysicsMatrix* MatrixAddress(const PhysicsMatrix* matrix){return matrix;}

static inline PhysicsVec SceneAddScalar(const PhysicsVec& a,float b){PhysicsVec scalar,r;asm("qmtc2.ni bitsr, scalarv":"=j scalarv"(scalar):"r bitsr"(b));asm("vaddx.xyz dstv, srca, srcbx":"=j dstv"(r):"j srca"(a),"j srcb"(scalar));return r;}
union SceneLaneView{PhysicsVec native;volatile float lane[4];};
static inline float SceneLane(PhysicsVec value,SceneLaneView& view,unsigned lane){asm volatile ("sqc2 nativev,0(address)":"=m"(view):"j nativev"(value),"r address"(&view));return view.lane[lane];}
static inline void SceneMatrixAssign(PhysicsMatrix& result,PhysicsVec y,PhysicsVec z,PhysicsVec x,PhysicsVec p){result.row[0]=x;result.row[1]=y;result.row[2]=z;result.row[3]=p;}
typedef char SceneBoundsStride32[sizeof(PhysicsBounds)==32?1:-1];
typedef char SceneByteAddress32[sizeof(void*)==4 && sizeof(unsigned)==4?1:-1];
int PhysicsScene::UpdateShapeBounds(PhysicsInstance* instance,unsigned ordinal){
 PhysicsMatrix world;PhysicsVec x,y,z,p;
 const PhysicsBody* b=instance->body;
 if(b){
  p=b->position;
  if(instance->offset){
   PhysicsMatrix body;
   SceneMatrixAssign(body,b->rowY,b->rowZ,b->rowX,p);
   world=SceneMatrixProduct(MatrixView(body),*instance->offset);
   goto frameReady;
  }
  z=b->rowZ;y=b->rowY;x=b->rowX;
 }else{z=instance->frame.row[2];y=instance->frame.row[1];x=instance->frame.row[0];p=instance->frame.row[3];}
 world.row[0]=x;world.row[1]=y;world.row[2]=z;world.row[3]=p;
frameReady:;
 PhysicsShape* shape=instance->shape;PhysicsBoundsCallback* cb=shape->worldBounds;
 if(cb->invoke((char*)shape+cb->adjustment,&world,0,reinterpret_cast<PhysicsBounds*>((ordinal * sizeof(PhysicsBounds)) + reinterpret_cast<unsigned>(boxes)))){
  boundsValid.Set(ordinal);
  if(!instanceFixed.Test(ordinal)){
   const PhysicsVec& marginBase=*D_0040E408;
   SceneLaneView yView,zView;
   volatile SceneScalar absolute[3];
   PhysicsVec step=instance->body->linearStep;
   float distance=SceneAbsWord(absolute[0],SceneXWord(step))+SceneAbsWord(absolute[1],SceneWord(SceneLane(step,yView,1)))+SceneAbsWord(absolute[2],SceneWord(SceneLane(step,zView,2)));
   PhysicsVec margin=SceneAddScalar(marginBase,distance);
   boxes[ordinal].low=PhysicsSub(boxes[ordinal].low,margin);boxes[ordinal].high=PhysicsAdd(boxes[ordinal].high,margin);
  }return 1;
 }
 boundsValid.Clear(ordinal);return 0;
}
#endif

// The visible scalar view preserves the current index separately from the loop counter.
static inline unsigned PhysicsSceneIndexValue(const unsigned& value) { return value; }

int PhysicsScene::RebuildGroupBounds(unsigned group, PhysicsBounds* bounds)
{
    int found = 0;
    unsigned count = groups[group]->instanceCount;
    for (unsigned i = 0; i < count; ++i) {
        unsigned index = i;
        PhysicsInstance& instance = groups[group]->instances[PhysicsSceneIndexValue(index)];
        unsigned ordinal = instance.ordinal;
        while (shapePairs[ordinal]) {
            PhysicsPairNode* node = shapePairs[ordinal];
            ReleasePairNode(node, shapePairs);
            ReleasePairNode(node->partner, shapePairs);
        }
        if (boundsValid.Test(ordinal)) {
            if (!found) {
                *bounds = boxes[ordinal];
                found = 1;
            } else {
                *bounds = func_00394E20(bounds, &boxes[ordinal]);
            }
        }
    }
    if (found)
        groupPlaced.Set(group);
    else
        groupPlaced.Clear(group);
    return found;
}

extern "C" unsigned func_0032CA68(const PhysicsBitmap* bitmap){
 PhysicsBitCursor cursor=bitmap->Begin(),end=bitmap->End();
 cursor.AdvanceClear(&end);return bitmap->IndexOf(cursor);
}


#ifdef FULL_TU_CONTEXT
static unsigned FirstClear(const PhysicsBitmap* bitmap){PhysicsBitCursor c=bitmap->Begin(),end=bitmap->End();c.AdvanceClear(&end);return bitmap->IndexOf(c);}

#endif
static inline unsigned AllocateBit(PhysicsBitmap* bitmap){unsigned n=func_0032CA68(bitmap);bitmap->Set(n);return n;}

void PhysicsScene::RegisterCompound(PhysicsCompound* compound, unsigned int mode)
{
    unsigned int i;
    unsigned int count = compound->instanceCount;
    unsigned int group = func_0032CA68(&groupUsed);
    compound->ordinal = group;
    func_0032AE70(compound,solver,mode);
    groupUsed.Set(group);
    groupPlaced.Clear(group);
    groups[group] = compound;
    ++groupCount;
    for (i = 0; i < count; ++i) {
        unsigned int ordinal = AllocateBit(&instanceUsed);
        ++instanceCount;
        instances[ordinal] = &compound->instances[i];
        instances[ordinal]->ordinal = ordinal;
        shapePairs[ordinal] = 0;
        exclusions[ordinal] = 0;
        boundsDirty.Set(ordinal);
        boundsValid.Clear(ordinal);
        PhysicsInstance& instance = compound->instances[i];
        instance.body->Ordinal() = ordinal;
        groupOf[ordinal] = group;
        if (mode == 1)
            instanceFixed.Set(ordinal);
        else
            instanceFixed.Clear(ordinal);
    }
    for (i = 0; i < compound->jointCount; ++i) {
        PhysicsJoint* joint = &compound->joints[i];
        AddExclusion(joint->a->ordinal, joint->b->ordinal);
    }
}

void PhysicsScene::DeregisterCompound(PhysicsCompound* compound)
{
    unsigned int group = compound->ordinal;
    unsigned int count = compound->instanceCount;
    SetCompoundUpdateMask(compound, 0);
    RetireCompoundPairs(group);
    func_0032B3B0(groups[group],solver);
    if (groupPlaced.Test(group))
        func_00333808(tree,group);
    for (unsigned int i = 0; i < count; ++i)
        instanceUsed.Clear(groups[group]->instances[i].ordinal);
    groupUsed.Clear(group);
    --groupCount;
    instanceCount -= count;
}


void PhysicsScene::ResetPairPools()
{
    freePairs = pairNodes;
    unsigned int i;
    for (i = 0; i < pairNodeCount; ++i) {
        unsigned int next = i + 1;
        pairNodes[i].next = &pairNodes[next];
        pairNodes[i].partner = &pairNodes[next - (i & 1) * 2];
    }
    pairNodes[pairNodeCount - 1].next = 0;
    groupUsed.ClearAll();
    instanceUsed.ClearAll();
    boundsDirty.ClearAll();
    groupCount = 0;
    instanceCount = 0;
    exclusionCount = 0;
}


void PhysicsScene::CollectAwakeBodies()
{
    quiet.ClearAll();
    awakeHead = 0xffffffff;
    queued.ClearAll();
    PhysicsBody* sentinel = &solver->awakeBodies;
    unsigned int limit = solver->quietFrameLimit;
    for (PhysicsBody* body = sentinel->Next(); body != sentinel; body = body->Next()) {
        unsigned int ordinal = body->ordinal;
        boundsDirty.Set(ordinal);
        if (body->quietFrames >= limit) {
            quiet.Set(ordinal);
        } else {
            unsigned int* awakeLinks = links;
            awakeLinks[ordinal] = awakeHead;
            awakeHead = ordinal;
            queued.Set(ordinal);
        }
    }
}


static inline int PhysicsCursorAdvanceSet(PhysicsBitCursor& cursor, const PhysicsBitCursor& end)
{
    return cursor.AdvanceSet(&end);
}

void PhysicsScene::UpdateDirtyBounds()
{
    groupDirty.ClearAll();
    PhysicsBitCursor cursor(boundsDirty.Begin().word, 0);
    while (PhysicsCursorAdvanceSet(cursor, boundsDirty.End())) {
        unsigned ordinal = boundsDirty.IndexOf(cursor);
        func_0032C5A0(this, instances[ordinal], ordinal);
        groupDirty.Set(groupOf[ordinal]);
        boundsDirty.Clear(ordinal);
        cursor.Next();
    }
}

inline void PhysicsScene::UpdateSpatialGroup(unsigned group)
{
    PhysicsBounds bounds;
    PhysicsBounds* boundsPointer = &bounds;
    if (groupPlaced.Test(group)) {
        if (RebuildGroupBounds(group, boundsPointer)) {
            PhysicsSpatialTree* groupTree = tree;
            func_00333808(groupTree, group);
            func_003333A8(groupTree, group, boundsPointer);
        } else {
            func_00333808(tree, group);
        }
    } else if (RebuildGroupBounds(group, boundsPointer)) {
        func_003333A8(tree, group, boundsPointer);
    }
}

void PhysicsScene::UpdateDirtyGroups()
{
    PhysicsBitCursor cursor(groupDirty.Begin().word, 0);
    while (PhysicsCursorAdvanceSet(cursor, groupDirty.End())) {
        unsigned group = groupDirty.IndexOf(cursor);
        UpdateSpatialGroup(group);
        cursor.Next();
    }
}

void PhysicsScene::QueryDirtyGroups()
{
    PhysicsBitCursor cursor(groupDirty.Begin().word, 0);
    while (PhysicsCursorAdvanceSet(cursor, groupDirty.End())) {
        unsigned group = groupDirty.IndexOf(cursor);
        if (groupPlaced.Test(group))
            QueryGroup(group, &tree->boxes[group]);
        cursor.Next();
    }
}

#ifdef FULL_TU_CONTEXT
// Unmatched: 27 differing instructions in sentinel/counter allocation and one extra loop-exit word; 114 recorded states agree at 82% block coverage.
void PhysicsScene::CollectIslandPairs(unsigned int passes, unsigned int pairLimit, unsigned int stepLimit)
{
    visited.ClearAll();
    wakeHead = ~0u;
    unsigned int head = awakeHead;
    collisionWork->pairCount = 0;
    unsigned other;
    PhysicsPairNode* node;
    unsigned int tail;
    unsigned int steps = 0;
    unsigned int pass = 0;
    unsigned int pairs = 0;
    unsigned empty = ~0u;
    unsigned int current;
    while(head != ~0u) {
        tail=empty;
        current=head;
        while(current != ~0u){
            if (++steps > stepLimit && pass > 0)
                return;
            visited.Set(current);
            unsigned int* link = reinterpret_cast<unsigned*>((current*sizeof(unsigned))+reinterpret_cast<unsigned>(links));
            unsigned int next = *link;
            if (pass > 0) {
                if (quiet.Test(current)) {
                    quiet.Clear(current);
                } else {
                    *link = wakeHead;
                    wakeHead = current;
                }
            }
            for (node = shapePairs[current]; node; node = node->next) {
                other = node->partner->index;
                if (visited.Test(other))
                    continue;
                if (++pairs > pairLimit)
                    return;
                if(!collisionWork->AppendPair(instances[other],instances[current]))return;
                if (!instanceFixed.Test(other) && !queued.Test(other)) {
                    links[other] = tail;
                    queued.Set(other);
                    tail = other;
                }
            }
            for (node = exclusions[current]; node; node = node->next) {
                other = node->partner->index;
                if (!visited.Test(other) && !instanceFixed.Test(other) && !queued.Test(other)) {
                    links[other] = tail;
                    queued.Set(other);
                    tail = other;
                }
            }
            current=next;
        }
        if(++pass>passes)return;
        head=tail;
    }
}
#endif

void PhysicsScene::PublishSleepWake()
{
    for (unsigned ordinal = wakeHead; ordinal != ~0u; ordinal = links[ordinal]) {
        PhysicsBody* body = instances[ordinal]->body;
        func_0037CF60(body->solver, body);
    }
    // Reading Begin's word retains its original aggregate construction temporary.
    PhysicsBitCursor cursor(quiet.Begin().word, 0);
    while (PhysicsCursorAdvanceSet(cursor, quiet.End())) {
        PhysicsBody* body = instances[quiet.IndexOf(cursor)]->body;
        if ((body->state & 7) != 2)
            func_0037CFD0(body->solver, body);
        cursor.Next();
    }
}

#include "physics/startup_constants.h"

using namespace PhysicsStartup;
// The named union member supplies a real 128-bit view under strict aliasing.
// XYZ are written; the fourth stack lane is transported unchanged.
struct SceneVectorTemporary {
    union {
        struct { volatile float x, y, z, unspecifiedW; } scalar;
        volatile EeS128 native;
    };
    SceneVectorTemporary(float first, float second, float third)
    {
        scalar.x = first;
        scalar.y = second;
        scalar.z = third;
    }
    operator EeS128() const { return *(const volatile EeS128*)&native; }
} __attribute__((aligned(16)));

extern "C" {
extern StartupToken D_0040E848, D_0040E850;
extern ConstantQuad D_0045CC30, D_0045CC40, D_0045CC50, D_0045CC60;
StartupToken* func_00100228(StartupToken*);
StartupToken* func_00100258(StartupToken*);
void func_00100260(StartupToken*, int);
void func_00100230(StartupToken*, int);
}
__asm__(".extern D_0040E848,8\n.extern D_0040E850,8");

extern "C" void func_0032DF00(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            func_00100228(&D_0040E848);
            func_00100258(&D_0040E850);
            SceneVectorTemporary a(1.5707963705062866f, -0.15915493667125702f, 12582912.0f);
            EeS128 qa = (EeS128)a;
            SceneVectorTemporary b(-0.15915493667125702f, 0.5f, 0.25f);
            EeS128 qb = (EeS128)b;
            SceneVectorTemporary c(-76.57495880126953f, -41.3416748046875f, 81.60222625732422f);
            EeS128 qc = (EeS128)c;
            SceneVectorTemporary d(39.71065902709961f, 6.283185005187988f, 0.0f);
            EeS128 qd = (EeS128)d;
            D_0045CC30.value = qa;
            D_0045CC40.value = qb;
            D_0045CC50.value = qc;
            D_0045CC60.value = qd;
        } else {
            func_00100260(&D_0040E850, 2);
            func_00100230(&D_0040E848, 2);
        }
    }
}

extern "C" {
StartupToken D_0040E848 __attribute__((section(".sbss")));
StartupToken D_0040E850 __attribute__((section(".sbss")));
ConstantQuad D_0045CC30, D_0045CC40, D_0045CC50, D_0045CC60;
}


#ifdef FULL_TU_CONTEXT
static inline int SceneFloatWord(float value){int result;asm volatile("mfc1 %0,%1":"=r"(result):"f"(value));return result;}
static inline PhysicsVec SceneScalarX(int input){PhysicsVec value;asm volatile("qmtc2.ni %1,%0":"=j"(value):"r"(input));return value;}
static inline PhysicsVec SceneScalarY(int input){PhysicsVec value;asm("qmtc2.ni %1,%0":"=j"(value):"r"(input));return value;}
static inline PhysicsVec SceneScalarZ(int input){PhysicsVec value;asm("qmtc2.ni %1,%0":"=j"(value):"r"(input));return value;}
static inline PhysicsVec SceneComponentX(PhysicsVec value,PhysicsVec scalar){asm("vaddx.x %0,vf0,%1x":"+j"(value):"j"(scalar));return value;}
static inline PhysicsVec SceneComponentY(PhysicsVec value,PhysicsVec scalar){asm("vaddx.y %0,vf0,%1x":"+j"(value):"j"(scalar));return value;}
static inline PhysicsVec SceneComponentZ(PhysicsVec value,PhysicsVec scalar){asm("vaddx.z %0,vf0,%1x":"+j"(value):"j"(scalar));return value;}
static inline void ScenePublish(PhysicsVec* address,PhysicsVec value){*(volatile PhysicsVec*)address=value;}
static inline float SceneExtent(float scale){float result;asm("mul.s %0,%1,%2":"=f"(result):"f"(scale),"f"(1000.f));return result;}
static inline float SceneNegate(float value){float result;asm volatile("neg.s %0,%1":"=f"(result):"f"(value));return result;}
// Unmatched: 19 ordering differences in original Y/Z and store/return scheduling; 256 artificial inputs still disagree on VU outputs.
extern "C" PhysicsSceneSettings* func_0032E048(PhysicsSceneSettings* settings,unsigned groups,unsigned instances,unsigned pairs,unsigned unknown,unsigned joints,float scale){
 PhysicsVec highX,lowX,px,py,highY,nx,ny,nz,lowY,pz;
 float extent=SceneExtent(scale);
 highX=settings->maximum;lowX=settings->minimum;
 settings->groups=groups;settings->pairBudget=pairs;
 int positive=SceneFloatWord(extent);px=SceneScalarX(positive);py=SceneScalarY(positive);
 highX=SceneComponentX(highX,px);highY=SceneComponentY(highX,py);
 settings->solverBodies=instances;float low=SceneNegate(extent);
 ScenePublish(&settings->maximum,highX);ScenePublish(&settings->maximum,highY);
 int negative=SceneFloatWord(low);nx=SceneScalarX(negative);ny=SceneScalarY(negative);
 lowX=SceneComponentX(lowX,nx);nz=SceneScalarZ(negative);lowY=SceneComponentY(lowX,ny);
 ScenePublish(&settings->minimum,lowX);ScenePublish(&settings->minimum,lowY);
 pz=SceneScalarZ(positive);lowY=SceneComponentZ(lowY,nz);highY=SceneComponentZ(highY,pz);
 settings->solverJoints=joints;settings->unknown38=unknown;settings->scale=scale;
 ScenePublish(&settings->minimum,lowY);ScenePublish(&settings->maximum,highY);settings->instances=instances;return settings;
}
#endif

extern "C" PhysicsStorageRequirement* func_0032E0E0(PhysicsStorageRequirement* storage,const PhysicsSceneSettings* settings){
    PhysicsSceneLayout layout=func_0032BC70(settings);
    storage->alignment=128;
    storage->size=layout.total;
    return storage;

}

extern "C" void func_0032E120(PhysicsScene* scene, PhysicsCollisionDefinitions* definitions)
{
    PhysicsStorageBlock storage;
    scene->collisionDefinitions = definitions;
    PhysicsCollisionWork* oldWork = scene->collisionWork;
    if (oldWork) {
        func_0032FAF0(oldWork);
        scene->collisionWork = 0;
    }
    PhysicsSolver* solver = scene->solver;
    if (definitions) {
        func_0037CE60(solver, definitions->shapeDefinitions, definitions->shapeCount, definitions->meshCount);
        storage.memory = definitions->workMemory;
        PhysicsCollisionWork* work = func_0032E710(&storage, definitions->pairCapacity, scene->solver);
        scene->collisionWork = work;
        return;
    }
    func_0037CE60(solver, 0, 0, 0);
}

extern "C" int func_0032E1B0(PhysicsScene* scene,const PhysicsCompound* compound){
    int valid=0;
    if(compound){
    unsigned group=compound->ordinal;
    if(group<scene->groupCapacity&&scene->groups[group]==compound)valid=scene->groupUsed.Test(group);

}return valid;

}

void PhysicsScene::SetCompoundUpdateMask(PhysicsCompound* compound,int enabled){PhysicsScene* scene=this;
 unsigned count=compound->instanceCount;
 for(unsigned i=0;i<count;++i)func_0032E2A0(scene,&compound->instances[i],enabled);
}

extern "C" void func_0032E2A0(PhysicsScene* scene,PhysicsInstance* instance,int enabled){
    if(enabled){
    unsigned ordinal=instance->ordinal;
    scene->boundsDirty.Set(ordinal);

}else{
    unsigned ordinal=instance->ordinal;
    scene->boundsDirty.Clear(ordinal);

}
}

extern "C" PhysicsSolver* func_0032E320(PhysicsScene* scene){return scene->solver;}

extern "C" void func_0032E328(PhysicsScene* scene){
    func_0032D248(scene);
    func_0032D358(scene);
    func_0032D590(scene);
    func_0032D7C0(scene);
    func_0032D990(scene,scene->islandPasses,scene->pairBudget,scene->instanceCapacity);
    func_0032DCE8(scene);
    func_0032FAF8(scene->collisionWork);
    func_0037C4E0(scene->solver);

}

extern "C" void func_0032DF00(int,int);
extern "C" void func_0032E390(){func_0032DF00(1,65535);}
extern "C" void func_0032E3B0(){func_0032DF00(0,65535);}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032BDC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032C0D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032C5A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032D238);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032D990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032E048);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032E208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032E310);
