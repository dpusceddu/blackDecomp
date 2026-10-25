#include "include_asm.h"

#include "kynapse/flee_agent.hpp"
using namespace FleeViews;
extern unsigned int D_003E2A58[],D_003E2AE0,D_0044ECD0;
extern unsigned int *D_0044EDE0;
extern "C" void func_002E00F0(void *,const char *,void *(*)(),int,int,int);
extern "C" void *func_002D1610();
extern "C" int func_002DFF98(FleeAgent *,int);
extern int (*D_003C87E0)(void *);

extern "C" void func_002D2CE8(int initialize,int priority) {
    if (priority==0xffff) {
        if (initialize) {
            func_002E00F0(&D_0044ECD0,"CFleeAgent",func_002D1610,0,0,0);
            return;
        }
        D_0044EDE0=&D_003E2AE0;
    }
}
extern "C" int func_002D2DB8(FleeAgent *self,int flags) {
    *(void **)self=D_003E2A58;
    if (self->points)D_003C87E0((char *)self->points-0x10);
    if (self->entities)D_003C87E0(self->entities);
    func_002DFF98(self,0);
    int result=flags&1;
    if (result)result=D_003C87E0(self);
    return result;
}
extern "C" void func_002D2EE8(FleeAgent *self) {
    self->pointCount=0;
    self->pathId=0x7fffffff;
}
extern "C" void func_002D2F40(FleeAgent *self) {
    self->entityCount=0;
}
namespace FleeViews {
    float FleeAgent::Rate(void *,int blocked,float sum,int depth) {
        return (sum/(float)(depth+1))/(float)(blocked*10+1);
    }
    int FleeAgent::AddPoint(const Vec3 *point) {
        if (pointCount>=maxPoints)return 0;
        points[pointCount]=*point;
        ++pointCount;
        return 1;
    }
    int FleeAgent::AddEntity(Actor *actor) {
        if (entityCount>=maxEntities)return 0;
        entities[entityCount]=actor;
        ++entityCount;
        return 1;
    }
}
extern "C" void func_002D2FB8() {
    func_002D2CE8(1,0xffff);
}
extern "C" void func_002D2FD8() {
    func_002D2CE8(0,0xffff);
}

