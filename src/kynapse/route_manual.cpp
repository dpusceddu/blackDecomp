#include "include_asm.h"

#include "kynapse/ai_route_follower.hpp"

static inline void* PS2NodeAt(NavigationGraph* graph,unsigned int ordinal)
{
    if (ordinal>=graph->nodeCapacity) return 0;
    NavigationGraph::NodeRecord* node = (NavigationGraph::NodeRecord*)(ordinal * 20 + (unsigned int)graph->nodes);
    return node->id == -1 ? 0 : node;
}

void* AIRouteFollower::ResolveRequestNode(RouteRequest* request)
{
    RouteRequest* original = request;
    unsigned int ordinal;
    int graphValue;
    unsigned int converted;

    if (!converter)
        goto collect;
    if (graphId != (unsigned int)-1) {
        if (original->GetEndpoint(&ordinal, &graphValue)) {
            if (graphValue == graphId)
                return PS2NodeAt(graph,ordinal);
            if (converter->Convert(original, graphId, &converted))
                return PS2NodeAt(graph,converted);
        }
    }
collect:
    return collectNode(this, original->GetPoint(), 0, 0);
}

bool AIRouteFollower::IsDefaultCollector()
{
    if (collectNode == AIRouteFollower_CollectNodeLoose && !looseGraph)
        return false;
    return true;
}

bool AIRouteFollower::FollowPoint(const float* point, RouteRequest* request)
{
    activated = false;
    ((ActionBank*)world)->ClearActivation();
    Actor* actor = controller->actor;
    position = actor->position;
    movable = true;
    target = *(const Vec3f*)point;
    lastPoint = target;
    MoveRecord move;
    if (!FindNextMove(&move, request))
        return false;
    if (!activated && movable) {
        if (!Deliver(&move))
            return false;
    }
    return true;
}

bool __cdecl AIRouteFollower_ResetSegment(AIRouteFollower* follower, int* result)
{
    *result = 0;
    follower->previous = follower->position;
    follower->Stop();
    return true;
}

extern "C" unsigned int func_00305250(AIRouteFollower* follower, float* output,
                                                            const float* point)
{
    if (!follower->policy)
        return AIRouteFollower_GenerateMove(follower, output, point);
    follower->policy->Apply(point, output);
    return 1;
}

extern "C" void* func_00305378(AIRouteFollower* follower, const float* point,
                                               unsigned char outgoing, unsigned char incoming)
{
    if (!follower->looseGraph)
        return 0;
    return (void*)NavigationGraph_QueryNode(point, follower->controller->actor, follower->radius,
                                            follower->looseGraph, outgoing, incoming);
}


