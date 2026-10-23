// Scene storage, broadphase pools and bitmap iteration; PS2 member offsets are in scene.hpp.
#include "physics/scene.hpp"

#ifdef BLACK_NONMATCHING
// Unmatched: storage-layout arithmetic scheduling and aggregate return registers.
extern "C" PhysicsSceneLayout func_0032BC70(const PhysicsSceneSettings* settings){
 PhysicsStorageRequirement tree,solver;PhysicsBounds bounds;
 func_00334028(&tree,settings->groups,&bounds);
 func_0037CDF0(&solver,settings->solverBodies,settings->solverJoints);
 PhysicsSceneLayout layout;
 layout.pairs=(settings->pairBudget+settings->solverJoints)*2;
 layout.treeAlignment=tree.alignment;layout.treeSize=tree.size;
 layout.solverAlignment=solver.alignment;layout.solverSize=solver.size;
 unsigned size=PhysicsAlignUp((settings->instances+8)<<5,tree.alignment)+tree.size;
 size=PhysicsAlignUp(PhysicsAlignUp(size,solver.alignment)+solver.size,128);
 layout.total=size+(settings->groups+settings->instances)*4+((settings->instances+31)>>5)*28+((settings->groups+31)>>5)*12+(settings->instances+layout.pairs)*16;
 return layout;
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: allocation layout and inline bitmap initialization register allocation.
extern "C" PhysicsScene* func_0032BDC0(PhysicsStorageBlock* storage, const PhysicsSceneSettings* settings)
{
    PhysicsSceneLayout layout = func_0032BC70(settings);
    PhysicsScene* scene = static_cast<PhysicsScene*>(storage->memory);
    scene->scale = settings->scale;
    scene->wakeHead = ~0u;
    scene->awakeHead = ~0u;
    scene->islandPasses = 100;
    scene->groupMask = 0;
    scene->instanceCapacity = settings->instances;
    scene->pairBudget = settings->pairBudget;
    scene->groupCapacity = settings->groups;
    scene->boxes = reinterpret_cast<PhysicsBounds*>(reinterpret_cast<char*>(scene) + 0x100);
    scene->pairNodeCount = layout.pairs;
    unsigned int offset = PhysicsAlignUp((settings->instances + 8) << 5, layout.treeAlignment);
    PhysicsSpatialTree* tree = reinterpret_cast<PhysicsSpatialTree*>(reinterpret_cast<char*>(scene) + offset);
    offset += layout.treeSize;
    scene->tree = func_003339A0(tree,settings->groups,settings);
    offset = PhysicsAlignUp(offset, layout.solverAlignment);
    PhysicsStorageBlock solverStorage;
    solverStorage.memory = reinterpret_cast<char*>(scene) + offset;
    solverStorage.unknown4 = 0;
    scene->solver = func_0037C238(&solverStorage,settings->solverBodies,settings->solverJoints);
    scene->collisionWork = 0;
    scene->solver->contactMargin = settings->scale * 0.2f;
    offset = PhysicsAlignUp(offset + layout.solverSize, 128);
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

#ifdef BLACK_NONMATCHING
// Unmatched: inlined spatial query, pair callbacks and EE vector register lifetimes.
static float Separation(const PhysicsBounds& a,const PhysicsBounds& b){
 PhysicsVec x=PhysicsSub(b.low,a.high),y=PhysicsSub(a.low,b.high);
 float gx=PhysicsLane(x,0)>PhysicsLane(y,0)?PhysicsLane(x,0):PhysicsLane(y,0);
 float gy=PhysicsLane(x,1)>PhysicsLane(y,1)?PhysicsLane(x,1):PhysicsLane(y,1);
 float gz=PhysicsLane(x,2)>PhysicsLane(y,2)?PhysicsLane(x,2):PhysicsLane(y,2);
 float xy=gx>gy?gx:gy;return xy>gz?xy:gz;
}
void PhysicsScene::AllocatePair(unsigned first,unsigned second){PhysicsPairNode* a=freePairs;PhysicsPairNode* b=a->next;freePairs=b->next;a->index=first;a->next=shapePairs[first];if(a->next)a->next->previous=a;a->previous=0;shapePairs[first]=a;b->index=second;b->next=shapePairs[second];if(b->next)b->next->previous=b;b->previous=0;shapePairs[second]=b;}

int PhysicsScene::PairGroups(unsigned int first, unsigned int second)
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
        unsigned int index = firstClass < secondClass ? firstClass * groupMask->stride + secondClass
                                                      : secondClass * groupMask->stride + firstClass;
        if (groupMask->Test(index))
            return 0;
    }
    if (first == second)
        selfMask = (PhysicsPairMask*)compound->selfMask;
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

#ifdef BLACK_NONMATCHING
// Unmatched: VU0 matrix composition and lane payload lifetimes.
int PhysicsScene::UpdateShapeBounds(PhysicsInstance* instance,unsigned ordinal){
 PhysicsMatrix world;
 if(instance->body){
  PhysicsMatrix body;
  const PhysicsBody* b=instance->body;
  body.row[0]=*(const PhysicsVec*)((const char*)b+0x40);body.row[1]=*(const PhysicsVec*)((const char*)b+0x50);body.row[2]=*(const PhysicsVec*)((const char*)b+0x60);body.row[3]=*(const PhysicsVec*)((const char*)b+0x10);
  if(instance->offset){world.row[0]=PhysicsDirection(body,instance->offset->row[0]);world.row[1]=PhysicsDirection(body,instance->offset->row[1]);world.row[2]=PhysicsDirection(body,instance->offset->row[2]);world.row[3]=PhysicsPosition(body,instance->offset->row[3]);}else world=body;
 }else world=instance->frame;
 PhysicsShape* shape=instance->shape;PhysicsBoundsCallback* cb=shape->worldBounds;
 if(cb->invoke((char*)shape+cb->adjustment,&world,0,&boxes[ordinal])){
  boundsValid.Set(ordinal);
  if(!instanceFixed.Test(ordinal)){
   PhysicsVec step=instance->body->linearStep;
   float distance=PhysicsAbs(PhysicsLane(step,0))+PhysicsAbs(PhysicsLane(step,1))+PhysicsAbs(PhysicsLane(step,2));
   PhysicsVec margin=PhysicsAddScalar(*D_0040E408,distance);
   boxes[ordinal].low=PhysicsSub(boxes[ordinal].low,margin);boxes[ordinal].high=PhysicsAdd(boxes[ordinal].high,margin);
  }return 1;
 }
 boundsValid.Clear(ordinal);return 0;
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: bounds aggregate copies and paired-list register allocation.
int PhysicsScene::RebuildGroupBounds(unsigned group,PhysicsBounds* bounds){
 int found=0;unsigned count=groups[group]->instanceCount;
 for(unsigned i=0;i<count;++i){
  unsigned ordinal=groups[group]->instances[i].ordinal;
  while(shapePairs[ordinal]){PhysicsPairNode* node=shapePairs[ordinal];ReleasePairNode(node,shapePairs);ReleasePairNode(node->partner,shapePairs);}
  if(boundsValid.Test(ordinal)){
   if(!found){*bounds=boxes[ordinal];found=1;}else *bounds=func_00394E20(bounds,&boxes[ordinal]);
  }
 }
 if(found)groupPlaced.Set(group);else groupPlaced.Clear(group);
 return found;
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: bitmap cursor temporary storage and inline lowering.
extern "C" unsigned func_0032CA68(const PhysicsBitmap* bitmap){
 unsigned* words=bitmap->words;unsigned bits=bitmap->bitCount;
 PhysicsBitCursor cursor(words,0),end(words+(bits>>5),bits&31);
 cursor.AdvanceClear(&end);return (cursor.word-words)*32+cursor.bit;
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: compound instance/joint loop scheduling.
static unsigned FirstClear(const PhysicsBitmap* bitmap){PhysicsBitCursor c=bitmap->Begin(),end=bitmap->End();c.AdvanceClear(&end);return bitmap->IndexOf(c);}
static unsigned AllocateBit(PhysicsBitmap* bitmap){unsigned n=func_0032CA68(bitmap);bitmap->Set(n);return n;}
void PhysicsScene::RegisterCompound(PhysicsCompound* compound, unsigned int mode)
{
    unsigned int count = compound->instanceCount;
    unsigned int group = func_0032CA68(&groupUsed);
    compound->ordinal = group;
    func_0032AE70(compound,solver,mode);
    groupUsed.Set(group);
    groupPlaced.Clear(group);
    groups[group] = compound;
    ++groupCount;
    for (unsigned int i = 0; i < count; ++i) {
        unsigned int ordinal = AllocateBit(&instanceUsed);
        ++instanceCount;
        instances[ordinal] = &compound->instances[i];
        instances[ordinal]->ordinal = ordinal;
        shapePairs[ordinal] = 0;
        exclusions[ordinal] = 0;
        boundsDirty.Set(ordinal);
        boundsValid.Clear(ordinal);
        compound->instances[i].body->ordinal = ordinal;
        groupOf[ordinal] = group;
        if (mode == 1)
            instanceFixed.Set(ordinal);
        else
            instanceFixed.Clear(ordinal);
    }
    for (unsigned int j = 0; j < compound->jointCount; ++j) {
        PhysicsJoint* joint = &compound->joints[j];
        AddExclusion(joint->a->ordinal, joint->b->ordinal);
    }
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: paired-list removal allocation and inlining.
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
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: bitmap clear loop code generation and short-loop padding.
void PhysicsScene::ResetPairPools()
{
    freePairs = pairNodes;
    unsigned int i;
    for (i = 0; i < pairNodeCount; ++i) {
        pairNodes[i].next = &pairNodes[i] + 1;
        pairNodes[i].partner = &pairNodes[i - (i & 1) * 2 + 1];
    }
    pairNodes[pairNodeCount - 1].next = 0;
    groupUsed.ClearAll();
    instanceUsed.ClearAll();
    boundsDirty.ClearAll();
    groupCount = 0;
    instanceCount = 0;
    exclusionCount = 0;
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: bitmap clear loops and body-list scheduling.
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
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: bitmap cursor aggregate temporaries and scheduling.
void PhysicsScene::UpdateDirtyBounds()
{
    groupDirty.ClearAll();
    PhysicsBitCursor cursor = boundsDirty.Begin();
    for (PhysicsBitCursor end = boundsDirty.End(); cursor.AdvanceSet(&end); end.word = boundsDirty.words + (boundsDirty.bitCount >> 5), end.bit = boundsDirty.bitCount & 31) {
        unsigned int ordinal = boundsDirty.IndexOf(cursor);
        unsigned int bit = cursor.bit;
        func_0032C5A0(this,instances[ordinal],ordinal);
        groupDirty.Set(groupOf[ordinal]);
        boundsDirty.Clear(ordinal);
        cursor.bit = ++bit;
        if (bit == 32) {
            unsigned int* nextWord = cursor.word + 1;
            cursor.bit = 0;
            cursor.word = nextWord;
        }
    }
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: inlined bitmap cursor and bounds rebuild scheduling.
void PhysicsScene::UpdateSpatialGroup(unsigned int group)
{
    PhysicsBounds bounds;
    if (groupPlaced.Test(group)) {
        if (RebuildGroupBounds(group, &bounds)) {
            PhysicsSpatialTree* groupTree = tree;
            func_00333808(groupTree,group);
            func_003333A8(groupTree,group,&bounds);
        } else {
            func_00333808(tree,group);
        }
    } else if (RebuildGroupBounds(group, &bounds)) {
        func_003333A8(tree,group,&bounds);
    }
}

void PhysicsScene::UpdateDirtyGroups()
{
    PhysicsBitCursor cursor = groupDirty.Begin();
    for (PhysicsBitCursor end = groupDirty.End(); cursor.AdvanceSet(&end); end.word = groupDirty.words + (groupDirty.bitCount >> 5), end.bit = groupDirty.bitCount & 31) {
        unsigned int bit = cursor.bit;
        unsigned int group = groupDirty.IndexOf(cursor);
        UpdateSpatialGroup(group);
        cursor.bit = ++bit;
        if (bit == 32) {
            unsigned int* nextWord = cursor.word + 1;
            cursor.bit = 0;
            cursor.word = nextWord;
        }
    }
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: bitmap cursor temporary lifetime and scheduling.
void PhysicsScene::QueryDirtyGroups()
{
    PhysicsBitCursor cursor = groupDirty.Begin();
    for (PhysicsBitCursor end = groupDirty.End(); cursor.AdvanceSet(&end); end = groupDirty.End()) {
        unsigned int group = groupDirty.IndexOf(cursor);
        unsigned int bit = cursor.bit;
        if (groupPlaced.Test(group))
            QueryGroup(group, &tree->boxes[group]);
        if (++bit == 32) { ++cursor.word; bit = 0; }
        cursor.bit = bit;
    }
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: bounded island traversal register allocation and inline pair publication.
void PhysicsScene::CollectIslandPairs(unsigned int passes, unsigned int pairLimit, unsigned int stepLimit)
{
    visited.ClearAll();
    collisionWork->pairCount = 0;
    wakeHead = ~0u;
    unsigned int head = awakeHead;
    unsigned int tail;
    unsigned int pass = 0;
    unsigned int pairs = 0;
    unsigned int steps = 0;
    while (head != ~0u) {
        tail = ~0u;
        do {
            if (++steps > stepLimit && pass > 0)
                return;
            visited.Set(head);
            unsigned int* link = &links[head];
            unsigned int next = *link;
            if (pass > 0) {
                if (quiet.Test(head)) {
                    quiet.Clear(head);
                } else {
                    *link = wakeHead;
                    wakeHead = head;
                }
            }
            for (PhysicsPairNode* node = shapePairs[head]; node; node = node->next) {
                unsigned int other = node->partner->index;
                if (visited.Test(other))
                    continue;
                if (++pairs > pairLimit)
                    return;
                PhysicsInstance* second = instances[head];
                PhysicsInstance* first = instances[other];
                PhysicsCollisionWork* work = collisionWork;
                if (work->pairCount == work->pairCapacity)
                    return;
                PhysicsCollisionPair* pair = &work->pairs[work->pairCount++];
                pair->second = first;
                pair->first = second;
                if (!instanceFixed.Test(other) && !queued.Test(other)) {
                    links[other] = tail;
                    queued.Set(other);
                    tail = other;
                }
            }
            for (PhysicsPairNode* node = exclusions[head]; node; node = node->next) {
                unsigned int other = node->partner->index;
                if (!visited.Test(other) && !instanceFixed.Test(other) && !queued.Test(other)) {
                    links[other] = tail;
                    queued.Set(other);
                    tail = other;
                }
            }
            head = next;
        } while (head != ~0u);
        if (++pass > passes)
            return;
        head = tail;
    }
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: bitmap cursor aggregate temporaries and body-bank registers.
void PhysicsScene::PublishSleepWake()
{
    for (unsigned int ordinal = wakeHead; ordinal != 0xffffffff; ordinal = links[ordinal]) {
        PhysicsBody* body = instances[ordinal]->body;
        func_0037CF60(body->solver,body);
    }
    PhysicsBitCursor cursor = quiet.Begin();
    PhysicsBitCursor end = quiet.End();
    while (cursor.AdvanceSet(&end)) {
        unsigned int bit = cursor.bit;
        PhysicsBody* body = instances[quiet.IndexOf(cursor)]->body;
        if ((body->state & 7) != 2) {
            cursor.bit = bit;
            func_0037CFD0(body->solver,body);
        }
        cursor.bit = ++bit;
        if (bit == 32) {
            unsigned int* next = cursor.word + 1;
            cursor.bit = 0;
            cursor.word = next;
        }
        end.word = quiet.words + (quiet.bitCount >> 5);
        end.bit = quiet.bitCount & 31;
    }
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: static vector constant construction and gp-relative initialization.
struct PhysicsConstants {float x,y,z,w;} __attribute__((aligned(16)));
extern "C" {extern unsigned D_0040E848[2],D_0040E850[2];extern PhysicsConstants D_0045CC30,D_0045CC40,D_0045CC50,D_0045CC60;void func_00100228(void*);void func_00100258(void*);void func_00100260(void*,int);void func_00100230(void*,int);}
extern "C" void func_0032DF00(int initialize,int priority){
 if(priority==65535){if(initialize){
 func_00100228(D_0040E848);func_00100258(D_0040E850);
 PhysicsConstants a;a.x=1.5707963705062866f;a.y=-0.15915493667125702f;a.z=12582912.0f;PhysicsConstants b;b.x=-0.15915493667125702f;b.y=0.5f;b.z=0.25f;PhysicsConstants c;c.x=-76.57495880126953f;c.y=-41.3416748046875f;c.z=81.60222625732422f;PhysicsConstants d;d.x=39.71065902709961f;d.y=6.283185005187988f;d.z=0.0f;
 D_0045CC30=a;D_0045CC40=b;D_0045CC50=c;D_0045CC60=d;
 }else{func_00100260(D_0040E850,2);func_00100230(D_0040E848,2);}}
}
#endif

#ifdef BLACK_NONMATCHING
// Unmatched: VU0 lane assignment and scalar store scheduling.
extern "C" PhysicsSceneSettings* func_0032E048(PhysicsSceneSettings* settings,unsigned groups,unsigned instances,unsigned pairs,unsigned unknown,unsigned joints,float scale){
 float extent=scale*1000.f;settings->groups=groups;settings->pairBudget=pairs;
 settings->maximum=PhysicsWithX(settings->maximum,PhysicsFloatBits(extent));settings->maximum=PhysicsWithY(settings->maximum,PhysicsFloatBits(extent));
 settings->solverBodies=instances;float low=-extent;
 settings->minimum=PhysicsWithX(settings->minimum,PhysicsFloatBits(low));settings->minimum=PhysicsWithY(settings->minimum,PhysicsFloatBits(low));settings->minimum=PhysicsWithZ(settings->minimum,PhysicsFloatBits(low));settings->maximum=PhysicsWithZ(settings->maximum,PhysicsFloatBits(extent));
 settings->solverJoints=joints;settings->unknown38=unknown;settings->scale=scale;settings->instances=instances;return settings;
}
#endif

extern "C" PhysicsStorageRequirement* func_0032E0E0(PhysicsStorageRequirement* storage,const PhysicsSceneSettings* settings){
    PhysicsSceneLayout layout=func_0032BC70(settings);
    storage->alignment=128;
    storage->size=layout.total;
    return storage;

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