#ifdef NONMATCHING
// Unmatched: independent initialization stores are scheduled differently.
namespace FleeViews {
    FleeAgent::FleeAgent(Context *context):Behavior(context),graphSlot((unsigned int)-1) {
        maxEntities=20;
        pathId=0x7fffffff;
        provider=0;
        graph=0;
        unknown18=0;
        perception=0;
        maxPoints=20;
        points=0;
        entities=0;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: validation branch and return layout differs.
extern "C" int func_002D2F48(FleeAgent *self) {
    if (!self->graph) return 0;
    if (self->pointCount != 0) return 1;
    if (self->entityCount != 0) return 1;
    return 0;
}
#endif

#ifdef NONMATCHING
// Unmatched: configuration return branches differ.
extern const char D_00404098[];
extern const char D_00404088[];
extern const char D_00404080[];
extern const char D_00404070[];
extern const char D_00404068[];
extern const char D_00404058[];
extern const char D_00404048[];
extern const char D_00404030[];
namespace FleeViews {
    bool Kaim_InCorridor(const Vec3 *, const Vec3 *, const Vec3 *) __asm__("func_002D27D8");
}
namespace FleeViews {
    bool FleeAgent::Configure(ChildBuffers* entry)
   {
        if (entry) {
            const char* key = entry->GetSecond();
            if (!func_00360838(key, D_00404030)) {
                const char* value = entry->GetValue();
                if (value) {
                    interval = func_00291C68(func_0035E730(value));
                    return true;
                }
            }
            else if (!func_00360838(key, D_00404048)) {
                const char* value = entry->GetValue();
                if (value) {
                    pathLength = func_0035E750(value);
                    return true;
                }
            }
            else if (!func_00360838(key, D_00404058)) {
                const char* value = entry->GetValue();
                if (value) {
                    stopWhenHidden = func_00360838(value, D_00404068) != 0;
                    return true;
                }
            }
            else if (!func_00360838(key, D_00404070)) {
                const char* value = entry->GetValue();
                if (value) {
                    long parsed = func_0035E730(value);
                    Engine* engine = gEngine;
                    maxDeltaHeight = func_00291C68(parsed) * engine->unit;
                    return true;
                }
            }
            else if (!func_00360838(key, D_00404080)) {
                const char* value = entry->GetValue();
                if (value) {
                    ItemList* list = (ItemList*)((ClassRegistryB*)gEngine)->FindByClass(&gTypeListClass);
                    if (!list)
                    return false;
                    void* id = list->IdByName(value);
                    if (!id)
                    return false;
                    return SetGraph(id);
                }
            }
            else if (!func_00360838(key, D_00404088)) {
                const char* value = entry->GetValue();
                if (value) {
                    maxPoints = func_0035E750(value);
                    return true;
                }
            }
            else if (!func_00360838(key, D_00404098)) {
                const char* value = entry->GetValue();
                if (value) {
                    maxEntities = func_0035E750(value);
                    return true;
                }
            }
            if (entry && entry->GetSecond() && *entry->GetSecond() == '_')
            return true;
        }
        return false;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: array-cookie construction and stack/register lifetimes differ.
namespace FleeViews {
    bool Kaim_InCorridor(const Vec3 *, const Vec3 *, const Vec3 *) __asm__("func_002D27D8");
}
namespace FleeViews {
    bool FleeAgent::Init(ChildBuffers* config)
   {
        float unit = gEngine->unit;
        requery = unit * unit;
        lastQuery = gOrigin;
        node = 0;
        danger = true;
        valid = true;
        destination = gOrigin;
        initialized = false;
        maxDeltaHeight = gEngine->unit;
        pointCount = 0;
        entityCount = 0;
        interval = 1.0f;
        pathLength = 2;
        stopWhenHidden = false;
        graph = 0;
        if (ConfigureAll(config)) {
            if (maxPoints > 0)
            points = (Vec3*)new PointCell[maxPoints];
            if (maxEntities)
            entities = (Actor**)KaimAllocate(maxEntities * 4);
            if (entities) {
                unsigned int i = 0;
                if (i < maxEntities) {
                    do {
                        entities[i] = 0;
                        ++i;
                    }
                    while (i < maxEntities);
                }
            }
            provider = (TargetEntity*)((ClassRegistryA*)context)->FindByClass(&gTargetClass);
            perception = (Perception*)((ClassRegistryA*)context)->FindByClass(&gPerceptionClass);
            ParameterTables* names = GetNameTables();
            dangerName = ((NameTable4*)names)->FindName("CFleeAgent::CheckDangerVisible");
            computeName = ((NameTable8*)names)->FindName("CFleeAgent::ComputeDestination");
            nextTime = 0;
            if (Prepare()) {
                if (Validate())
                return true;
            }
        }
        return false;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: registry/component loop registers differ.
namespace FleeViews {
    bool Kaim_InCorridor(const Vec3 *, const Vec3 *, const Vec3 *) __asm__("func_002D27D8");
}
namespace FleeViews {
    bool FleeAgent::SetGraph(void* id)
   {
        graph = (NodeGraph*)id;
        graphSlot = -1;
        node = 0;
        TypeList* types = (TypeList*)((ClassRegistryB*)gEngine)->FindByClass(&gTypeListClass);
        if (!types)
        return false;
        LookupService* slots = (LookupService*)((ClassRegistryB*)gEngine)->FindByClass(&gLookupClass);
        unsigned int i = 0;
        if (types->count > 0) {
            TypeEntry** cursor = types->entries;
            do {
                TypeEntry* entry = *cursor;
                if (entry->id == (int)graph) {
                    unsigned int j = 0;
                    if (entry->componentCount > 0) {
                        do {
                            if (entry->components[j]->GetClassInfo() == &gSectionClass) {
                                section = (NodeGraph*)entry->components[j];
                                break;
                            }
                            ++j;
                        }
                        while (j < entry->componentCount);
                    }
                    if (slots && !slots->Lookup(entry->key, &graphSlot))
                    graphSlot = -1;
                    return true;
                }
                ++i;
                ++cursor;
            }
            while (i < types->count);
        }
        return true;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: query-object lifetimes and visibility callback ABI differ.
namespace FleeViews {
    bool Kaim_InCorridor(const Vec3 *, const Vec3 *, const Vec3 *) __asm__("func_002D27D8");
}
namespace FleeViews {
    bool FleeAgent::Update()
   {
        float now = gNow;
        bank->ClearActivation();
        if (!initialized) {
            destination = context->actor->position;
            pathId = 0x7fffffff;
            pathFlag = -1;
            initialized = true;
        }
        ParameterTables* tables = GetNameTables();
        if (stopWhenHidden) {
            if (tables->Raise(dangerName, context->actor)) {
                danger = false;
                unsigned int i = 0;
                if (pointCount > 0) {
                    do {
                        Actor* actor = context->actor;
                        Vec3* to = &points[i];
                        const Vec3* from = &actor->position;
                        danger = danger | gVisibilityHook(from, to, actor, 1);
                        if (danger)
                        break;
                        ++i;
                    }
                    while (i < pointCount);
                }
                if (!danger) {
                    i = 0;
                    if (entityCount > 0) {
                        do {
                            danger = danger | (perception->GetRecord(entities[i])->hidden == false);
                            if (danger)
                            break;
                            ++i;
                        }
                        while (i < entityCount);
                    }
                }
            }
            if (!danger) {
                destination = context->actor->position;
                pathId = 0x7fffffff;
                pathFlag = -1;
                return true;
            }
        }
        unknown18 = 0;
        if (nextTime < now && tables->Consume(computeName, context->actor)) {
            valid = ComputeDestination();
            tables->Accumulate(computeName, context->actor);
            nextTime = now + interval;
        }
        if (!valid)
        return true;
        bool ok;
        int flag = pathFlag;
        int id;
        if (flag == -1 || (id = pathId) == 0x7fffffff) {
            ok = provider->Query(&destination);
        }
        else {
            FollowQuery query((const int*)&destination, id, flag);
            ok = provider->QueryTransform(&query);
        }
        if (!ok)
        return false;
        bank->Select(provider->id);
        return true;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: vector temporaries and distance-helper calls differ.
namespace FleeViews {
    bool Kaim_InCorridor(const Vec3 *, const Vec3 *, const Vec3 *) __asm__("func_002D27D8");
}
namespace FleeViews {
    bool FleeAgent::ComputeDestination()
   {
        Actor* actor = context->actor;
        Vec3 position = actor->position;
        destination = position;
        pathId = 0x7fffffff;
        pathFlag = -1;
        if (!graph)
        return false;
        bool lookup = true;
        if (node) {
            float dx = position.x - lastQuery.x;
            float dy = position.y - lastQuery.y;
            float dz = position.z - lastQuery.z;
            float squared = dx * dx + dy * dy + dz * dz;
            if (!(squared > requery))
            lookup = false;
        }
        if (lookup) {
            if (!section)
            node = Kaim_FindNearestNodeSimple(graph, &position, true, false);
            else
            node = NavigationGraph_QueryNode(&position, context->actor, maxDeltaHeight, section, 0, 0);
            lastQuery = context->actor->position;
        }
        if (!node)
        return false;
        float sum = 0;
        const Vec3* pointCursor = points;
        for (unsigned int remaining = pointCount; remaining != 0; --remaining, ++pointCursor) {
            float dx = node->position.x - pointCursor->x;
            float dy = node->position.y - pointCursor->y;
            float dz = node->position.z - pointCursor->z;
            sum = sqrtf(dx * dx + dy * dy + dz * dz) + sum;
        }
        Actor** entityCursor = entities;
        for (unsigned int remaining = entityCount; remaining != 0; --remaining, ++entityCursor) {
            Actor* entity = *entityCursor;
            float dx = node->position.x - entity->position.x;
            float dy = node->position.y - entity->position.y;
            float dz = node->position.z - entity->position.z;
            sum = sqrtf(dx * dx + dy * dy + dz * dz) + sum;
        }
        GraphNode* best = 0;
        ScorePath(&best, node, 0, pathLength, 0, sum);
        if (best) {
            destination = best->position;
            pathId = best->id;
            pathFlag = graphSlot;
        }
        return true;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: outgoing-edge enumeration is inlined in the target.
namespace FleeViews {
    bool Kaim_InCorridor(const Vec3 *, const Vec3 *, const Vec3 *) __asm__("func_002D27D8");
}
namespace FleeViews {
    float FleeAgent::ScorePath(GraphNode** result, GraphNode* from, int depth, int maxDepth, int blocked, float sum)
   {
        float score = Rate(*result, blocked, sum, depth);
        if (depth == maxDepth) {
            *result = from;
            return score;
        }
        FleeVisitor visitor;
        visitor.node = from;
        visitor.points = points;
        visitor.pointCount = pointCount;
        visitor.entities = entities;
        visitor.entityCount = entityCount;
        visitor.depth = depth;
        visitor.maxDepth = maxDepth;
        visitor.best = score;
        visitor.sum = sum;
        visitor.blocked = blocked;
        visitor.agent = this;
        visitor.bestNode = from;
        visitor.EnumerateOutgoingEdges(from);
        *result = visitor.bestNode;
        return visitor.best;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: vector normalization and squared-length helper temporaries differ.
namespace FleeViews {
    bool Kaim_InCorridor(const Vec3 *, const Vec3 *, const Vec3 *) __asm__("func_002D27D8");
}
namespace FleeViews {
    bool Kaim_InCorridor(const Vec3* origin, const Vec3* through, const Vec3* point)
   {
        float px = point->x - origin->x;
        float py = point->y - origin->y;
        float pz = point->z - origin->z;
        float dx = through->x - origin->x;
        float dy = through->y - origin->y;
        float dz = through->z - origin->z;
        float inverse = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);
        float nx = dx * inverse;
        float ny = dy * inverse;
        float nz = inverse * dz;
        float cx = ny * pz - nz * py;
        float cy = nz * px - pz * nx;
        float cz = py * nx - ny * px;
        float squared = cx * cx + cy * cy + cz * cz;
        float lateral;
        if (squared <= 0.0001f) {
            lateral = 0.0f;
        }
        else {
            float n = 1.0f / sqrtf(squared);
            lateral = fabsf((n * cy * nz - n * cz * ny) * px + (n * cz * nx - nz * cx * n) * py +
            (ny * cx * n - n * cy * nx) * pz);
        }
        float along = nx * px + ny * py + nz * pz;
        float width = gEngine->unit + gEngine->unit;
        if (lateral < width) {
            if (along >= 0.0f) {
                float length = nx * dx + ny * dy + nz * dz;
                if (length >= along)
                return true;
            }
        }
        return false;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: distance-helper temporaries and loop registers differ.
namespace FleeViews {
    bool Kaim_InCorridor(const Vec3 *, const Vec3 *, const Vec3 *) __asm__("func_002D27D8");
}
namespace FleeViews {
    bool FleeVisitor::OnEdge(GraphEdge* edge)
   {
        NodeGraph* owner = edge->graph;
        GraphNode* target;
        if (edge == &owner->syntheticEdge)
        target = &owner->syntheticStart;
        else
        target = &owner->nodes[owner->edgeStart[edge->index]];
        bool seen = false;
        int i = 0;
        if (pointCount > 0) {
            Vec3* point = points;
            do {
                seen = Kaim_InCorridor(&node->position, &target->position, point);
                if (seen)
                break;
                ++i;
                ++point;
            }
            while (i < pointCount);
        }
        if (!seen) {
            i = 0;
            if (entityCount > 0) {
                Actor** entity = entities;
                do {
                    seen = Kaim_InCorridor(&node->position, &target->position, &(*entity)->position);
                    if (seen)
                    break;
                    ++i;
                    ++entity;
                }
                while (i < entityCount);
            }
        }
        int count = blocked;
        if (seen)
        ++count;
        float total = sum;
        const Vec3* cursor = points;
        for (int k = pointCount; k > 0; --k, ++cursor) {
            const Vec3& p = *cursor;
            float dz = p.z - target->position.z;
            float dx = p.x - target->position.x;
            float dy = p.y - target->position.y;
            total = sqrtf(dz * dz + dx * dx + dy * dy) + total;
        }
        Actor** entityCursor = entities;
        for (int k = entityCount; k > 0; --k, ++entityCursor) {
            Actor* entity = *entityCursor;
            float dz = entity->position.z - target->position.z;
            float dx = entity->position.x - target->position.x;
            float dy = entity->position.y - target->position.y;
            total = sqrtf(dz * dz + dx * dx + dy * dy) + total;
        }
        GraphNode* chosen = 0;
        float score = agent->ScorePath(&chosen, target, depth + 1, maxDepth, count, total);
        if (score > best) {
            best = score;
            bestNode = chosen;
        }
        return true;
    }
}
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2D48);