#ifdef NONMATCHING

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
unsigned char __cdecl AIRouteFollower_PublishControls(AIRouteFollower* follower, MoveRecord* move)
{
    AIRouteFollower* self = follower;
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
            double angle;
            if (cosine < 1.0f) {
                if (cosine <= -1.0f)
                    angle = 3.1415927;
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
                ControlChannel* torso = gTorsoBank.GetItem();
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

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
bool AIRouteFollower::FindNextMove(MoveRecord* move, RouteRequest* request)
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
    if (waypointIndex == 0 || waypointIndex == -1 || (guard = guards[waypointIndex - 1]) == 0
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
            if (*((unsigned char*)this + 0x8c) == 1 && pointCount <= (unsigned int)waypoint + 2) {
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
                if (pointCount == 0) {
                    waypoint = -1;
                    point[0] = target.x;
                    point[1] = target.y;
                    point[2] = target.z;
                } else {
                    waypoint = 0;
                    point[0] = points[0].x;
                    point[1] = points[0].y;
                    point[2] = points[0].z;
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
                AIRouteFollower_AdvanceSubgoal(this);
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
        if (guard->Evaluate(controller->actor, &points[0].x + waypoint * 3, world, &done, probe)) {
            movable = false;
        } else {
            simpleMove(this, &output->speed, probe);
        }
        if (done) {
            unsigned int next = waypoint + 1;
            if (next < pointCount) {
                waypoint = next;
                point[0] = points[next].x;
                point[1] = points[next].y;
                point[2] = points[next].z;
            } else {
                point[0] = target.x;
                point[1] = target.y;
                point[2] = target.z;
            }
            for (unsigned int i = waypoint; i < pointCount; ++i) {
                int base = waypoint;
                points[i - base] = points[i];
            }
            pointCount -= waypoint;
            waypoint = 0;
        }
        GetNameTables()->Store(turnSlotIndex, controller->actor);
    }
finish:
    if (oldX == point[0] && oldY == previous.y) {
        if (oldZ == previous.z)
            return true;
    }
    AIRouteFollower_BeginSegment(this);
    return true;
}

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
bool AIRouteFollower::RefreshSearch(bool invalidateStart, bool* changed, RouteRequest* request)
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

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
unsigned char __cdecl AIRouteFollower_CheckSegmentCorridor(AIRouteFollower* follower, const float* point)
{
    int index;
    if (follower->previous.x == follower->target.x && follower->previous.y == follower->target.y &&
        follower->previous.z == follower->target.z)
        return 1;
    index = follower->waypoint;
    if (index == 0) return 1;
    if (index == -1) return 1;
    const Vec3f* end = &follower->points[index];
    const Vec3f* start = end - 1;
    Vec3f delta;
    delta.x = end->x - start->x;
    delta.y = end->y - start->y;
    delta.z = end->z - start->z;
    unsigned int edgeIndex = follower->edgeIds[index - 1];
    float length;
    if (edgeIndex < follower->graph->edgeCapacity && follower->graph->edges[edgeIndex].index != -1 &&
        &follower->graph->edges[edgeIndex])
        length = follower->graph->edges[edgeIndex].GetAuthoredLength();
    else
        length = Vec3_Length(start, end);
    if (length != 0.0f) {
        Vec3f relative = Vector3_SubtractValue(follower->position, *start);
        float along = (relative.x * delta.x + relative.y * delta.y + relative.z * delta.z) * (1.0f / length);
        if (-follower->heightRadiusB <= along && along <= length) {
            Vec3f crossValue;
            const Vec3f* cross = Vector3_CrossPtr(&crossValue, &delta, &relative);
            float lateral = (1.0f / length) * cross->y;
            if (lateral < 0.0f)
                lateral = -lateral;
            if (lateral < follower->corridorWidth)
                return 1;
        }
    }
    unsigned char unsupported = AIRouteFollower_HasUnsupportedGround(follower, point);
    if (unsupported)
        follower->turnState = 2;
    return unsupported == 0;
}

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
unsigned int __cdecl AIRouteFollower_GenerateMove(AIRouteFollower* owner, float* move, const float* point)
{
    Vec3f delta;
    delta.x = point[0] - owner->position.x;
    delta.y = point[1] - owner->position.y;
    delta.z = point[2] - owner->position.z;
    move[3] = delta.z;
    move[1] = delta.x;
    move[2] = delta.y;
    float length = (float)sqrt(move[3] * move[3] + move[2] * move[2] + move[1] * move[1]);
    float planar = (float)sqrt(move[3] * move[3] + move[1] * move[1]);
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

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
unsigned char __cdecl AIRouteFollower_SelectSteeringProbe(AIRouteFollower* follower, const float* from,
                                                          const float* to, float* output)
{
    TraceResult first;
    TraceResult second;
    Vec3f origin, leftPoint, rightPoint;
    float dx = to[0] - from[0];
    float startX = from[0];
    float dy = to[1] - from[1];
    float dz = to[2] - from[2];
    float inverse = 1.0f / (float)sqrt(dx * dx + dz * dz + dy * dy);
    dx = inverse * dx;
    dz = inverse * dz;
    float startY = from[1];
    float step = gWorldScale->unit * 5.0f;
    float startZ = from[2];
    float stepZ = dz * step;
    float endX = dx * step + from[0];
    float endY = inverse * dy * step + from[1];
    float endZ = stepZ + from[2];
    float perpY = inverse * dy * 0.0f;
    float perpZ = dz * 0.0f - dx * 0.0f;
    step = step * 0.33333334f;
    float leftX = (perpY - dz) * step + endX;
    float leftY = perpZ * step + endY;
    float leftZ = (dx - perpY) * step + endZ;
    float sideX = (perpY - dz) * step;
    perpZ = perpZ * step;
    float rightX = endX - sideX;
    float rightY = endY - perpZ;
    float rightZ = endZ - (dx - perpY) * step;
    origin.Set(startX,startY,startZ);
    leftPoint.Set(leftX,leftY,leftZ);
    rightPoint.Set(rightX,rightY,rightZ);
    Actor* actor = follower->controller->actor;
    gTraceHook(&origin.x, &leftPoint.x, actor, &first, 2);
    if (first.fraction != 1.0f) {
        gTraceHook(&origin.x, &rightPoint.x, actor, &second, 2);
        if (second.fraction == 1.0f || first.fraction <= second.fraction) {
            leftPoint.x = rightPoint.x - origin.x;
            leftPoint.y = rightPoint.y - origin.y;
            leftPoint.z = rightPoint.z;
            goto done;
        }
    }
    leftPoint.x = leftPoint.x - origin.x;
    leftPoint.y = leftPoint.y - origin.y;
done:
    output[0] = leftPoint.x;
    output[1] = leftPoint.y;
    output[2] = leftPoint.z - origin.z;
    return 1;
}

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
unsigned char __cdecl AIRouteFollower_AdvanceSubgoal(AIRouteFollower* owner)
{
    float* point = &owner->previous.x;
    if (point[0] == owner->target.x && point[1] == owner->target.y) {
        if (point[2] == owner->target.z)
            return 1;
    }
    unsigned int waypoint = owner->waypoint;
    if (waypoint > 0 && waypoint != 0xffffffff) {
        WaypointGuard* guard = owner->guards[waypoint - 1];
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
    float length = (float)sqrt(dz * dz + dx * dx + dy * dy);
    if (length < owner->heightRadiusB) {
        unsigned int next = nearest + 1;
        if (next < owner->pointCount) {
            owner->waypoint = next;
            const Vec3f* waypointPoint = &owner->points[next];
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

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
unsigned int __cdecl AIRouteFollower_AdvanceSubgoalSmooth(AIRouteFollower* owner)
{
    if (owner->hold)
        return AIRouteFollower_AdvanceSubgoal(owner);
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
    owner->previous.x = owner->points[nearest].x;
    owner->previous.y = owner->points[nearest].y;
    owner->previous.z = owner->points[nearest].z;
    ParameterTables* tables = GetNameTables();
    SegmentGraph* graph = (SegmentGraph*)owner->graph;
    void* probeEdge = &graph->syntheticIndex;
    unsigned int index = owner->waypoint;
    unsigned int steps = 0;
    if (index != owner->pointCount - 1) {
        unsigned int offset = index * 12;
        for (;;) {
            if (index > 0) {
                WaypointGuard* guard = owner->guards[index - 1];
                Actor* actor = owner->controller->actor;
                if (guard && !guard->Check(actor, &actor->position.x, &owner->points[0].x + offset / 4))
                    return 1;
            }
            const Vec3f* next = (const Vec3f*)((char*)owner->points + offset + 12);
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
            SetProbeSegment(graph, &owner->points[0].x + offset / 4, &next->x);
            policy->Cost(actor, probeEdge, &costThrough);
            SetProbeSegment(graph, &owner->controller->actor->position.x, &owner->points[0].x + offset / 4);
            policy->Cost(owner->controller->actor, probeEdge, &costFrom);
            SetProbeSegment(graph, &owner->controller->actor->position.x, &next->x);
            if (!policy->Cost(owner->controller->actor, probeEdge, &costDirect))
                break;
            if (costThrough + costFrom < costDirect)
                break;
            ++steps;
            index = nextIndex;
            offset += 12;
            if (steps >= (unsigned int)owner->unknown4cLimit || index == owner->pointCount - 1)
                break;
        }
    }
    bool reachedTarget = false;
    if (steps < (unsigned int)owner->unknown4cLimit && index + 1 == owner->pointCount) {
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
                    SetProbeSegment(graph, &owner->points[index].x, &owner->target.x);
                    ((FloatSlot*)probeEdge)->SetLength(Vec3_Length(&graph->endPosition, &graph->startPosition));
                    policy->Cost(owner->controller->actor, probeEdge, &costA);
                    SetProbeSegment(graph, &owner->controller->actor->position.x, &owner->points[index].x);
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
                    if (Vec3_DistanceSquared(&owner->points[index], &owner->position) <= reach * reach) {
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
    if (index == current && index + 1 < owner->pointCount) {
        float reach = owner->heightRadiusB;
        if (Vec3_DistanceSquared(&owner->position, &owner->points[current]) < reach * reach)
            index = index + 1;
    }
    if (index != current) {
        owner->waypoint = index;
        if (!reachedTarget) {
            owner->previous.x = owner->points[index].x;
            owner->previous.y = owner->points[index].y;
            owner->previous.z = owner->points[index].z;
        }
        tables->Store(owner->goalSlotIndex, owner->controller->actor);
    }
    return 1;
}

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
unsigned char __cdecl AIRouteFollower_HasUnsupportedGround(AIRouteFollower* follower, const float* point)
{
    float dx = point[0] - follower->position.x;
    float dy = point[1] - follower->position.y;
    float dz = point[2] - follower->position.z;
    float sideX = dy * gSideAxisZ - dz * gSideAxisY;
    float sideY = dz * gSideAxisX - dx * gSideAxisZ;
    float sideZ = dx * gSideAxisY - dy * gSideAxisX;
    float sideLength = (float)sqrt(sideX * sideX + sideY * sideY + sideZ * sideZ);
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
        float length = (float)sqrt(ex * ex + ey * ey + ez * ez);
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

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
float AIRouteFollower::RemainingDistance()
{
    if (IsComplete() == true)
        return Distance(&controller->actor->position, &target);
    float total = Distance(&controller->actor->position, &previous);
    if (previous.x != target.x || previous.y != target.y || previous.z != target.z) {
        if (waypoint != -1) {
            unsigned int next = waypoint + 1;
            if (next < pointCount) {
                const Vec3f* from = &points[waypoint];
                const float* to = &(from + 1)->y;
                do {
                    float dz=to[1] - to[-2];
                    float dx=to[-1] - from->x;
                    ++from;
                    float dy=to[0] - to[-3];
                    to += 3;
                    ++next;
                    total += (float)sqrt(dz * dz + dx * dx + dy * dy);
                } while (next < pointCount);
            }
        }
        total += Distance(&points[pointCount - 1], &target);
    }
    return total;
}

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
bool AIRouteFollower::SetGraphByName(const char* name)
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
    unsigned int count = 0;
    for (unsigned int i = 0; i < serviceCount; ++i) {
        if (serviceList[i])
            serviceList[i]->SetGraph(graph);
        count = serviceCount;
    }
    return true;
}

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
bool AIRouteFollower::SetGraph(NavigationGraph* newGraph)
{
    if (!newGraph) {
        graph = 0;
        graphId = -1;
        routeTable = 0;
        looseGraph = 0;
    } else {
        GraphRegistry* registry = gEngineHandle->FindByClass(&gGraphRegistryClass);
        if (!registry)
            return false;
        graph = newGraph;
        bool found = false;
        if (converter) {
            for (unsigned int i = 0; i < registry->count; ++i) {
                if (registry->items[i]->graph == newGraph) {
                    const char* name = registry->items[i]->name;
                    if (name) {
                        if (!converter->NameToId(name, &graphId))
                            graphId = -1;
                        found = true;
                    }
                    break;
                }
            }
        }
        if (!found)
            graphId = -1;
        routeTable = (RouteTable*)registry->Find((int)newGraph, &gRouteTableClass);
        looseGraph = (NavigationGraph*)registry->Find((int)newGraph, &gLooseGraphClass);
    }
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

// Unmatched: PS2 offsets recovered; stack/vector lifetimes, call contexts and scheduling still differ.
unsigned char AIRouteFollower::Initialize(ChildBuffers* definition)
{
    if (!definition)
        return 0;
    simpleMove = AIRouteFollower_GenerateMove;
    complexMove = AIRouteFollower_GenerateMove;
    stopCondition = (StopFn)AIRouteFollower_IsAtGoal;
    collectNode = AIRouteFollower_CollectNode;
    canGo = (GuardFn)Kaim_AlwaysTrue;
    moveModeCheck = (GuardFn)Kaim_AlwaysTrue;
    nextSubgoal = (SubgoalFn)AIRouteFollower_AdvanceSubgoal;
    SetRouteType(&gRouteTypeKey);
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
        const char* className = classEntry ? classEntry->GetValue() : 0;
        AvoidanceFactory* factory = className ? AIAvoidance_FindClass(className) : 0;
        void* avoidance;
        if (factory) {
            avoidance = factory->create(this);
        } else {
            void* block = Kaim_AllocateTagged(0xfc);
            avoidance = block ? AIAvoidance_Construct(block, this) : 0;
        }
        policy = (MovePolicy*)avoidance;
    }
    if (!ConfigureAll(definition))
        return 0;
    speeds = (SpeedTable*)controller->actor->GetAuthoredProperty(&gForwardKey);
    radiusHolder = (RadiusHolder*)controller->actor->GetAuthoredProperty(&gHeightKey2);
    heightFlag = (HeightFlag*)controller->actor->GetAuthoredProperty(&gHeightFlagKey);
    yawChannel = gBankA.GetItem();
    turnChannel = gBankB.GetItem();
    speedChannel = gBankC.GetItem();
    speedChannelAlt = gBankD.GetItem();
    verticalChannel = gBankE.GetItem();
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
        if (!guardCapacity)
            ((RouteBlock*)((char*)this + 0x6c))->SetMaxPathSize(0x32);
        ListenerRegistry* listeners = gClassRegistry->FindListeners(&gListenerClass2);
        if (listeners)
            Kaim_AddThirdCallback(AIRouteFollower_OnActorEvent, this, controller->actor);
        return 1;
    }
    return 0;
}

// Unmatched: array construction/cleanup and static-counter ownership.
#include "kynapse/route_lifetime.hpp"
namespace Kaim {
RouteFollowerShell::RouteFollowerShell(Collection* collection)
    : TreeOwner(collection)
{
    activated = true;
    waypoint = -1;
    restartSearch = false;
    paused = false;
    routeTable = 0;
    looseGraph = 0;
    hold = false;
    searchOk = false;
    goalNode = 0;
    startNode = 0;
    lastTarget = gOrigin;
    target = gOrigin;
    previous = gOrigin;
    turnState = 0;
    savedTarget = gOrigin;
    savedStart = 0;
    savedGoal = 0;
    unsigned int propertyCount = count;
    if (propertyCount != 0)
        perProperty = new Tolerance[propertyCount];
    else
        perProperty = 0;
    ownedHead = 0;
    static OwnedCounter slots;
    int trackCount = slots.value;
    ownedCount = trackCount;
    if (trackCount == 0) {
        owned = 0;
    } else {
        owned = (Tracked**)KaimAllocate(trackCount * 4);
        for (unsigned int i = 0; i < ownedCount; ++i)
            owned[i] = 0;
    }
    lastPosition = gOrigin;
    policy = 0;
    segmentLength = -1.0f;
}
}

// Unmatched: array construction/cleanup and static-counter ownership.
#include "kynapse/route_lifetime.hpp"
namespace Kaim {
RouteFollowerShell::~RouteFollowerShell()
{
    ListenerRegistry* registry = gEngine->FindByClass(&gListenerClass);
    if (registry)
        registry->Remove(Kaim_ApplyToTarget, this, controller->actor);
    delete[] perProperty;
    if (owned) {
        for (unsigned int i = 0; i < ownedCount; ++i) {
            if (owned[i])
                delete owned[i];
        }
        memoryRelease(owned);
    }
    if (policy)
        delete policy;
}
}

// Unmatched: callback policy widths and configuration control-flow scheduling.
#include "kynapse/route_configuration.hpp"
namespace Kaim {
extern "C" unsigned long ReadRouteDoubleBits(const char*) __asm__("func_0035E730");
extern "C" float NarrowRouteDoubleBits(unsigned long) __asm__("func_00291C68");
inline float ReadRouteFloat(const char* text) { return NarrowRouteDoubleBits(ReadRouteDoubleBits(text)); }
bool RouteFollowerConfig::Configure(ChildBuffers* property)
{
    if (!property)
        return false;
    if (!_stricmp(property->GetSecond(), "Graph"))
        return SetGraph(property->GetValue());
    if (!_stricmp(property->GetSecond(), "DistMinNewGoal")) {
        const char* value = property->GetValue();
        if (value) {
            distMinNewGoal = (float)(ReadRouteFloat(value) * gEngine->unit);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "DistGoal")) {
        const char* value = property->GetValue();
        if (value) {
            distGoal = (float)(ReadRouteFloat(value) * gEngine->unit);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "DistStop")) {
        const char* value = property->GetValue();
        if (value) {
            distStop = (float)(ReadRouteFloat(value) * gEngine->unit);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "DistGoalSlowDown")) {
        const char* value = property->GetValue();
        if (value) {
            distGoalSlowDown = (float)(ReadRouteFloat(value) * gEngine->unit);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "DistSlowDown")) {
        const char* value = property->GetValue();
        if (value) {
            distSlowDown = (float)(ReadRouteFloat(value) * gEngine->unit);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "MaxDeltaHeight")) {
        const char* value = property->GetValue();
        if (value) {
            maxDeltaHeight = (float)(ReadRouteFloat(value) * gEngine->unit);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "DistSubgoalMax")) {
        const char* value = property->GetValue();
        if (value) {
            distSubgoalMax = (float)(ReadRouteFloat(value) * gEngine->unit);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "MaxDeltaAngle")) {
        const char* value = property->GetValue();
        if (value) {
            maxDeltaAngle = Degrees_WrapUnsigned((float)ReadRouteFloat(value));
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "MaxYawSpeed")) {
        const char* value = property->GetValue();
        if (value) {
            maxYawSpeed = (float)ReadRouteFloat(value);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "NbMaxSubgoal")) {
        const char* value = property->GetValue();
        if (value) {
            maxSubgoals = atoi(value);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "HoleHeight")) {
        const char* value = property->GetValue();
        if (value) {
            holeHeight = (float)(ReadRouteFloat(value) * gEngine->unit);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "WidthRatioForHoleDetection")) {
        const char* value = property->GetValue();
        if (value) {
            widthRatio = (float)ReadRouteFloat(value);
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "HoleDistToEdge")) {
        const char* value = property->GetValue();
        if (value) {
            float edge = (float)ReadRouteFloat(value);
            holeDistToEdge = Kaim_WorldUnit() * edge;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "CpuPrudence")) {
        const char* value = property->GetValue();
        if (value) {
            cpuPrudence = (float)ReadRouteFloat(value);
            unsigned int i = 0;
            if (recordCount != 0) {
                int offset = 0;
                do {
                    *(float*)((char*)records + offset + 0x10) = cpuPrudence;
                    ++i;
                    offset += 0x14;
                } while (i < recordCount);
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
        void* policy = FindValue61D30(property->GetValue());
        if (policy) {
            stopPolicy = policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "FindVertex")) {
        void* policy = FindValue61E40(property->GetValue());
        if (policy) {
            vertexPolicy = policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "MoveModeCheck")) {
        void* policy = FindValue61F50(property->GetValue());
        if (policy) {
            moveModePolicy = policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "SimpleMove")) {
        void* policy = FindValue62060(property->GetValue());
        if (policy) {
            simpleMovePolicy = policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "ComplexMove")) {
        void* policy = FindValue62060(property->GetValue());
        if (policy) {
            complexMovePolicy = policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "NextSubgoal")) {
        void* policy = FindValue61D30(property->GetValue());
        if (policy) {
            nextSubgoalPolicy = policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "CanGo")) {
        void* policy = FindValue61F50(property->GetValue());
        if (policy) {
            canGoPolicy = policy;
            return true;
        }
    } else if (!_stricmp(property->GetSecond(), "MaxPathSize")) {
        long size = atoi(property->GetValue());
        route.SetMaxPathSize(size);
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
            if (avoidance && avoidance->Configure(property) == true)
                return true;
            return Kaim_IsHiddenName(property);
        }
        return true;
    }
    long mode = atoi(property->GetValue());
    short narrowed = (short)mode;
    if (narrowed > -1 && narrowed < 3) {
        yawSmoothing = narrowed != 0;
        return true;
    }
    return false;
}

}

// Unmatched: complete registry model; descriptor ownership and inline registration scheduling.
#include "kynapse/route_registry.hpp"
extern "C" void InitializeRouteClass(void*,const char*,void*,void*,int,int) __asm__("func_002E75D0");
extern char RouteClassStorage[] __asm__("D_004548B8");
extern const char RouteClassName[] __asm__("D_00408268");
extern char RouteFactory[] __asm__("func_002FEC10");
extern char RouteClassBase[] __asm__("D_004512B0");
extern void* RegistryOwner __asm__("D_004549C8");
extern char RegistryOwnerTable[] __asm__("D_003E00E0");
extern char BaseObjectTable[] __asm__("D_003E0040");
extern RouteCallbackDescriptor Descriptor004549d0 __asm__("D_004549D0");
extern char Table003eff48[] __asm__("D_003EFF48");
extern const char Name408278[] __asm__("D_408278");
extern char Callback00305010[] __asm__("func_00305010");
extern "C" RouteCallbackRegistry* Registry00393650() __asm__("func_00393650");
extern RouteCallbackDescriptor Descriptor00454ae0 __asm__("D_00454AE0");
extern char Table003eff30[] __asm__("D_003EFF30");
extern const char Name408290[] __asm__("D_408290");
extern char Callback00393950[] __asm__("func_00393950");
extern "C" RouteCallbackRegistry* Registry003936c8() __asm__("func_003936C8");
extern RouteCallbackDescriptor Descriptor00454bf0 __asm__("D_00454BF0");
extern char Table003eff30[] __asm__("D_003EFF30");
extern const char Name4082a0[] __asm__("D_4082A0");
extern char Callback00305340[] __asm__("func_00305340");
extern "C" RouteCallbackRegistry* Registry003936c8() __asm__("func_003936C8");
extern RouteCallbackDescriptor Descriptor00454d00 __asm__("D_00454D00");
extern char Table003eff30[] __asm__("D_003EFF30");
extern const char Name4082b8[] __asm__("D_4082B8");
extern char Callback00305378[] __asm__("func_00305378");
extern "C" RouteCallbackRegistry* Registry003936c8() __asm__("func_003936C8");
extern RouteCallbackDescriptor Descriptor00454e10 __asm__("D_00454E10");
extern char Table003eff18[] __asm__("D_003EFF18");
extern const char Name4082d0[] __asm__("D_4082D0");
extern char Callback00305150[] __asm__("func_00305150");
extern "C" RouteCallbackRegistry* Registry00393740() __asm__("func_00393740");
extern RouteCallbackDescriptor Descriptor00454f20 __asm__("D_00454F20");
extern char Table003eff18[] __asm__("D_003EFF18");
extern const char Name4082e0[] __asm__("D_4082E0");
extern char Callback00305188[] __asm__("func_00305188");
extern "C" RouteCallbackRegistry* Registry00393740() __asm__("func_00393740");
extern RouteCallbackDescriptor Descriptor00455030 __asm__("D_00455030");
extern char Table003eff18[] __asm__("D_003EFF18");
extern const char Name4082f0[] __asm__("D_4082F0");
extern char Callback00305190[] __asm__("func_00305190");
extern "C" RouteCallbackRegistry* Registry00393740() __asm__("func_00393740");
extern RouteCallbackDescriptor Descriptor00455140 __asm__("D_00455140");
extern char Table003eff48[] __asm__("D_003EFF48");
extern const char Name408308[] __asm__("D_408308");
extern char Callback00302198[] __asm__("func_00302198");
extern "C" RouteCallbackRegistry* Registry00393650() __asm__("func_00393650");
extern RouteCallbackDescriptor Descriptor00455250 __asm__("D_00455250");
extern char Table003eff48[] __asm__("D_003EFF48");
extern const char Name408318[] __asm__("D_408318");
extern char Callback00302388[] __asm__("func_00302388");
extern "C" RouteCallbackRegistry* Registry00393650() __asm__("func_00393650");
extern RouteCallbackDescriptor Descriptor00455360 __asm__("D_00455360");
extern char Table003eff18[] __asm__("D_003EFF18");
extern const char Name408328[] __asm__("D_408328");
extern char Callback00305110[] __asm__("func_00305110");
extern "C" RouteCallbackRegistry* Registry00393740() __asm__("func_00393740");
extern RouteCallbackDescriptor Descriptor00455470 __asm__("D_00455470");
extern char Table003eff18[] __asm__("D_003EFF18");
extern const char Name408338[] __asm__("D_408338");
extern char Callback003016e8[] __asm__("func_003016E8");
extern "C" RouteCallbackRegistry* Registry00393740() __asm__("func_00393740");
extern RouteCallbackDescriptor Descriptor00455580 __asm__("D_00455580");
extern char Table003eff18[] __asm__("D_003EFF18");
extern const char Name408348[] __asm__("D_408348");
extern char Callback00305148[] __asm__("func_00305148");
extern "C" RouteCallbackRegistry* Registry00393740() __asm__("func_00393740");
extern RouteCallbackDescriptor Descriptor00455690 __asm__("D_00455690");
extern char Table003eff00[] __asm__("D_003EFF00");
extern const char Name408350[] __asm__("D_408350");
extern char Callback00301a30[] __asm__("func_00301A30");
extern "C" RouteCallbackRegistry* Registry003937b8() __asm__("func_003937B8");
extern RouteCallbackDescriptor Descriptor004557a0 __asm__("D_004557A0");
extern char Table003eff00[] __asm__("D_003EFF00");
extern const char Name408360[] __asm__("D_408360");
extern char Callback00301c68[] __asm__("func_00301C68");
extern "C" RouteCallbackRegistry* Registry003937b8() __asm__("func_003937B8");
extern RouteCallbackDescriptor Descriptor004558b0 __asm__("D_004558B0");
extern char Table003eff00[] __asm__("D_003EFF00");
extern const char Name408370[] __asm__("D_408370");
extern char Callback00305250[] __asm__("func_00305250");
extern "C" RouteCallbackRegistry* Registry003937b8() __asm__("func_003937B8");
extern RouteCallbackDescriptor Descriptor004559c0 __asm__("D_004559C0");
extern char Table003eff00[] __asm__("D_003EFF00");
extern const char Name408388[] __asm__("D_408388");
extern char Callback00305200[] __asm__("func_00305200");
extern "C" RouteCallbackRegistry* Registry003937b8() __asm__("func_003937B8");
static inline bool RegisterRouteDescriptor(RouteCallbackRegistry* registry,RouteCallbackDescriptor* descriptor)
{
    for (int i=0;i<registry->count;++i) {
        if (!strcmp(registry->entries[i]->name,descriptor->name)) {
            registry->entries[i]=descriptor;
            return true;
        }
    }
    if (registry->count==16) { registry->overflowed=1;return false; }
    registry->entries[registry->count++]=descriptor;
    return true;
}
static inline void InitializeRouteDescriptor(RouteCallbackDescriptor& descriptor,void* table,const char* name,void* callback,RouteCallbackRegistry* (*access)())
{
    descriptor.vtable=table;
    strcpy(descriptor.name,name);
    descriptor.callback=callback;
    if (RegisterRouteDescriptor(access(),&descriptor)) descriptor.ordinal=access()->count-1;
    else descriptor.ordinal=-1;
}
extern "C" void func_003039D8(int initialize,int priority)
{
    if (priority!=65535) return;
    if (!initialize) {
        RegistryOwner=RegistryOwnerTable;
        Descriptor004549d0.vtable=BaseObjectTable;
        Descriptor00454ae0.vtable=BaseObjectTable;
        Descriptor00454bf0.vtable=BaseObjectTable;
        Descriptor00454d00.vtable=BaseObjectTable;
        Descriptor00454e10.vtable=BaseObjectTable;
        Descriptor00454f20.vtable=BaseObjectTable;
        Descriptor00455030.vtable=BaseObjectTable;
        Descriptor00455140.vtable=BaseObjectTable;
        Descriptor00455250.vtable=BaseObjectTable;
        Descriptor00455360.vtable=BaseObjectTable;
        Descriptor00455470.vtable=BaseObjectTable;
        Descriptor00455580.vtable=BaseObjectTable;
        Descriptor00455690.vtable=BaseObjectTable;
        Descriptor004557a0.vtable=BaseObjectTable;
        Descriptor004558b0.vtable=BaseObjectTable;
        Descriptor004559c0.vtable=BaseObjectTable;
    } else {
        InitializeRouteClass(RouteClassStorage,RouteClassName,RouteFactory,RouteClassBase,1,1);
        InitializeRouteDescriptor(Descriptor004549d0,Table003eff48,Name408278,Callback00305010,Registry00393650);
        InitializeRouteDescriptor(Descriptor00454ae0,Table003eff30,Name408290,Callback00393950,Registry003936c8);
        InitializeRouteDescriptor(Descriptor00454bf0,Table003eff30,Name4082a0,Callback00305340,Registry003936c8);
        InitializeRouteDescriptor(Descriptor00454d00,Table003eff30,Name4082b8,Callback00305378,Registry003936c8);
        InitializeRouteDescriptor(Descriptor00454e10,Table003eff18,Name4082d0,Callback00305150,Registry00393740);
        InitializeRouteDescriptor(Descriptor00454f20,Table003eff18,Name4082e0,Callback00305188,Registry00393740);
        InitializeRouteDescriptor(Descriptor00455030,Table003eff18,Name4082f0,Callback00305190,Registry00393740);
        InitializeRouteDescriptor(Descriptor00455140,Table003eff48,Name408308,Callback00302198,Registry00393650);
        InitializeRouteDescriptor(Descriptor00455250,Table003eff48,Name408318,Callback00302388,Registry00393650);
        InitializeRouteDescriptor(Descriptor00455360,Table003eff18,Name408328,Callback00305110,Registry00393740);
        InitializeRouteDescriptor(Descriptor00455470,Table003eff18,Name408338,Callback003016e8,Registry00393740);
        InitializeRouteDescriptor(Descriptor00455580,Table003eff18,Name408348,Callback00305148,Registry00393740);
        InitializeRouteDescriptor(Descriptor00455690,Table003eff00,Name408350,Callback00301a30,Registry003937b8);
        InitializeRouteDescriptor(Descriptor004557a0,Table003eff00,Name408360,Callback00301c68,Registry003937b8);
        InitializeRouteDescriptor(Descriptor004558b0,Table003eff00,Name408370,Callback00305250,Registry003937b8);
        InitializeRouteDescriptor(Descriptor004559c0,Table003eff00,Name408388,Callback00305200,Registry003937b8);
    }
}

#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003003B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00300A40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00301418);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003016E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00301A30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00301C68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00301E78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00302198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00302388);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00302EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00303388);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003037B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003039D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00304BE8);
