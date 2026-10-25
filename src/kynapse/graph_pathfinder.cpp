#include "include_asm.h"

#include "kynapse/graph/pathfinder.hpp"
namespace Kaim {
extern "C" long func_0035E730(const char*);
extern "C" float func_00291C68(long);

static inline float ParseFloat(const char *s){return func_00291C68(func_0035E730(s));}
static inline float Kaim_WorldUnit(){return gWorldScale?gWorldScale->unit:0.0f;}
static inline float Degrees_WrapUnsigned(float v){if(v>360.0f)v-=360.0f;else if(v<0.0f)v+=360.0f;return v;}
static inline bool Kaim_IsHiddenName(ChildBuffers* p){if(p){if(!p->GetSecond())return false;if(*p->GetSecond()=='_')return true;}return false;}
extern "C" void *func_00393A18(const char*);
extern "C" void *func_00393AC0(const char*);
extern "C" void *func_00393B68(const char*);
extern "C" void *func_00393C10(const char*);


void CPathFinder::Reset()
{
    route.Clear();
    activated = false;
    searchOk = false;
    startNode = 0;
    goalNode = 0;
    waypoint = -1;
    savedStart = 0;
    savedGoal = 0;
    restartSearch = false;
    turnState = 0;
    previous = controller->actor->position;
    target = previous;
    ControlChannel* channel = speedChannel;
    if (channel || (channel = speedChannelAlt) != 0)
        ResetChannel(channel, 0, true);
    channel = yawChannel;
    if (channel || (channel = turnChannel) != 0)
        ResetChannel(channel, 0, true);
    channel = verticalChannel;
    if (channel)
        ResetChannel(channel, 0, true);
    if (policy)
        policy->Reset();
}
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char CPathFinder::Initialize(ChildBuffers* definition)
{
    if (!definition)
        return 0;
    simpleMove = CPathFinder_GenerateMove;
    complexMove = CPathFinder_GenerateMove;
    stopCondition = (StopFn)CPathFinder_IsAtGoal;
    collectNode = CPathFinder_CollectNode;
    canGo = (GuardFn)Kaim_AlwaysTrue;
    moveModeCheck = (GuardFn)Kaim_AlwaysTrue;
    nextSubgoal = (SubgoalFn)CPathFinder_AdvanceSubgoal;
    InstallService(&gRouteTypeKey);
    SetGraphType(&gGraphTypeKey);
    distMinNewGoal = gWorldScale->unit * 0.5f;
    heightRadiusA = gWorldScale->unit * 0.75f;
    heightRadiusB = gWorldScale->unit * 0.75f;
    arrivalRadius = gWorldScale->unit;
    finalRadius = gWorldScale->unit * 3.0f;
    radius = gWorldScale->unit;
    maxDeltaAngle = 359.0f;
    maxYawSpeed = 360.0f;
    unknown4cLimit = 1;
    distSubgoalMax = gWorldScale->unit * 100.0f;
    widthRatio = 1.0f;
    holeHeight = gWorldScale->unit * 0.5f;
    corridorWidth = gWorldScale ? gWorldScale->unit : 0.0f;
    cpuPrudence = 0.2f;
    avoidCpuPeaks = false;
    unknownB4 = true;
    updateTorsoRotate = false;
    yawSmoothing = false;
    graph = 0;
    converter = gClassRegistry->FindConverter(&gConverterClass);
    ChildBuffers* disable = definition->FindBySecond("DisableDA");
    bool createAvoidance = true;
    if (disable) {
        const char* value = disable->GetValue();
        if (value) {
            if (!_stricmp(value, "1"))
                createAvoidance = false;
            else
                _stricmp(value, "0");
        }
    }
    if (createAvoidance) {
        ChildBuffers* classEntry = definition->FindBySecond("DynamicAvoidanceClass");
        if(classEntry){
         const char*className=classEntry->GetValue();
         if(className){AvoidanceFactory*factory=AIAvoidance_FindClass(className);if(factory)policy=(MovePolicy*)factory->create(this);else policy=(MovePolicy*)new PathAvoidance(this);}
         else policy=(MovePolicy*)new PathAvoidance(this);
        }else policy=(MovePolicy*)new PathAvoidance(this);
    }
    if (!ConfigureAll(definition))
        return 0;
    speeds = (SpeedTable*)controller->actor->GetAuthoredProperty(&gForwardKey);
    radiusHolder = (RadiusHolder*)controller->actor->GetAuthoredProperty(&gHeightKey2);
    heightFlag = (HeightFlag*)controller->actor->GetAuthoredProperty(&gHeightFlagKey);
    yawChannel = func_002DFE08(world,&gBankA);
    turnChannel = func_002DFE08(world,&gBankB);
    speedChannel = func_002DFE08(world,&gBankC);
    speedChannelAlt = func_002DFE08(world,&gBankD);
    verticalChannel = func_002DFE08(world,&gBankE);
    if (yawChannel) {
        yawChannel->value = 0;
        yawChannel->dirty = true;
    }
    if (turnChannel) {
        turnChannel->value = 0;
        turnChannel->dirty = true;
    }
    if (speedChannel) {
        speedChannel->value = 0;
        speedChannel->dirty = true;
    }
    if (speedChannelAlt) {
        speedChannelAlt->value = 0;
        speedChannelAlt->dirty = true;
    }
    if (verticalChannel) {
        verticalChannel->value = 0;
        verticalChannel->dirty = true;
    }
    ParameterTables* tables = GetNameTables();
    slotIndex = tables->FindNameA("CPathFinder::FindNextMove::CheckAccident");
    searchSlotIndex = tables->FindNameB("CPathFinder::FindNextMove::ASTAR");
    goalSlotIndex = tables->FindNameA("CPathFinder::FindNextMove::NewSubGoal");
    turnSlotIndex = tables->FindNameA("CPathFinder::FindNextMove::Goto");
    if (Bind1() && Bind2() && Bind3() && Bind4() && Bind5()) {
        if (!route.capacity)
            ((RouteBlock*)((char*)this + 0x6c))->SetMaxPathSize(0x32);
        ListenerRegistry* listeners = gClassRegistry->FindListeners(&gListenerClass2);
        if (listeners)
            listeners->Add(CPathFinder_OnActorEvent, this, controller->actor);
        return 1;
    }
    return 0;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char __cdecl CPathFinder_PublishControls(CPathFinder* follower, MoveRecord* move)
{
    CPathFinder* self = follower;
    if (follower->hold) {
        ControlChannel* channel = follower->speedChannel;
        if (!channel)
            channel = follower->speedChannelAlt;
        if (channel) {
            channel->value = channel->value;
            channel->dirty = true;
        }
        channel = follower->yawChannel;
        if (!channel)
            channel = follower->turnChannel;
        if (channel) {
            channel->value = channel->value;
            channel->dirty = true;
        }
        channel = follower->verticalChannel;
        if (channel) {
            channel->value = channel->value;
            channel->dirty = true;
        }
    }
    if (move->direction[0] != gOriginX || move->direction[1] != gOriginY || move->direction[2] != gOriginZ) {
        float maxTurn = gUpdateStep * follower->maxYawSpeed;
        ControlChannel* turn = follower->turnChannel;
        if (!turn) {
            ControlChannel* yaw = follower->yawChannel;
            if (!yaw)
                return 0;
            Vector3Value flat;
            flat.x = move->direction[0];
            flat.z = move->direction[2];
            flat.y = 0.0f;
            Vector3Value unit = Vector3_Normalize(flat);
            Actor* actor = follower->controller->actor;
            float* facing = (float*)actor;
            float cosine = unit.x * facing[0x12] + unit.y * facing[0x13] + unit.z * facing[0x14];
            float angle;
            if (cosine < 1.0f) {
                if (cosine <= -1.0f)
                    angle = 3.1415927f;
                else
                    angle = AcosRadians(cosine);
            } else {
                angle = 0.0;
            }
            angle = angle / kRadiansPerDegree;
            const float* currentFacing = (const float*)follower->controller->actor;
            if (unit.x * currentFacing[0x14] - unit.z * currentFacing[0x12] <= 0.0f)
                angle = -angle;
            float delta = (float)angle;
            if (follower->yawSmoothing) {
                if (-maxTurn <= delta && maxTurn < delta)
                    delta = maxTurn;
                else if (!(-maxTurn <= delta))
                    delta = -maxTurn;
            }
            float target = Degrees_WrapSigned(delta + facing[0x10]);
            if (!move->flagA || !follower->updateTorsoRotate) {
                if (delta < 0 ? -delta < follower->maxDeltaAngle : delta < follower->maxDeltaAngle) {
                    yaw->value = target;
                    yaw->dirty = true;
                } else {
                    AuthoredValue* property = actor->GetAuthoredProperty(&gTurnKey);
                    if (!property)
                        move->speed = (follower->maxDeltaAngle / (delta < 0 ? -delta : delta)) * move->speed;
                    else
                        move->speed = follower->speeds->speed * 0.1f;
                    float heading = ((const float*)follower->controller->actor)[0x10];
                    if (delta <= 0.0f)
                        heading = heading - follower->maxDeltaAngle;
                    else
                        heading = heading + follower->maxDeltaAngle;
                    follower->yawChannel->value = heading;
                    follower->yawChannel->dirty = true;
                }
            } else {
                ControlChannel* torso = func_002DFE08(follower->world,&gTorsoBank);
                if (torso) {
                    torso->second = Degrees_WrapSigned(move->extra[1]);
                    torso->dirty = true;
                }
                follower->yawChannel->value = target;
                follower->yawChannel->dirty = true;
            }
        } else {
            Vector3Value orientation;
            Direction_Orientation(&orientation, (const Vector3Value*)&move->direction[0]);
            float diff = orientation.y - ((float*)follower->controller->actor)[0x10];
            if (diff > 180.0f)
                diff = diff - 360.0f;
            else if (diff < -180.0f)
                diff = diff + 360.0f;
            float limited = diff;
            if (follower->yawSmoothing) {
                if (-maxTurn <= diff && maxTurn < diff)
                    limited = maxTurn;
                else if (!(-maxTurn <= diff))
                    limited = -maxTurn;
            }
            if (follower->maxDeltaAngle <= (limited < 0 ? -limited : limited)) {
                turn->dirty = true;
                turn->value = limited <= 0.0f ? -1.0f : 1.0f;
            } else {
                turn->dirty = true;
                turn->value = limited / follower->maxDeltaAngle;
            }
        }
    }
    ControlChannel* speed = follower->speedChannel;
    if (!speed) {
        speed = follower->speedChannelAlt;
        if (!speed)
            return 0;
        speed->value = move->speed;
        speed->dirty = true;
    } else {
        float current = *(float*)((char*)follower->controller->actor + 0x54);
        if (move->speed <= current) {
            speed->dirty = true;
            speed->value = move->speed < current ? -1.0f : 0.0f;
        } else {
            speed->value = 1.0f;
            speed->dirty = true;
        }
    }
    if (follower->heightFlag && follower->heightFlag->enabled) {
        ControlChannel* vertical = follower->verticalChannel;
        if (!vertical)
            return 0;
        float climb = move->direction[1];
        vertical->dirty = true;
        if (climb >= 0.0f) {
            vertical->value = climb * 2.5f;
            return 1;
        }
        vertical->value = climb + climb;
    }
    return 1;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
bool CPathFinder::FindNextMove(MoveRecord* move, RouteRequest* request)
{
    MoveRecord* output = move;
    float savedY, savedZ, savedX;
    bool flag;
    bool searched;
    if (!hold) {
        lastPoint.z = position.z - target.z;
        lastPoint.x = position.x - target.x;
        lastPoint.y = position.y - target.y;
        unknownB4 = true;
    } else {
        lastPoint.z = position.z - savedTarget.z;
        lastPoint.x = position.x - savedTarget.x;
        lastPoint.y = position.y - savedTarget.y;
        unknownB4 = false;
    }
    move->speed = 0;
    Actor* actor = controller->actor;
    move->direction[0] = *(float*)((char*)actor + 0x48);
    move->direction[1] = *(float*)((char*)actor + 0x4c);
    move->direction[2] = *(float*)((char*)actor + 0x50);
    move->flagA = false;
    float oldX = previous.x;
    float oldY = previous.y;
    float oldZ = previous.z;
    float* point = &previous.x;
    if (policy)
        policy->Update();
    int waypointIndex = waypoint;
    WaypointGuard* guard = 0;
    if (waypointIndex == 0 || waypointIndex == -1 || (guard = route.guards[waypointIndex - 1]) == 0
        || !guard->IsBlocked(controller->actor)) {
        if (stopCondition(this)) {
            output->speed = cachedMove.speed;
            output->direction[0] = cachedMove.direction[0];
            output->direction[1] = cachedMove.direction[1];
            output->direction[2] = cachedMove.direction[2];
            output->extra[0] = cachedMove.extra[0];
            output->extra[1] = cachedMove.extra[1];
            output->extra[2] = cachedMove.extra[2];
            output->flagA = cachedMove.flagA;
            output->flagB = cachedMove.flagB;
            output->speed = 0;
            activated = true;
            hold = false;
            return true;
        }
    }
    GetNameTables();
    flag = false;
    if (!restartSearch) {
        if (!searchPaused) {
            float limit = arrivalRadius;
            float distance = Vec3_DistanceSquared(&lastPoint, &target);
            if (limit * limit < distance) {
                if (guard) {
                    if (!guard->IsBlocked(controller->actor))
                        goto notBlocked;
                }
                goto setFlag;
            }
        notBlocked:
            if (*((unsigned char*)this + 0x8c) == 1 && route.count <= (unsigned int)waypoint + 2) {
                flag = true;
                restartSearch = true;
                goto consume;
            }
            if (!guard)
                flag = Slot23();
            else
                flag = flag198 = guard->CanContinue(controller->actor);
            goto checkFlag;
        }
    setFlag:
        flag = true;
    consume:
        {
            bool consumed = GetNameTables()->Consume(searchSlotIndex, controller->actor);
            hold = !consumed;
            if (hold) {
                target.x = savedTarget.x;
                target.y = savedTarget.y;
                target.z = savedTarget.z;
                startNode = savedStart;
                goalNode = savedGoal;
                if (searchPaused)
                    GetNameTables()->SelectUser(controller->actor);
            }
        }
    } else {
        if (!guard)
            flag = true;
        else if (guard->IsBlocked(controller->actor) == true)
            flag = true;
        cachedMove.speed = 0;
    checkFlag:
        if (flag)
            goto consume;
    }
    searched = false;
    if (!hold && flag) {
        activated = false;
        lastPoint.x = target.x;
        lastPoint.y = target.y;
        lastPoint.z = target.z;
        searched = true;
        bool changed = flag;
        searchOk = RefreshSearch(flag198, &changed, request);
        restartSearch = false;
        GetNameTables()->Accumulate(searchSlotIndex, controller->actor);
        waypointPosition = position;
        savedTarget = target;
        savedStart = startNode;
        savedGoal = goalNode;
        flag = changed;
        if (!searchPaused) {
            if (searchOk && (flag || flag198)) {
                if (!flag198) {
                    unsigned int exact = AIRoute_FindExactPoint((RouteBlock*)((char*)this + 0x6c), point);
                    if (exact != 0xffffffff) {
                        waypoint = exact;
                        goto afterSearch;
                    }
                }
                if (route.count == 0) {
                    waypoint = -1;
                    point[0] = target.x;
                    point[1] = target.y;
                    point[2] = target.z;
                } else {
                    waypoint = 0;
                    point[0] = route.points[0].x;
                    point[1] = route.points[0].y;
                    point[2] = route.points[0].z;
                }
            }
        }
    }
afterSearch:
    if (searchPaused) {
        searchOk = false;
        return true;
    }
    if (!searchOk)
        return false;
    if (searched)
        goto advance;
    if (GetNameTables()->Raise(goalSlotIndex, controller->actor))
        goto advance;
    if (guard)
        goto guarded;
    if (GetNameTables()->Raise(turnSlotIndex, controller->actor))
        goto turn;
    activated = false;
    *output = cachedMove;
    goto finish;
advance:
    if (!guard) {
        if (turnState == 0) {
            nextSubgoal(this);
        } else {
            int before = waypoint;
            if (turnState == 2)
                nextSubgoal(this);
            else
                CPathFinder_AdvanceSubgoal(this);
            if (before != waypoint)
                --turnState;
        }
        GetNameTables()->Store(goalSlotIndex, controller->actor);
    turn:
        GetNameTables()->Store(turnSlotIndex, controller->actor);
        if (!moveModeCheck(this, point))
            complexMove(this, &output->speed, point);
        else
            simpleMove(this, &output->speed, point);
        PredictMove(&output->speed);
        cachedMove = *output;
        goto finish;
    }
guarded:
    {
        float probe[3];
        probe[2] = previous.z;
        probe[0] = point[0];
        probe[1] = previous.y;
        bool done = false;
        if (guard->Evaluate(controller->actor, &route.points[0].x + waypoint * 3, world, &done, probe)) {
            movable = false;
        } else {
            simpleMove(this, &output->speed, probe);
        }
        if (done) {
            unsigned int next = waypoint + 1;
            if (next < route.count) {
                waypoint = next;
                point[0] = route.points[next].x;
                point[1] = route.points[next].y;
                point[2] = route.points[next].z;
            } else {
                point[0] = target.x;
                point[1] = target.y;
                point[2] = target.z;
            }
            for (unsigned int i = waypoint; i < route.count; ++i) {
                int base = waypoint;
                route.points[i - base] = route.points[i];
            }
            route.count -= waypoint;
            waypoint = 0;
        }
        GetNameTables()->Store(turnSlotIndex, controller->actor);
    }
finish:
    if (oldX == point[0] && oldY == previous.y) {
        if (oldZ == previous.z)
            return true;
    }
    CPathFinder_BeginSegment(this);
    return true;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
bool CPathFinder::RefreshSearch(bool invalidateStart, bool* changed, RouteRequest* request)
{
    void* start = collectNode(this, &position.x, 1, 0);
    void* goal = 0;
    if (request)
        goal = ResolveRequestNode(request);
    if (!goal)
        goal = collectNode(this, &target.x, 0, 1);
    if (!searchPaused && (!invalidateStart || start == startNode) && goal == goalNode && !restartSearch) {
        *changed = false;
        return searchOk;
    }
    *changed = true;
    startNode = start;
    goalNode = goal;
    if (!start || !goal)
        return false;
    RouteBlock* route = (RouteBlock*)((char*)this + 0x6c);
    route->count = 0;
    route->length = 0;
    if (routeTable) {
        if (source->GetType() == &gRouteTableType)
            return routeTable->Build(*(unsigned int*)startNode, *(unsigned int*)goalNode, route);
    }
    graph->costPolicy = GetCostPolicy();
    graph->heuristic = GetHeuristic();
    if (!avoidCpuPeaks)
        return graph->FindRoute(route, startNode, goalNode, controller->actor);
    SearchRecord* record = &records[*(int*)((char*)source->GetType() + 4)];
    float remaining = GetNameTables()->Remaining(searchSlotIndex);
    if (remaining < 0.0005f)
        remaining = 0.0005f;
    searchPaused = false;
    unsigned int status = graph->AdvanceTimed(route, startNode, goalNode, controller->actor, &record->samples,
                                              &record->mean, &record->deviation, record->scale, remaining,
                                              restartSearch);
    if (status == 0)
        return false;
    if (status == 1)
        return true;
    if (status == 2) {
        searchPaused = true;
        GetNameTables()->SelectUser(controller->actor);
        return true;
    }
    return false;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
float CPathFinder::RemainingDistance()
{
    if (IsComplete() == true)
        return Distance(&controller->actor->position, &target);
    float total = Distance(&controller->actor->position, &previous);
    if (previous.x != target.x || previous.y != target.y || previous.z != target.z) {
        if (waypoint != -1) {
            unsigned int next = waypoint + 1;
            if (next < route.count) {
                const Vec3f* from = &route.points[waypoint];
                const float* to = &(from + 1)->y;
                do {
                    float dz=to[1] - to[-2];
                    float dx=to[-1] - from->x;
                    ++from;
                    float dy=to[0] - to[-3];
                    to += 3;
                    ++next;
                    total += sqrtf(dz * dz + dx * dx + dy * dy);
                } while (next < route.count);
            }
        }
        total += Distance(&route.points[route.count - 1], &target);
    }
    return total;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
bool CPathFinder::SetGraph(NavigationGraph*newGraph)
{
 if(!newGraph){graph=0;routeTable=0;graphId=-1;looseGraph=0;}
 else{
  GraphRegistry*registry=gEngineHandle->FindByClass(&gGraphRegistryClass);if(!registry)return false;
  graph=newGraph;
  if(converter){const char*name=0;for(unsigned int i=0;i<registry->count;++i){if(registry->items[i]->graph==graph){name=registry->items[i]->name;break;}}if(name){if(!converter->NameToId(name,&graphId))graphId=-1;}else graphId=-1;}
  else graphId=-1;
  routeTable=(RouteTable*)registry->Find((int)newGraph,&gRouteTableClass);looseGraph=(NavigationGraph*)registry->Find((int)newGraph,&gLooseGraphClass);
 }
 for(unsigned int i=0;i<agentCount;++i)if(agentList[i])agentList[i]->SetGraph(graph);
 for(unsigned int i=0;i<serviceCount;++i)if(serviceList[i])serviceList[i]->SetGraph(graph);
 return true;
}
#endif
bool CPathFinder::SetGraphByName(const char* name)
{
    GraphRegistry* registry = gEngineHandle->FindByClass(&gGraphRegistryClass);
    if (!registry)
        return false;
    int id = registry->IdByName(name);
    if (id == 0)
        return false;
    graph = (NavigationGraph*)id;
    if (converter) {
        if (!converter->NameToId(name, &graphId))
            graphId = -1;
    } else {
        graphId = -1;
    }
    routeTable = (RouteTable*)registry->Find(id, &gRouteTableClass);
    looseGraph = (NavigationGraph*)registry->Find(id, &gLooseGraphClass);
    for (unsigned int i = 0; i < agentCount; ++i) {
        if (agentList[i])
            agentList[i]->SetGraph(graph);
    }
    for (unsigned int i = 0; i < serviceCount; ++i) {
        if (serviceList[i])
            serviceList[i]->SetGraph(graph);
    }
    return true;
}
void CPathFinder::UpdateProgress()
{
    if (!flag198) {
        if (GetNameTables()->Raise(slotIndex, controller->actor)) {
            float length = position.DistanceFrom(previous);
            if (segmentLength < 0.0f || segmentLength * 0.95f < length) {
                flag198 = true;
                GetNameTables()->Restart(slotIndex, controller->actor);
            }
            segmentLength = length;
        }
    }
}
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char __cdecl CPathFinder_HasUnsupportedGround(CPathFinder* follower, const float* point)
{
    float dx = point[0] - follower->position.x;
    float dy = point[1] - follower->position.y;
    float dz = point[2] - follower->position.z;
    float sideX = dy * gSideAxisZ - dz * gSideAxisY;
    float sideY = dz * gSideAxisX - dx * gSideAxisZ;
    float sideZ = dx * gSideAxisY - dy * gSideAxisX;
    float sideLength = sqrtf(sideX * sideX + sideY * sideY + sideZ * sideZ);
    if (sideLength == 0.0f)
        return 0;
    float scale = (follower->radiusHolder->radius / sideLength) * follower->widthRatio;
    sideX = sideX * scale;
    sideY = sideY * scale;
    sideZ = sideZ * scale;
    AuthoredValue* property = follower->controller->actor->GetAuthoredProperty(&gGroundKey);
    float drop;
    if (!property)
        drop = gWorldScale ? gWorldScale->unit : 0.0f;
    else
        drop = property->value * 0.5f;
    float hole = follower->holeHeight;
    for (int side = 0; side < 2; ++side) {
        float a[3];
        float b[3];
        if (side == 0) {
            a[0] = sideX + follower->position.x;
            a[1] = sideY + follower->position.y;
            a[2] = sideZ + follower->position.z;
            b[0] = sideX + point[0];
            b[1] = sideY + point[1];
            b[2] = sideZ + point[2];
        } else {
            a[0] = follower->position.x - sideX;
            a[1] = follower->position.y - sideY;
            a[2] = follower->position.z - sideZ;
            b[0] = point[0] - sideX;
            b[1] = point[1] - sideY;
            b[2] = point[2] - sideZ;
        }
        float ex = b[0] - a[0];
        float ey = b[1] - a[1];
        float ez = b[2] - a[2];
        float length = sqrtf(ex * ex + ey * ey + ez * ez);
        if (length == 0.0f)
            return 0;
        float travelled = 0.0f;
        float inverse = 1.0f / length;
        unsigned int probes = 0;
        float stepX = ex * inverse;
        do {
            if (length < travelled)
                return 0;
            float y = inverse * ey * travelled;
            float z = inverse * ez * travelled;
            float from[3];
            from[0] = stepX * travelled + a[0];
            from[1] = y + a[1];
            from[2] = z + a[2];
            float to[3];
            to[0] = from[0];
            to[1] = from[1] - (hole + drop);
            to[2] = from[2];
            if (gGroundProbeHook(from, to, follower->controller->actor, 2))
                return 1;
            ++probes;
            travelled = (gWorldScale ? gWorldScale->unit : 0.0f) + travelled;
        } while (probes < 2);
        if (length < travelled)
            return 0;
        travelled = (length - travelled) * 0.5f + travelled;
        float from[3];
        from[0] = stepX * travelled + a[0];
        from[1] = inverse * ey * travelled + a[1];
        from[2] = inverse * ez * travelled + a[2];
        float to[3];
        to[0] = from[0];
        to[1] = from[1] - (hole * 1.2f + drop);
        to[2] = from[2];
        if (gGroundProbeHook(from, to, follower->controller->actor, 2))
            break;
        if (side + 1 > 1)
            return 0;
    }
    return 1;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned int __cdecl CPathFinder_GenerateMove(CPathFinder* owner, float* move, const float* point)
{
    Vec3f delta;
    delta.x = point[0] - owner->position.x;
    delta.y = point[1] - owner->position.y;
    delta.z = point[2] - owner->position.z;
    move[3] = delta.z;
    move[1] = delta.x;
    move[2] = delta.y;
    float length = sqrtf(move[3] * move[3] + move[2] * move[2] + move[1] * move[1]);
    float planar = sqrtf(move[3] * move[3] + move[1] * move[1]);
    float inverse = 1.0f / length;
    move[3] = inverse * move[3];
    move[1] = inverse * move[1];
    move[2] = inverse * move[2];
    if (!owner->heightFlag || !owner->heightFlag->enabled)
        move[2] = 0;
    float limit;
    if (point[0] == owner->target.x && point[1] == owner->target.y && point[2] == owner->target.z)
        limit = owner->finalRadius;
    else
        limit = owner->arrivalRadius;
    if (length <= limit)
        move[0] = owner->speeds->speed * 0.5f;
    else
        move[0] = owner->speeds->speed;
    if (!owner->heightFlag || owner->heightFlag->enabled != 1)
        return 1;
    float stop;
    if (Kaim_Vec3Equal(point, &owner->target.x))
        stop = owner->heightRadiusA;
    else
        stop = owner->heightRadiusB;
    if (planar < stop)
        move[0] = 0;
    return 1;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char __cdecl CPathFinder_AdvanceSubgoal(CPathFinder* owner)
{
    float* point = &owner->previous.x;
    if (point[0] == owner->target.x && point[1] == owner->target.y) {
        if (point[2] == owner->target.z)
            return 1;
    }
    unsigned int waypoint = owner->waypoint;
    if (waypoint > 0 && waypoint != 0xffffffff) {
        WaypointGuard* guard = owner->route.guards[waypoint - 1];
        Actor* actor = owner->controller->actor;
        if (guard) {
            if (!guard->Check(actor, &actor->position.x, point))
                return 1;
        }
    }
    unsigned int nearest = ((RouteBlock*)((char*)owner + 0x6c))->FindNearestPoint(point);
    owner->waypoint = nearest;
    if (nearest == 0xffffffff)
        return 0;
    float dz = point[2] - owner->position.z;
    float dx = point[0] - owner->position.x;
    float dy = point[1] - owner->position.y;
    float length = sqrtf(dz * dz + dx * dx + dy * dy);
    if (length < owner->heightRadiusB) {
        unsigned int next = nearest + 1;
        if (next < owner->route.count) {
            owner->waypoint = next;
            const Vec3f* waypointPoint = &owner->route.points[next];
            *point = waypointPoint->x;
            point[1] = waypointPoint->y;
            point[2] = waypointPoint->z;
        } else {
            *point = owner->target.x;
            point[1] = owner->target.y;
            point[2] = owner->target.z;
        }
        GetNameTables()->Store(owner->goalSlotIndex, owner->controller->actor);
    }
    return 1;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned int __cdecl CPathFinder_AdvanceSubgoalSmooth(CPathFinder* owner)
{
    if (owner->hold)
        return CPathFinder_AdvanceSubgoal(owner);
    if (owner->previous.x == owner->target.x && owner->previous.y == owner->target.y &&
        owner->previous.z == owner->target.z)
        return 1;
    if (!owner->goalNode)
        return 1;
    if (!owner->startNode)
        return 1;
    unsigned int nearest = ((RouteBlock*)((char*)owner + 0x6c))->FindNearestPoint(&owner->previous.x);
    owner->waypoint = nearest;
    if (nearest == 0xffffffff)
        return 1;
    owner->previous.x = owner->route.points[nearest].x;
    owner->previous.y = owner->route.points[nearest].y;
    owner->previous.z = owner->route.points[nearest].z;
    ParameterTables* tables = GetNameTables();
    SegmentGraph* graph = (SegmentGraph*)owner->graph;
    void* probeEdge = &graph->syntheticIndex;
    unsigned int index = owner->waypoint;
    unsigned int steps = 0;
    if (index != owner->route.count - 1) {
        unsigned int offset = index * 12;
        for (;;) {
            if (index > 0) {
                WaypointGuard* guard = owner->route.guards[index - 1];
                Actor* actor = owner->controller->actor;
                if (guard && !guard->Check(actor, &actor->position.x, &owner->route.points[0].x + offset / 4))
                    return 1;
            }
            const Vec3f* next = (const Vec3f*)((char*)owner->route.points + offset + 12);
            unsigned int nextIndex = index + 1;
            float dz = owner->position.z - next->z;
            float dx = owner->position.x - next->x;
            float dy = owner->position.y - next->y;
            if (owner->distSubgoalMax * owner->distSubgoalMax < dz * dz + dx * dx + dy * dy)
                break;
            float vertical = next->y - owner->position.y;
            if (vertical < 0)
                vertical = -vertical;
            if (owner->radius < vertical || !owner->moveModeCheck(owner, &next->x))
                break;
            SegmentPolicy* policy = (SegmentPolicy*)owner->GetCostPolicy();
            float costThrough, costFrom, costDirect;
            Actor* actor = owner->controller->actor;
            SetProbeSegment(graph, &owner->route.points[0].x + offset / 4, &next->x);
            policy->Cost(actor, probeEdge, &costThrough);
            SetProbeSegment(graph, &owner->controller->actor->position.x, &owner->route.points[0].x + offset / 4);
            policy->Cost(owner->controller->actor, probeEdge, &costFrom);
            SetProbeSegment(graph, &owner->controller->actor->position.x, &next->x);
            if (!policy->Cost(owner->controller->actor, probeEdge, &costDirect))
                break;
            if (costThrough + costFrom < costDirect)
                break;
            ++steps;
            index = nextIndex;
            offset += 12;
            if (steps >= (unsigned int)owner->unknown4cLimit || index == owner->route.count - 1)
                break;
        }
    }
    bool reachedTarget = false;
    if (steps < (unsigned int)owner->unknown4cLimit && index + 1 == owner->route.count) {
        float limit = owner->distSubgoalMax;
        float distance = Vec3_DistanceSquared(&owner->target, &owner->position);
        if (distance <= limit * limit) {
            float vertical = owner->target.y - owner->position.y;
            if (vertical < 0)
                vertical = -vertical;
            if (vertical <= owner->radius) {
                if (owner->moveModeCheck(owner, &owner->target.x) == 1) {
                    SegmentPolicy* policy = (SegmentPolicy*)owner->GetCostPolicy();
                    float costA, costB, costC;
                    SetProbeSegment(graph, &owner->route.points[index].x, &owner->target.x);
                    ((FloatSlot*)probeEdge)->SetLength(Vec3_Length(&graph->endPosition, &graph->startPosition));
                    policy->Cost(owner->controller->actor, probeEdge, &costA);
                    SetProbeSegment(graph, &owner->controller->actor->position.x, &owner->route.points[index].x);
                    ((FloatSlot*)probeEdge)->SetLength(Vec3_Length(&graph->endPosition, &graph->startPosition));
                    policy->Cost(owner->controller->actor, probeEdge, &costB);
                    SetProbeSegment(graph, &owner->controller->actor->position.x, &owner->target.x);
                    ((FloatSlot*)probeEdge)->SetLength(Vec3_Length(&graph->endPosition, &graph->startPosition));
                    if (policy->Cost(owner->controller->actor, probeEdge, &costC) == 1 && costB + costA > costC) {
                        owner->previous.x = owner->target.x;
                        owner->previous.y = owner->target.y;
                        owner->previous.z = owner->target.z;
                        reachedTarget = true;
                    }
                } else {
                    float reach = owner->heightRadiusB;
                    if (Vec3_DistanceSquared(&owner->route.points[index], &owner->position) <= reach * reach) {
                        owner->previous.x = owner->target.x;
                        owner->previous.y = owner->target.y;
                        owner->previous.z = owner->target.z;
                        reachedTarget = true;
                    }
                }
            }
        }
    }
    unsigned int current = owner->waypoint;
    if (index == current && index + 1 < owner->route.count) {
        float reach = owner->heightRadiusB;
        if (Vec3_DistanceSquared(&owner->position, &owner->route.points[current]) < reach * reach)
            index = index + 1;
    }
    if (index != current) {
        owner->waypoint = index;
        if (!reachedTarget) {
            owner->previous.x = owner->route.points[index].x;
            owner->previous.y = owner->route.points[index].y;
            owner->previous.z = owner->route.points[index].z;
        }
        tables->Store(owner->goalSlotIndex, owner->controller->actor);
    }
    return 1;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
bool CPathFinder::Configure(ChildBuffers* property)
{
    if (!property)
        return false;
    if (!_stricmp(property->GetSecond(), "Graph"))
        return SetGraphByName(property->GetValue());
    if (!_stricmp(property->GetSecond(), "DistMinNewGoal")) {
        const char* value = property->GetValue();
        if (value) {
            distMinNewGoal = ParseFloat(value) * gWorldScale->unit;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "DistGoal")) {
        const char* value = property->GetValue();
        if (value) {
            heightRadiusA = ParseFloat(value) * gWorldScale->unit;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "DistStop")) {
        const char* value = property->GetValue();
        if (value) {
            heightRadiusB = ParseFloat(value) * gWorldScale->unit;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "DistGoalSlowDown")) {
        const char* value = property->GetValue();
        if (value) {
            finalRadius = ParseFloat(value) * gWorldScale->unit;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "DistSlowDown")) {
        const char* value = property->GetValue();
        if (value) {
            arrivalRadius = ParseFloat(value) * gWorldScale->unit;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "MaxDeltaHeight")) {
        const char* value = property->GetValue();
        if (value) {
            radius = ParseFloat(value) * gWorldScale->unit;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "DistSubgoalMax")) {
        const char* value = property->GetValue();
        if (value) {
            distSubgoalMax = ParseFloat(value) * gWorldScale->unit;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "MaxDeltaAngle")) {
        const char* value = property->GetValue();
        if (value) {
            maxDeltaAngle = Degrees_WrapUnsigned(ParseFloat(value));
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "MaxYawSpeed")) {
        const char* value = property->GetValue();
        if (value) {
            maxYawSpeed = ParseFloat(value);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "NbMaxSubgoal")) {
        const char* value = property->GetValue();
        if (value) {
            unknown4cLimit = atoi(value);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "HoleHeight")) {
        const char* value = property->GetValue();
        if (value) {
            holeHeight = ParseFloat(value) * gWorldScale->unit;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "WidthRatioForHoleDetection")) {
        const char* value = property->GetValue();
        if (value) {
            widthRatio = ParseFloat(value);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "HoleDistToEdge")) {
        const char* value = property->GetValue();
        if (value) {
            float edge = ParseFloat(value);
            corridorWidth = Kaim_WorldUnit() * edge;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "CpuPrudence")) {
        const char* value = property->GetValue();
        if (value) {
            cpuPrudence = ParseFloat(value);
            unsigned int i = 0;
            if (serviceCount != 0) {
                int offset = 0;
                do {
                    *(float*)((char*)records + offset + 0x10) = cpuPrudence;
                    ++i;
                    offset += 0x14;
                } while (i < serviceCount);
            }
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "AvoidCpuPeaks")) {
        const char* value = property->GetValue();
        if (value) {
            long flag = atoi(value);
            if ((float)flag == 0.0f) {
                avoidCpuPeaks = false;
                return true;
            }
            avoidCpuPeaks = true;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "StopCondition")) {
        void* policy = func_00393A18(property->GetValue());
        if (policy) {
            stopCondition = (StopFn)policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "FindVertex")) {
        void* policy = func_00393AC0(property->GetValue());
        if (policy) {
            collectNode = (CollectNodeFn)policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "MoveModeCheck")) {
        void* policy = func_00393B68(property->GetValue());
        if (policy) {
            moveModeCheck = (GuardFn)policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "SimpleMove")) {
        void* policy = func_00393C10(property->GetValue());
        if (policy) {
            simpleMove = (MoveFn)policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "ComplexMove")) {
        void* policy = func_00393C10(property->GetValue());
        if (policy) {
            complexMove = (MoveFn)policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "NextSubgoal")) {
        void* policy = func_00393A18(property->GetValue());
        if (policy) {
            nextSubgoal = (SubgoalFn)policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "CanGo")) {
        void* policy = func_00393B68(property->GetValue());
        if (policy) {
            canGo = (GuardFn)policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "MaxPathSize")) {
        long size = atoi(property->GetValue());
        ((RouteBlock*)((char*)this+0x6c))->SetMaxPathSize(size);
        return true;
    }
    if (_stricmp(property->GetSecond(), "YawSmoothing")) {
        if (!_stricmp(property->GetSecond(), "UpdateTorsoRotate")) {
            const char* value = property->GetValue();
            if (_stricmp(value, "yes") && _stricmp(value, "true") && _stricmp(value, "1")) {
                if (_stricmp(value, "no") && _stricmp(value, "false") && _stricmp(value, "0"))
                    return false;
                updateTorsoRotate = false;
                return true;
            }
            updateTorsoRotate = true;
        } else if (_stricmp(property->GetSecond(), "DynamicAvoidanceClass")) {
            if (this->policy && this->policy->Configure(property) == true)
                return true;
            return Kaim_IsHiddenName(property);
        }
        return true;
    }
    long mode = atoi(property->GetValue());
    unsigned short narrowed = (unsigned short)mode;
    if (narrowed < 3) {
        yawSmoothing = narrowed != 0;
        return true;
    }
    return false;
}
#endif

struct PathRegistry {void *items[256];int count;};
extern "C" PathRegistry *func_00390168();
extern "C" void *func_002EC058(void*,const void*);
extern "C" void func_003053F0(float,void*);
extern "C" void func_002F5A40(void*,void*,void*,void*);
extern const Vec3f pathOrigin __asm__("D_004514F8");
extern char pathManagerClass __asm__("D_004525B8");
CPathFinder::CPathFinder(void *brain):IPathFinder(brain)
{
 activated=true;waypoint=(unsigned int)-1;restartSearch=false;searchPaused=false;
 routeTable=0;looseGraph=0;hold=false;searchOk=false;goalNode=0;startNode=0;
 pendingTarget=pathOrigin;target=pathOrigin;previous=pathOrigin;turnState=0;savedTarget=pathOrigin;savedStart=0;savedGoal=0;
 if(serviceCount)records=new SearchRecord[serviceCount];else records=0;
 unknown1c=0;agentCount=func_00390168()->count;
 if(!agentCount)agentList=0;else{agentList=(AgentObject**)Allocate(agentCount*4);for(unsigned int i=0;i<agentCount;++i)agentList[i]=0;}
 lastProbe=pathOrigin;segmentLength=-1.0f;policy=0;
}
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
CPathFinder::~CPathFinder()
{
 void *listeners=func_002EC058(gWorldScale,&pathManagerClass);
 if(listeners)func_002F5A40(listeners,(void*)func_003053F0,this,controller->actor);
 delete[] records;
 if(agentList){for(unsigned int i=0;i<agentCount;++i){if(agentList[i])delete agentList[i];}D_003C87E0(agentList);}
 delete policy;
}
#endif


extern "C" NavigationGraph::NodeRecord *func_0038F2B0(const EdgeRef*);
extern "C" NavigationGraph::NodeRecord *func_0038F2F0(const EdgeRef*);
inline float EdgeRef::GetAuthoredLength()const
{
 SegmentGraph*owner=(SegmentGraph*)graph;
 if(this==(EdgeRef*)&owner->syntheticIndex)return owner->syntheticLength;
 if(!owner->edgeLengths){const float*a=(const float*)((char*)func_0038F2B0(this)+4);const float*b=(const float*)((char*)func_0038F2F0(this)+4);float dx=b[0]-a[0],dz=b[2]-a[2],dy=b[1]-a[1];return sqrtf(dz*dz+dx*dx+dy*dy);}return owner->edgeLengths[index];
}
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char CPathFinder_CheckSegmentCorridor(CPathFinder *self,const float*point)
{
 if(Kaim_Vec3Equal(&self->previous.x,&self->target.x))return true;
 unsigned int at=self->waypoint;if(!at || at==(unsigned)-1)return true;
 const Vec3f&end=self->route.points[at];const Vec3f&start=self->route.points[at-1];Vec3f delta=end-start;
 unsigned int id=self->route.edgeIds[at-1];EdgeRef*edge=0;if(id<self->graph->edgeCapacity){EdgeRef*p=&self->graph->edges[id];if(p->index!=-1)edge=p;}
 float length=edge?edge->GetAuthoredLength():sqrtf(delta.Squared());
 if(length!=0.0f){Vec3f offset=self->position-self->route.points[self->waypoint-1];float along=delta.Dot(offset)/length;
  if(-self->heightRadiusB<=along && along<=length){float side=(delta.z*offset.x-delta.x*offset.z)/length;if(side<0.0f)side=-side;if(side<self->corridorWidth)return true;}}
 unsigned char unsupported=CPathFinder_HasUnsupportedGround(self,point);if(unsupported)self->turnState=2;return unsupported==0;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char CPathFinder_SelectSteeringProbe(CPathFinder*self,const float*from,const float*to,float*out)
{
 TraceResult leftTrace,rightTrace;
 Vec3f delta=*(const Vec3f*)to-*(const Vec3f*)from;
 Vec3f direction=delta/sqrtf(delta.Squared());
 Vec3f origin=*(const Vec3f*)from;
 float length=gWorldScale->unit*5.0f;
 Vec3f side=direction.Cross(Vec3f(0.0f,1.0f,0.0f))*(length/3.0f);
 Vec3f center=origin+direction*length;
 Vec3f left=center+side;Vec3f right=center-side;
 gTraceHook(&origin.x,&left.x,self->controller->actor,&leftTrace,2);
 if(leftTrace.fraction==1.0f)right=left-origin;
 else{gTraceHook(&origin.x,&right.x,self->controller->actor,&rightTrace,2);if(rightTrace.fraction==1.0f || leftTrace.fraction<=rightTrace.fraction)right=right-origin;else right=left-origin;}
 *(Vec3f*)out=right;return 1;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char CPathFinder_GenerateSteeringMove(CPathFinder*self,float*out,const float*point)
{
 Vec3f direction;
 if(!CPathFinder_SelectSteeringProbe(self,&self->position.x,point,&direction.x)){out[1]=direction.x;out[3]=0;out[2]=0;out[2]=direction.y;out[3]=direction.z;out[0]=0;}
 else {Vec3f normalized=direction/sqrtf(direction.Squared());*(Vec3f*)(out+1)=normalized;out[0]=self->speeds->speed;}
 self->waypointPosition=self->position;return 1;
}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
bool CPathFinder::Bind1(){if(!yawChannel){if(!turnChannel)return false;}else if(turnChannel)return false;return true;}
#endif
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
bool CPathFinder::Bind2(){if(!speedChannel){if(!speedChannelAlt)return false;}else if(speedChannelAlt)return false;return true;}
#endif
unsigned char CPathFinder_IsAtGoal(CPathFinder*self){float d=sqrtf(self->lateralDelta.HorizontalSquared());if(d<self->heightRadiusA && fabsf(self->lateralDelta.y)<self->radius)return 1;return 0;}
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
void CPathFinder::PredictMove(const float*move){predicted=position+Vec3f(move[1],move[2],move[3])*(move[0]/10.0f);}
#endif
extern "C" unsigned char func_002E27F8(float,const float*,const float*,Actor*,int);
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char CPathFinder_AcceptActorSegment(CPathFinder*self,const float*point)
{
 if(!func_002E27F8(self->radiusHolder->radius,&self->position.x,point,self->controller->actor,2))return false;
 return CPathFinder_HasUnsupportedGround(self,point)!=1;
}
#endif
void CPathFinder_BeginSegment(CPathFinder*self)
{
 self->segmentLength=self->position.DistanceFrom(self->previous);
 GetNameTables()->Store(self->slotIndex,self->controller->actor);
 self->flag198=false;
}


struct ServiceClass {int index;unsigned char unknown04[0x104];ServiceClass*parent;};
extern ServiceClass allowedServiceClass __asm__("D_00451778");
extern "C" void func_002E5218(CPathFinder*,const void*);
inline bool ServiceIsA(const ServiceClass*want,const ServiceClass*info){do{if(want==info)return true;info=info->parent;}while(info);return false;}
#if 0
// Unmatched: remaining class-call context, lifetime or scheduling differences.
bool CPathFinder::InstallService(const void*descriptor){const ServiceClass*which=(const ServiceClass*)descriptor;if(!ServiceIsA(&allowedServiceClass,which))return false;ServiceObject *prior=serviceList[which->index];func_002E5218(this,which);if(!prior)serviceList[which->index]->SetGraph(graph);return true;}
#endif

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FEFB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FF250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FF890);
