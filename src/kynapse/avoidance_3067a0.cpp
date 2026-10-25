#include "include_asm.h"

#include "kynapse/avoidance.hpp"
#ifdef NON_MATCHING
#include "kynapse/avoidance_classes.hpp"
#endif

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


INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00306848);
#ifdef NON_MATCHING
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
inline void Avoidance::SetStallDelay(float value) { if (value>=0) stallDelay=value; }
inline void Avoidance::SetDiagramWidth(float value) { if (value>0) diagramHalfWidth=value*.5f; }
inline void Avoidance::SetSpacing(float value) { if (value>0) candidateSpacing=value*width; }
extern "C" unsigned long ReadDoubleBits(const char*) __asm__("func_0035E730");
extern "C" float NarrowDoubleBits(unsigned long) __asm__("func_00291C68");
inline float ParseFloat(const char* text) { return NarrowDoubleBits(ReadDoubleBits(text)); }
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
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003071A8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00307480);
#ifdef NON_MATCHING
namespace KaimAvoidance {
// Unmatched: cell conversion, loop register lifetimes and floating scheduling.
void RefreshCells()
{
    if (nextTrackingUpdate<avoidanceTime) {
        UpdateCells();
        qsort(trackedActors,trackedCount,sizeof(TrackedActor),CompareTrackedCells);
        nextTrackingUpdate=trackingPeriod+avoidanceTime;
    }
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003077F0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00307970);
