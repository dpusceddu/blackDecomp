#include "include_asm.h"

#include "kynapse/avoidance.hpp"

SharedUser* CreateAvoidance(void* follower) { return new SharedUser(follower); }

SharedUser::~SharedUser()
{
    --gUserCount;
    if (gUserCount != 0)
        goto finished;
    if (!gSharedReady)
        goto finished;
    {
        delete gSharedA;
        delete gSharedB;
        delete gSharedC;
        gSharedA = 0;
        gSharedB = 0;
        gSharedC = 0;
        gSharedReady = false;
        if (gSharedList) {
            delete[] gSharedList;
            gSharedList = 0;
            gSharedCount = 0;
        }
        if (gCallbacksRegistered == true) {
            Entity_ApplyB(gEngine, (int)SharedOnAdded, (int)this);
            Entity_ApplyD(gEngine, (int)SharedOnRemoved, (int)this);
            gCallbacksRegistered = false;
        }
    }
finished:
    ;
}

#ifdef NONMATCHING
#include "kynapse/avoidance_classes.hpp"
namespace KaimAvoidance {
inline TrackedActor::TrackedActor() {}
inline CandidatePool::CandidatePool(unsigned int count)
{
    head=0; activeCount=0; capacity=count; freeHead=0; storage=0; tail=0;
    if (count) {
        storage=new CandidateNode[count]; freeHead=storage;
        storage->previous=0;
        for (unsigned int i=1; i<capacity; ++i) {
            storage[i].previous=&storage[i-1];
            storage[i].previous->next=&storage[i];
        }
        storage[capacity-1].next=0;
    }
}
inline Candidate& Candidate::operator=(const Candidate& other)
{
    interval=other.interval; frontier=other.frontier;
    lateral=other.lateral; forward=other.forward;
    target.x=other.target.x; target.y=other.target.y; target.z=other.target.z;
    cost=other.cost;
    return *this;
}
inline CandidateNode::CandidateNode() { previous=0; next=0; active=0; }
inline void CandidatePool::Clear()
{
    while (head) {
        head->active=0;
        CandidateNode* next=head->next;
        head->next=freeHead; freeHead=head; head=next;
    }
    tail=0; activeCount=0;
}
inline CandidateIterator CandidatePool::Insert(const Candidate& candidate,CandidateIterator before)
{
    CandidateNode* entry=freeHead;
    if (!entry) return CandidateIterator(0);
    ++activeCount; freeHead=entry->next; entry->candidate=candidate; entry->active=1;
    if (!before.node) {
        if (!tail) {
            head=entry; tail=entry; entry->next=0;
            head->previous=0; tail->previous=0; tail->next=0;
            return CandidateIterator(entry);
        }
        entry->previous=tail; entry->next=0; tail->next=entry; tail=entry;
        return CandidateIterator(entry);
    }
    CandidateNode* previous=before.node->previous;
    entry->next=before.node; before.node->previous=entry; entry->previous=previous;
    if (previous) { previous->next=entry; return CandidateIterator(entry); }
    head=entry;
    return CandidateIterator(entry);
}
static __forceinline int Cell(const Vec3& position,bool useZ)
{
    // The conversion deliberately decrements every negative coordinate,
    // including an exactly negative cell boundary.
    float cellWidth=WorldUnits()*20;
    if ((useZ?position.z:position.x)>=0)
        return (int)(int)((useZ?position.z:position.x)/cellWidth);
    return (int)(int)((useZ?position.z:position.x)/cellWidth)-1;
}
static __forceinline void UpdateCells()
{
    for (unsigned int i=0;i<trackedCount;++i) {
        trackedActors[i].cellX=Cell(trackedActors[i].entity->position,false);
        trackedActors[i].cellZ=Cell(trackedActors[i].entity->position,true);
    }
}
__forceinline void Avoidance::DefaultCandidate()
{
    selected.cost=0;selected.frontier=0;selected.lateral=0;
    CopyVector(&selected.target,&goal);
}

// Unmatched: polymorphic iterator and aggregate lifetimes, then register allocation.
Avoidance::Avoidance(RouteFollower* source)
{
    ++avoidanceOwners;
    route=source;
    if (route) {
        ScalarProperty* p=RouteEntity(route)->GetAuthoredProperty(&obstacleWidthKey);
        if (p) {
            width=p->value;
            if (width==0) width=WorldUnits();
        } else width=WorldUnits();
        p=RouteEntity(route)->GetAuthoredProperty(&obstacleHeightKey);
        if (p) height=p->value;
    } else width=WorldUnits();
    stallThreshold=.8f; stallDelay=.2f; radius=width*.5f;
    diagramHalfWidth=WorldUnits()*2;
    slowSpeedFactor=.25f; frameFlags=0; selectionKind=0;
    directionMode=0; directionDeadline=0;
    speedGraceDeadline=0; zeroGraceDeadline=0; retryDeadline=0;
    candidateSpacing=width*.5f;
    stallEscapeDeadline=0;
    CopyVector(&stallAnchor,&zeroVector); stallDistance=FLT_MAX; stallAnchorTime=0;
    if (!sharedInitialized) {
        sharedDiagram=new Diagram(intervalCapacity);
        rawCandidates=new CandidatePool(candidateCapacity);
        rankedCandidates=new CandidatePool(candidateCapacity);
        sharedInitialized=1;
    }
    if (avoidanceOwners==1 && !callbacksRegistered) {
        RegisterActorCreated(world,OnActorCreated,this);
        RegisterActorRemoved(world,OnActorRemoved,this);
    }
}

// Unmatched: cell conversion, loop register lifetimes and floating scheduling.
void CollectTrackedActors()
{
    if (!trackedActors) trackedActors=new TrackedActor[world->entityCapacity];
    trackedCount=0;
    for (WorldRow* row=world->entities->head;row;row=row->next)
        if (row->entity->flags&avoidanceEntityMask)
            trackedActors[trackedCount++].entity=row->entity;
    UpdateCells();
    qsort(trackedActors,trackedCount,sizeof(TrackedActor),CompareTrackedCells);
}

// Unmatched: stack Vec3/trace object lifetimes and vector arithmetic scheduling.
void Avoidance::BeginUpdate(const Vec3* point)
{
    float elapsed=gameTime-avoidanceTime;
    if (elapsed!=0) { avoidanceTime+=elapsed; RefreshCells(); }
    sharedDiagram->Reset(-diagramHalfWidth,diagramHalfWidth,FLT_MAX);
    rawCandidates->Clear(); rankedCandidates->Clear(); earliestContact=FLT_MAX;
    const Vec3& sourcePosition=RouteEntity(route)->position;
    CopyVector(&position,&sourcePosition);
    CopyVector(&goal,point);
    Vec3 delta;
    delta.x=goal.x-position.x;delta.y=goal.y-position.y;delta.z=goal.z-position.z;
    float length=(float)sqrt((delta.z*delta.z+delta.y*delta.y)+delta.x*delta.x);
    goalDistance=length;
    Vec3 direction=forwardVector;
    if (length>0) {
        float scale=1/length;
        direction.x=delta.x*scale;direction.y=scale*delta.y;direction.z=scale*delta.z;
    } else CopyVector(&direction,&RouteEntity(route)->forward);
    CopyVector(&orientation,DirectionOrientation(&delta,&direction));
    side.x=-direction.z;
    forward.y=direction.y; forward.z=direction.z;
    useOrientation=1;
    forward.x=direction.x; side.y=0; side.z=direction.x;
    if (RouteEntity(route)->speed==0) goalTime=FLT_MAX;
    else goalTime=goalDistance/RouteEntity(route)->speed;
    if (!(goalTime<10)) horizon=10;
    else if (1>goalTime) horizon=1;
    else horizon=goalTime;
    overlapCount=0; overlapWidth=0;
    CopyVector(&overlapCenter,&zeroVector);
}

// Unmatched: cell conversion, loop register lifetimes and floating scheduling.
void RefreshCells()
{
    if (nextTrackingUpdate<avoidanceTime) {
        UpdateCells();
        qsort(trackedActors,trackedCount,sizeof(TrackedActor),CompareTrackedCells);
        nextTrackingUpdate=trackingPeriod+avoidanceTime;
    }
}

// Unmatched: polymorphic iterator and aggregate lifetimes, then register allocation.
void Avoidance::GenerateMove(const Vec3* point,Movement* move)
{
    BeginUpdate(point);
    if (stallEscapeDeadline>avoidanceTime || DetectStalledProgress()) {
        selected.cost=0;selected.frontier=0;selected.lateral=0;selected.forward=goalDistance;
        CopyVector(&selected.target,&goal);
        if (goalDistance>1) {
            float step=WorldUnits()*.5f;
            Vec3 alternate((side.x*.5f+forward.x)*step+position.x,
                (side.y*.5f+forward.y)*step+position.y,(side.z*.5f+forward.z)*step+position.z);
            if (route->acceptPoint(route,&alternate)==1) {
                selected.forward=step;selected.lateral=step*.5f;
                CopyVector(&selected.target,&alternate);
            }
        }
        selectedSpeed=RequestedSpeed()*slowSpeedFactor;
        CopyVector(&target,&selected.target);selectionKind=2;
    } else if (retryDeadline<avoidanceTime) {
        if (!BuildNeighborDiagram() || overlapCount!=0) {
            if (overlapCount>0) {
                float dx=overlapCenter.x-position.x,dz=overlapCenter.z-position.z;
                float lateral=dx*side.x+dz*side.z;
                if (!(lateral<0)) lateral-=overlapWidth;
                else lateral+=overlapWidth;
                selected.lateral=lateral;selected.forward=0;
                float x=selected.lateral*side.x+position.x;
                float y=side.y*selected.lateral+position.y;
                float z=side.z*selected.lateral+position.z;
                selected.target.z=z;selected.target.x=x;selected.target.y=y;
                CopyVector(&target,&selected.target);
                selected.cost=0;selected.frontier=0;selectionKind=3;selectedSpeed=RequestedSpeed()*.25f;
            } else {
                selected.lateral=0;selected.cost=0;selected.frontier=0;
                CopyVector(&selected.target,&goal);
                CopyVector(&target,&goal);
                selectedSpeed=RequestedSpeed();selectionKind=0;
            }
        } else {
            if (!SelectCandidate()) { DefaultCandidate();selectedSpeed=0; }
            CopyVector(&target,&selected.target);
            selectionKind=1;BeginRouteSegment(route);
        }
    }
    if (selectedSpeed==0) {
        if (zeroGraceDeadline>avoidanceTime) selectedSpeed=RequestedSpeed()*slowSpeedFactor;
        else if (previousSpeed>0) retryDeadline=avoidanceTime+.1f;
    } else if (retryDeadline>avoidanceTime) selectedSpeed=0;
    else {
        if (previousSpeed==0) {
            float slow=RequestedSpeed()*slowSpeedFactor;
            if (selectedSpeed>slow) selectedSpeed=slow;
            speedGraceDeadline=avoidanceTime+.5f;zeroGraceDeadline=avoidanceTime+.1f;
        } else {
            float slow=RequestedSpeed()*slowSpeedFactor;
            if (selectedSpeed>slow) {
                if (speedGraceDeadline>avoidanceTime) selectedSpeed=slow;
                else {
                    if (selectionKind!=0) {
                        float square=PlanarDistanceSquared(&position,&goal);
                        float first=EngineWorldUnits(),second=EngineWorldUnits();
                        if (square<second*first+second*first) {
                            selectedSpeed=slow;speedGraceDeadline=avoidanceTime+.5f;
                        }
                    }
                }
            }
        }
    }
    previousSpeed=selectedSpeed;move->speed=selectedSpeed;
    float dx=target.x-position.x,dy=target.y-position.y,dz=target.z-position.z;
    move->direction.z=dz;move->direction.x=dx;move->direction.y=dy;
    CopyVector(&move->orientation,&orientation);
    move->useOrientation=useOrientation;
}

// Unmatched: polymorphic iterator and aggregate lifetimes, then register allocation.
unsigned char Avoidance::DetectStalledProgress()
{
    float unit=WorldUnits(),otherUnit=WorldUnits();
    float z=goal.z-stallAnchor.z,x=goal.x-stallAnchor.x,y=goal.y-stallAnchor.y;
    if ((y*y+x*x)+z*z>unit*otherUnit) {
        CopyVector(&stallAnchor,&goal);
    } else if (!(goalDistance<stallDistance)) {
        if (!(avoidanceTime-stallAnchorTime>stallThreshold)) return 0;
        stallEscapeDeadline=avoidanceTime+stallDelay;
        return 1;
    }
    stallDistance=goalDistance;stallAnchorTime=avoidanceTime;
    return 0;
}

// Unmatched: cell conversion, loop register lifetimes and floating scheduling.
unsigned char Avoidance::BuildNeighborDiagram()
{
    float speed=RequestedSpeed()*slowSpeedFactor;
    Entity* source=RouteEntity(route);
    if (speed<source->speed) speed=source->speed;
    predictedSpeed=speed;
    int x=Cell(position,false),z=Cell(position,true);
    PredictCellContacts(x,z,source);
    float cellWidth=WorldUnits()*20,half=cellWidth*.5f;
    float remainderZ=position.z-z*cellWidth;
    int otherX;
    if (!(position.x-x*cellWidth>half)) {
        PredictCellContacts(x-1,z,source);otherX=x-1;
        if (remainderZ>half) ++z;else --z;
    } else {
        PredictCellContacts(x+1,z,source);otherX=x+1;
        if (remainderZ>half) ++z;else --z;
    }
    PredictCellContacts(otherX,z,source);
    PredictCellContacts(x,z,source);
    earliestContact=sharedDiagram->bestTime;
    return sharedDiagram->pool->activeCount>1;
}

// Unmatched: stack Vec3/trace object lifetimes and vector arithmetic scheduling.
void Avoidance::PredictCellContacts(int x,int z,Entity* source)
{
    // The collected array is nonempty and sorted by the two cell coordinates.
    unsigned int high=trackedCount-1,low=0,mid=high>>1;
    while (high-low>1) {
        TrackedActor& row=trackedActors[mid];
        if (row.cellX<x || (row.cellX<=x && row.cellZ<z)) {
            low=mid; mid=(mid+1+high)>>1;
        } else { high=mid; mid=(mid+low)>>1; }
    }
    if (x<=trackedActors[low].cellX && trackedActors[low].cellX<=x &&
        z<=trackedActors[low].cellZ && trackedActors[low].cellZ<=z) high=low;
    for (unsigned int i=high;i<trackedCount;++i) {
        TrackedActor& row=trackedActors[i];
        if (row.cellX!=x || row.cellZ!=z) return;
        Entity* other=row.entity;
        if (other==source || !(other->flags&avoidanceEntityMask)) continue;
        float upper=position.y>goal.y?position.y:goal.y;
        if (upper+height<other->position.y) continue;
        float lower=position.y<goal.y?position.y:goal.y;
        if (lower-height>other->position.y) continue;
        bool round=true;
        ScalarProperty* diameterProperty=other->GetAuthoredProperty(&obstacleWidthKey);
        ScalarProperty* spanProperty=other->GetAuthoredProperty(&obstacleSpanKey);
        float diameter,span,extent;
        if (diameterProperty) {
            diameter=diameterProperty->value;
            if (spanProperty) {
                span=spanProperty->value;
                if (span>diameter) { round=false; extent=(float)sqrt(diameter*diameter+span*span); }
                else extent=diameter;
            } else { span=diameter;extent=diameter; }
        } else { diameter=EngineWorldUnits();span=diameter;extent=diameter; }
        float contactRadius=diameter*.5f+radius;
        if (round) {
            Vec3 displacement(other->position.x-source->position.x,0,
                other->position.z-source->position.z);
            float square=displacement.x*displacement.x+displacement.z*displacement.z;
            float radiusSquared=contactRadius*contactRadius;
            if (!(square<radiusSquared)) {
                float vx=other->forward.x*other->speed-forward.x*predictedSpeed;
                float vz=other->forward.z*other->speed-forward.z*predictedSpeed;
                float velocitySquared=vx*vx+vz*vz;
                if (!(square>horizon*horizon*velocitySquared+radiusSquared)) {
                    float length=(float)sqrt(square),directionX,directionZ;
                    if (length>0) {
                        const Vec3& direction=DivideVector(displacement,length);
                        directionX=direction.x;directionZ=direction.z;
                    } else { directionX=0;directionZ=0; }
                    if (!(directionX*forward.x+directionZ*forward.z<0)) {
                        float first=horizon,last=first;
                        if (SolveContactTimes(velocitySquared,vx*displacement.x+vz*displacement.z,
                            square-radiusSquared,&first,&last)) {
                            float time=((last+first)-extent/predictedSpeed)*.5f;
                            if (time<goalTime && time<horizon && -.5f<time) {
                                Vec3 predicted=AddVectors(other->position,
                                    ScaleVectorLeft(time*other->speed,other->forward));
                                Vec3 lowEdge=SubtractVectors(predicted,
                                    ScaleVectorRight(ScaleVectorRight(side,.5f),extent));
                                Vec3 highEdge=AddVectors(predicted,
                                    ScaleVectorRight(ScaleVectorRight(side,.5f),extent));
                                float lowOffset=DotVectors(SubtractVectors(lowEdge,position),side);
                                float highOffset=DotVectors(SubtractVectors(highEdge,position),side);
                                float minimum=-diagramHalfWidth;
                                if (lowOffset<minimum) lowOffset=minimum;
                                else if (lowOffset>diagramHalfWidth) lowOffset=diagramHalfWidth;
                                if (highOffset<minimum) highOffset=minimum;
                                else if (highOffset>diagramHalfWidth) highOffset=diagramHalfWidth;
                                float lateral=side.y*0+vx*side.x+vz*side.z;
                                float alignment=DotVectors(forward,other->forward);
                                if (lowOffset<highOffset) {
                                    Interval interval(lowOffset,highOffset,time,lateral,alignment);
                                    sharedDiagram->Merge(interval);
                                } else if (lowOffset>highOffset) {
                                    Interval interval(highOffset,lowOffset,time,lateral,alignment);
                                    sharedDiagram->Merge(interval);
                                }
                            }
                        }
                    }
                }
            } else {
                overlapCount+=1;
                float scale=1/overlapCount;
                Vec3 increment;
                increment.x=(other->position.x-overlapCenter.x)*scale;
                increment.y=(other->position.y-overlapCenter.y)*scale;
                increment.z=(other->position.z-overlapCenter.z)*scale;
                AccumulateVector(&overlapCenter,&increment);
                if (overlapWidth<extent) overlapWidth=extent;
            }
        } else {
            float half=(span-diameter*.25f)*.5f;
            Vec3 first=SubtractVectors(other->position,ScaleVectorLeft(half,other->forward));
            Vec3 last=AddVectors(other->position,ScaleVectorLeft(half,other->forward));
            unsigned short samples=(unsigned short)(1-(int)((span/diameter)*-2));
            Vec3 difference(last.x-first.x,last.y-first.y,last.z-first.z);
            Vec3 step=DivideVector(difference,(float)samples-1);
            Vec3 center(first.x-step.x,first.y-step.y,first.z-step.z);
            Vec3 firstOffset(first.x-position.x,first.y-position.y,first.z-position.z);
            Vec3 a=NormalizeVector(firstOffset);
            Vec3 lastOffset(last.x-position.x,last.y-position.y,last.z-position.z);
            Vec3 b=NormalizeVector(lastOffset);
            if (0<=a.x*forward.x+a.z*forward.z || 0<=b.x*forward.x+b.z*forward.z) {
                float vx=other->forward.x*other->speed-forward.x*predictedSpeed;
                float vz=other->forward.z*other->speed-forward.z*predictedSpeed;
                float velocitySquared=vz*vz+vx*vx;
                float radiusSquared=contactRadius*contactRadius;
                float reach=horizon*horizon*velocitySquared+radiusSquared;
                for (unsigned int remaining=samples;remaining;--remaining) {
                    center.x+=step.x;center.y+=step.y;center.z+=step.z;
                    float dx=center.x-source->position.x,dz=center.z-source->position.z;
                    float square=dz*dz+dx*dx;
                    if (!(square<radiusSquared)) {
                        if (!(square>reach)) {
                            float first=horizon,last=first;
                            if (SolveContactTimes(velocitySquared,dx*vx+dz*vz,
                                square-radiusSquared,&first,&last)) {
                                // Each elongated-body sample uses its width for the contact interval.
                                float time=((last+first)-diameter/predictedSpeed)*.5f;
                                if (time<goalTime && time<horizon && -.5f<time) {
                                    Vec3 predicted=AddVectors(center,
                                        ScaleVectorLeft(time*other->speed,other->forward));
                                    Vec3 lowEdge=SubtractVectors(predicted,
                                        ScaleVectorRight(ScaleVectorRight(side,.5f),diameter));
                                    Vec3 highEdge=AddVectors(predicted,
                                        ScaleVectorRight(ScaleVectorRight(side,.5f),diameter));
                                    float lowOffset=DotVectors(SubtractVectors(lowEdge,position),side);
                                    float highOffset=DotVectors(SubtractVectors(highEdge,position),side);
                                    float minimum=-diagramHalfWidth;
                                    if (lowOffset<minimum) lowOffset=minimum;
                                    else if (lowOffset>diagramHalfWidth) lowOffset=diagramHalfWidth;
                                    if (highOffset<minimum) highOffset=minimum;
                                    else if (highOffset>diagramHalfWidth) highOffset=diagramHalfWidth;
                                    float lateral=vx*side.x+side.y*0+vz*side.z;
                                    float alignment=DotVectors(forward,other->forward);
                                    if (lowOffset<highOffset) {
                                        Interval interval(lowOffset,highOffset,time,lateral,alignment);
                                        sharedDiagram->Merge(interval);
                                    } else if (lowOffset>highOffset) {
                                        Interval interval(highOffset,lowOffset,time,lateral,alignment);
                                        sharedDiagram->Merge(interval);
                                    }
                                }
                            }
                        }
                    } else {
                        overlapCount+=1;
                        float scale=1/overlapCount;
                        float dy=(other->position.y-overlapCenter.y)*scale;
                        float dz=(other->position.z-overlapCenter.z)*scale;
                        overlapCenter.x=(other->position.x-overlapCenter.x)*scale+overlapCenter.x;
                        overlapCenter.y=dy+overlapCenter.y;overlapCenter.z=dz+overlapCenter.z;
                        if (overlapWidth<diameter) overlapWidth=diameter;
                    }
                }
            }
        }
    }
}

// Unmatched: polymorphic iterator and aggregate lifetimes, then register allocation.
unsigned char Avoidance::SelectCandidate()
{
    if (!GenerateCandidates()) return 0;
    ScoreCandidates();
    if (!RankCandidates()) return 0;
    for (CandidateNode* node=rankedCandidates->head;node;node=node->next) {
        switch (directionMode) {
        case 1:
            if (node->candidate.lateral<node->candidate.frontier->low && directionDeadline>avoidanceTime) continue;
            break;
        case 2:
            if (node->candidate.lateral<node->candidate.frontier->low) continue;
            break;
        case 3:
            if (node->candidate.lateral>node->candidate.frontier->high && directionDeadline>avoidanceTime) continue;
            break;
        case 4:
            if (node->candidate.lateral>node->candidate.frontier->high) continue;
            break;
        }
        if ((selected.lateral<0 && node->candidate.lateral>0) ||
            (selected.lateral>0 && node->candidate.lateral<0)) continue;
        if (!route->acceptPoint(route,&node->candidate.target)) continue;
        TraceResult result;
        traceRoute(&node->candidate.target,&goal,RouteEntity(route),&result,2);
        if (result.fraction<1) continue;
        if (node->candidate.frontier->alignment>.2f) {
            if (node->candidate.frontier->time<=0) selectedSpeed=0;
            else if (node->candidate.frontier->time<2 || node->candidate.interval->time<2) selectedSpeed=RequestedSpeed()*slowSpeedFactor;
            else selectedSpeed=RequestedSpeed();
        } else if (node->candidate.frontier->time<=0) selectedSpeed=0;
        else if (node->candidate.frontier->time<2) {
            float factor=node->candidate.frontier->time*.5f;
            if (.5f>factor) factor=.5f;
            selectedSpeed=RequestedSpeed()*slowSpeedFactor*factor;
        } else if (node->candidate.interval->time<2) {
            float factor=node->candidate.interval->time*.5f;
            if (.5f>factor) factor=.5f;
            selectedSpeed=RequestedSpeed()*slowSpeedFactor*factor;
        } else selectedSpeed=RequestedSpeed();
        selected=node->candidate;
        // Read the pools and owner again after route callbacks and publication.
        switch (directionMode) {
        case 0:
            if (node->candidate.lateral<node->candidate.frontier->low) {
                directionMode=3;directionDeadline=avoidanceTime+.2f;
            } else if (node->candidate.lateral>node->candidate.frontier->high) {
                directionMode=1;directionDeadline=avoidanceTime+.5f;
            }
            break;
        case 1:
            if (node->candidate.lateral<node->candidate.frontier->low && directionDeadline<avoidanceTime) {
                directionMode=3;directionDeadline=avoidanceTime+.2f;
            }
            break;
        case 3:
            if (node->candidate.lateral>node->candidate.frontier->high && directionDeadline<avoidanceTime) {
                directionMode=2;directionDeadline=avoidanceTime+.5f;
            }
            break;
        }
        return 1;
    }
    return 0;
}

// Unmatched: polymorphic iterator and aggregate lifetimes, then register allocation.
unsigned char Avoidance::GenerateCandidates()
{
    // Direction modes are authored as 0..4. The original has no default arm.
    bool leftAllowed,rightAllowed,centerAllowed;
    switch (directionMode) {
    case 0: case 1: case 3: leftAllowed=rightAllowed=centerAllowed=true;break;
    case 2: rightAllowed=centerAllowed=true;leftAllowed=false;break;
    case 4: leftAllowed=centerAllowed=true;rightAllowed=false;break;
    }
    // Reset seeds FLT_MAX and Merge only publishes ordered earlier times.
    // Any admitted center therefore assigns earliest before it is read.
    IntervalNode* center=0;Interval* earliest;float firstTime=FLT_MAX;
    for (IntervalNode* row=sharedDiagram->pool->head;row;row=row->next) {

        if (row->interval.high>-radius) {
            if (row->interval.low>radius) break;
            if (row->interval.time<=firstTime) { firstTime=row->interval.time;earliest=&row->interval; }
            if (row->interval.low<=0 && row->interval.high>0) center=row;
        }
    }
    if (firstTime>horizon) firstTime=horizon;
    if (!center || !earliest) return 0;
    float bias=radius,threshold=WorldUnits()*.25f;
    float span=center->interval.high-center->interval.low;
    Candidate candidate;
    if (!(predictedSpeed*.2f>goalDistance)) {
        float alignment=!(earliest->high<0)?earliest->alignment:center->interval.alignment;
        if (!(alignment<.2f)) {
            candidate.forward=predictedSpeed*.5f;candidate.interval=&center->interval;
            candidate.lateral=predictedSpeed*.25f;candidate.cost=1e10f;
            candidate.target.x=candidate.forward*forward.x+candidate.lateral*side.x+position.x;
            candidate.target.y=candidate.forward*forward.y+candidate.lateral*side.y+position.y;
            candidate.target.z=candidate.forward*forward.z+candidate.lateral*side.z+position.z;
            candidate.frontier=earliest;
            rawCandidates->Insert(candidate,CandidateIterator());
        }
    }
    if (centerAllowed) {

        if (!(center->interval.time>5)) {
            // These two authored thresholds deliberately overlap no ordinary center->interval.
            if (.2f<center->interval.alignment && 25<center->interval.time) {
                candidate.interval=&center->interval;candidate.forward=firstTime*predictedSpeed-width;
                if (0<candidate.forward) {
                    candidate.cost=0;
                    candidate.lateral=(center->interval.low+center->interval.high)*.5f-firstTime*center->interval.lateralVelocity;
                    candidate.target.x=candidate.forward*forward.x+candidate.lateral*side.x+position.x;
                    candidate.target.y=candidate.forward*forward.y+position.y;
                    candidate.target.z=candidate.forward*forward.z+candidate.lateral*side.z+position.z;
                    candidate.frontier=earliest;rawCandidates->Insert(candidate,CandidateIterator());
                }
            }
        } else {
            if (center->interval.time<=firstTime) bias=-radius;
            candidate.interval=&center->interval;candidate.forward=firstTime*predictedSpeed+bias;
            if (threshold<candidate.forward && width<span) {
                candidate.frontier=earliest;
                if (center->interval.low+radius<=0 && 0<=center->interval.high-radius) {
                    candidate.target.x=candidate.forward*forward.x+position.x;
                    candidate.lateral=0;candidate.cost=0;
                    candidate.target.y=candidate.forward*forward.y+position.y;
                    candidate.target.z=candidate.forward*forward.z+position.z;
                    rawCandidates->Insert(candidate,CandidateIterator());
                }
                float quotient=span/candidateSpacing;
                unsigned int count=(unsigned short)((int)quotient+1);
                candidate.lateral=(span-(int)(count-1)*candidateSpacing)*.5f+center->interval.low;
                candidate.target.x=candidate.lateral*side.x+candidate.forward*forward.x+position.x;
                candidate.target.y=candidate.forward*forward.y+position.y;
                candidate.target.z=candidate.lateral*side.z+candidate.forward*forward.z+position.z;
                float stepX=side.x*candidateSpacing,stepZ=candidateSpacing*side.z;
                if (count) {
                    float total=(float)(int)count;int index=0;
                    do {
                        candidate.lateral+=candidateSpacing;
                        candidate.target.x+=stepX;candidate.target.z+=stepZ;
                        candidate.cost=1-((float)index+(float)index)/total;
                        candidate.cost=WorldUnits()*candidate.cost*candidate.cost;
                        rawCandidates->Insert(candidate,CandidateIterator());
                        ++index;--count;
                    } while (count);
                }
            }
        }
    }
    if (leftAllowed) {
        Interval* frontier=earliest;float time=firstTime;
        for (IntervalNode* row=center->previous;row;row=row->previous) {

            if (!(row->interval.time<=time)) candidate.forward=radius;
            else {
                if (row->interval.time<5) break;
                time=row->interval.time;frontier=&row->interval;candidate.forward=-radius;
            }
            float distance=time*predictedSpeed;
            candidate.interval=&row->interval;candidate.frontier=frontier;
            candidate.forward=distance+candidate.forward;
            if (!(candidate.forward<threshold)) {
                if (!(row->interval.high-row->interval.low>width)) {
                    if (.2f<row->interval.alignment && 25<row->interval.time) {
                        candidate.lateral=(row->interval.high+row->interval.low)*.5f-time*row->interval.lateralVelocity;
                        candidate.forward=distance-width;
                        if (0<candidate.forward) {
                            candidate.cost=0;
                            candidate.target.x=candidate.forward*forward.x+candidate.lateral*side.x+position.x;
                            candidate.target.y=candidate.forward*forward.y+position.y;
                            candidate.target.z=candidate.forward*forward.z+candidate.lateral*side.z+position.z;
                            rawCandidates->Insert(candidate,CandidateIterator());
                        }
                    }
                } else {
                    float span=row->interval.high-row->interval.low;
                    float quotient=span/candidateSpacing;
                    unsigned int count=(unsigned short)((int)quotient+1);
                    candidate.lateral=row->interval.high-(span-(int)(count-1)*candidateSpacing)*.5f;
                    candidate.target.x=candidate.lateral*side.x+candidate.forward*forward.x+position.x;
                    candidate.target.y=candidate.forward*forward.y+position.y;
                    candidate.target.z=candidate.lateral*side.z+candidate.forward*forward.z+position.z;
                    float stepX=side.x*candidateSpacing,stepZ=candidateSpacing*side.z;
                    if (count) {
                        float total=(float)(int)count;int index=0;
                        do {
                            candidate.lateral-=candidateSpacing;
                            candidate.target.x+=-stepX;candidate.target.z+=-stepZ;
                            candidate.cost=1-((float)index+(float)index)/total;
                            candidate.cost=WorldUnits()*candidate.cost*candidate.cost;
                            rawCandidates->Insert(candidate,CandidateIterator());
                            ++index;--count;
                        } while (count);
                    }
                }
            }
        }
    }
    if (rightAllowed) {
        Interval* frontier=earliest;float time=firstTime;
        for (IntervalNode* row=center->next;row;row=row->next) {

            if (!(row->interval.time<=time)) candidate.forward=radius;
            else {
                if (row->interval.time<5) break;
                time=row->interval.time;frontier=&row->interval;candidate.forward=-radius;
            }
            float distance=time*predictedSpeed;
            candidate.frontier=frontier;candidate.interval=&row->interval;
            candidate.forward=distance+candidate.forward;
            if (!(candidate.forward<threshold)) {
                if (!(row->interval.high-row->interval.low>width)) {
                    if (.2f<row->interval.alignment && 25<row->interval.time) {
                        candidate.lateral=(row->interval.high+row->interval.low)*.5f-time*row->interval.lateralVelocity;
                        candidate.forward=distance-width;
                        if (0<candidate.forward) {
                            candidate.cost=0;
                            candidate.target.x=candidate.forward*forward.x+candidate.lateral*side.x+position.x;
                            candidate.target.y=candidate.forward*forward.y+position.y;
                            candidate.target.z=candidate.forward*forward.z+candidate.lateral*side.z+position.z;
                            rawCandidates->Insert(candidate,CandidateIterator());
                        }
                    }
                } else {
                    float span=row->interval.high-row->interval.low;
                    float quotient=span/candidateSpacing;
                    unsigned int count=(unsigned short)((int)quotient+1);
                    candidate.lateral=(span-(int)(count-1)*candidateSpacing)*.5f+row->interval.low;
                    candidate.target.x=candidate.lateral*side.x+candidate.forward*forward.x+position.x;
                    candidate.target.y=candidate.forward*forward.y+position.y;
                    candidate.target.z=candidate.lateral*side.z+candidate.forward*forward.z+position.z;
                    float stepX=side.x*candidateSpacing,stepZ=candidateSpacing*side.z;
                    if (count) {
                        float total=(float)(int)count;int index=0;
                        do {
                            candidate.lateral+=candidateSpacing;
                            candidate.target.x+=stepX;candidate.target.z+=stepZ;
                            candidate.cost=1-((float)index+(float)index)/total;
                            candidate.cost=WorldUnits()*candidate.cost*candidate.cost;
                            rawCandidates->Insert(candidate,CandidateIterator());
                            ++index;--count;
                        } while (count);
                    }
                }
            }
        }
    }
    return rawCandidates->activeCount>0;
}

// Unmatched: polymorphic iterator and aggregate lifetimes, then register allocation.
void Avoidance::ScoreCandidates()
{
    if (directionDeadline<avoidanceTime) directionMode=0;
    float left,middle,right;
    switch (directionMode) {
    case 0: left=0;middle=WorldUnits()*100;right=0;break;
    case 1: left=WorldUnits()*50;middle=WorldUnits()*100;right=0;break;
    case 2: left=1e12f;middle=WorldUnits()*100;right=0;break;
    case 3: left=0;middle=WorldUnits()*100;right=WorldUnits()*50;break;
    case 4: left=0;middle=WorldUnits()*100;right=1e12f;break;
    }
    for (CandidateNode* node=rawCandidates->head;node;node=node->next)
        ScoreCandidate(&node->candidate,&right,&middle,&left);
}

// Unmatched: polymorphic iterator and aggregate lifetimes, then register allocation.
unsigned char Avoidance::RankCandidates()
{
    for (CandidateNode* node=rawCandidates->head;node;node=node->next) {
        if (!(node->candidate.cost<FLT_MAX)) continue;
        CandidateNode* before=rankedCandidates->head;
        while (before && !(node->candidate.cost<before->candidate.cost)) before=before->next;
        rankedCandidates->Insert(node->candidate,CandidateIterator(before));
    }
    return rankedCandidates->activeCount>0;
}

// Unmatched: 64-bit library return conversion recovered; 11 register differences remain.
inline void Avoidance::SetStallDelay(float value) { if (value>=0) stallDelay=value; }
inline void Avoidance::SetDiagramWidth(float value) { if (value>0) diagramHalfWidth=value*.5f; }
inline void Avoidance::SetSpacing(float value) { if (value>0) candidateSpacing=value*width; }
extern "C" unsigned long ReadDoubleBits(const char*) __asm__("func_0035E730");
extern "C" float NarrowDoubleBits(unsigned long) __asm__("func_00291C68");
inline float ParseFloat(const char* text) { return NarrowDoubleBits(ReadDoubleBits(text)); }
unsigned char Avoidance::Configure(const Property* p)
{
    if (!_stricmp(p->GetKey(),"TrackingUpdatePeriod")) {
        float value=ParseFloat(p->GetText());
        if (value<0) return 0;
        if (value>=0) trackingPeriod=value;
        return 1;
    } else if (!_stricmp(p->GetKey(),"ForcedModeTimerThreshold")) {
        float value=ParseFloat(p->GetText());
        if (value<0) return 0;
        if (value>=0) stallThreshold=value;
        return 1;
    } else if (!_stricmp(p->GetKey(),"ForcedModeTimerDelay")) {
        float value=ParseFloat(p->GetText()); if (value<0) return 0; SetStallDelay(value);
    } else if (!_stricmp(p->GetKey(),"CollisionDiagrammWidth")) {
        float value=ParseFloat(p->GetText()); if (value<=0) return 0; SetDiagramWidth(WorldUnits()*value);
    } else if (!_stricmp(p->GetKey(),"AvoidanceCandidateSpacing")) {
        float value=ParseFloat(p->GetText()); if (value<=0) return 0; SetSpacing(value);
    } else if (!_stricmp(p->GetKey(),"SlowSpeedFactor")) slowSpeedFactor=ParseFloat(p->GetText());
    else return 0;
    return 1;
}

}
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00306848);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003071A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00307480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003077F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00307970);
