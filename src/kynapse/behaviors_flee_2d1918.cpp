#include "include_asm.h"

#include "kynapse/behaviors/flee_queries.hpp"
#ifdef NON_MATCHING
#include "kynapse/flee_agent.hpp"
#endif
namespace FleeViews {
    

int InitAgent::Initialize(ChildBuffers* config)
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
            points = (Vec3*)new FleeQueries::PointCell[maxPoints];
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
            if (!((FleeQueries::Checks*)this)->Prepare())goto failed;
            if (((FleeQueries::Checks*)this)->Validate())goto succeeded;
        }
failed:
        return 0;
succeeded:
        return 1;
    }
    bool FleeAgent::Update()
   {
        float now = gNow;
        bank->ClearActivation();
        if (!initialized) {
            destination = context->actor->position;
            pathId = 0x7fffffff;
            (unsigned&)pathFlag = 0xffffffffU;
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
                        Vec3* to = (Vec3*)(i*sizeof(Vec3)+(unsigned)points);
                        const Vec3* from = &actor->position;
                        (unsigned char&)danger = (unsigned char&)danger | FleeQueries::hooks.visibility(from, to, actor, 1);
                        if (danger)
                        break;
                        ++i;
                    }
                    while (i < pointCount);
                }
                if (!danger) {
                    i = 0;
                    while (i<entityCount) {
                            unsigned char visible = perception->GetRecord(entities[i])->hidden;
                            (unsigned char&)danger = (unsigned char&)danger | (visible==0);
                            if (danger)
                            break;
                            ++i;
                    }
                }
            }
            if (!danger) {
                destination = context->actor->position;
                pathId = 0x7fffffff;
                (unsigned&)pathFlag = 0xffffffffU;
                return true;
            }
        }
        unknown18 = 0;
        if (nextTime < now && tables->Consume(computeName, context->actor)) {
            valid = ComputeDestination();
            tables->Accumulate(computeName, context->actor);
            nextTime = now + interval;
        }
        if (valid) {
        bool ok;
        unsigned flag = (unsigned&)pathFlag;
        int id;
        if (flag != 0xffffffffU && (id=pathId)!=0x7fffffff) {
            FleeQueries::Query query(destination,id,flag);
            ok = provider->Query(&query);
        } else {
            ok = provider->QueryTransform(&destination);
        }
        if (!ok)
        return false;
        bank->Select(provider->id);
        return true;
        }
        return true;
    }
 }
namespace FleeQueries {int Checks::Validate(){if(!graph)return 0;if(pointCount)goto yes;if(!entityCount)return 0;yes:return 1;}}

#ifdef NON_MATCHING
using namespace FleeViews;
namespace FleeViews {
    bool Kaim_InCorridor(const Vec3 *, const Vec3 *, const Vec3 *) __asm__("func_002D27D8");
// Unmatched: registry/component loop registers differ.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_flee_2d1918", func_002D1BC8);
#endif
#ifdef NON_MATCHING
namespace FleeViews {
// Unmatched: vector temporaries and distance-helper calls differ.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_flee_2d1918", func_002D2098);
#endif
#ifdef NON_MATCHING
namespace FleeViews {
// Unmatched: outgoing-edge enumeration is inlined in the target.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_flee_2d1918", func_002D23B0);
#endif
#ifdef NON_MATCHING
namespace FleeViews {
// Unmatched: vector normalization and squared-length helper temporaries differ.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_flee_2d1918", func_002D27D8);
#endif
#ifdef NON_MATCHING
namespace FleeViews {
// Unmatched: distance-helper temporaries and loop registers differ.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_flee_2d1918", func_002D2A60);
#endif
