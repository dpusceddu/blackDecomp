#ifndef BLACK_KYNAPSE_AVOIDANCE_HPP
#define BLACK_KYNAPSE_AVOIDANCE_HPP
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);
struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void* operator new[](unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
    static void operator delete[](void* block) { memoryRelease(block); }
};

// Recovered PS2 avoidance layouts. The member at 0x98 has its own vtable.
struct SharedUser : ObjectBase {
    unsigned char unknown04[0x94];
    ObjectBase marker;
    unsigned char unknown9c[0x60];
    SharedUser(void* follower);
    virtual ~SharedUser();
};
struct AvoidanceActor {
    unsigned char unknown00[0x30];
    float position[3];
};
struct SharedRecord : ObjectBase {
    AvoidanceActor* actor;
    int cellX;
    int cellZ;
};
struct AvoidanceEngine {
    unsigned char unknown00[0x0c];
    float frameTime;
};
extern AvoidanceEngine* gEngine;
extern unsigned short gUserCount;
extern unsigned char gSharedReady;
extern unsigned char gCallbacksRegistered;
extern ObjectBase* gSharedA;
extern ObjectBase* gSharedB;
extern ObjectBase* gSharedC;
extern SharedRecord* gSharedList;
extern unsigned int gSharedCount;
extern float gTrackingTime;
extern float gNextTrackingTime;
extern float gTrackingPeriod;
void SharedOnAdded(SharedUser*, void*);
void SharedOnRemoved(SharedUser*, void*);
void Entity_ApplyB(AvoidanceEngine*, int, int);
void Entity_ApplyD(AvoidanceEngine*, int, int);
int CompareSharedRecords(const void*, const void*);

// Candidate nodes have a virtual header, nine payload words, links and a byte flag.
struct AvoidanceCandidate {
    void* vtable;
    unsigned int key;
    unsigned int values[7];
    float score;
    AvoidanceCandidate* previous;
    AvoidanceCandidate* next;
    unsigned char active;
    unsigned char tail[3];
};
struct AvoidanceCandidateList {
    void* vtable;
    unsigned int unknown04;
    AvoidanceCandidate* first;
    AvoidanceCandidate* last;
    AvoidanceCandidate* free;
    unsigned int count;
    unsigned int capacity;
};
extern AvoidanceCandidateList* gCandidates;
extern AvoidanceCandidateList* gSortedCandidates;

struct AvoidanceState {
    void* vtable;
    void* follower;
    float radius;
    float halfRadius;
    unsigned char unknown10[0x24];
    float position[3];
    float target[3];
    float targetDistance;
    float direction[3];
    float side[3];
    float maximumDistance;
    float speed;
    unsigned int unknown70;
    float nearestDistance;
    float movement;
    unsigned char unknown7c[0x10];
    int mode;
    unsigned char unknown90[0x58];
    float forcedModeThreshold;
    float forcedModeDelay;
    float diagramHalfWidth;
    float candidateSpacing;
    float slowSpeedFactor;
};
typedef char VerifiedSharedUserSize[sizeof(SharedUser) == 0xfc ? 1 : -1];
typedef char VerifiedSharedRecordSize[sizeof(SharedRecord) == 0x10 ? 1 : -1];
#endif
