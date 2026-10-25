#include "include_asm.h"

#include "kynapse/behaviors/flee_queries.hpp"
namespace FleeRecovery {
    

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D1BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D23B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D27D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2A60);
