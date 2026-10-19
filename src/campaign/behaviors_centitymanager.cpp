#include "campaign/behaviors/entities.hpp"

extern int gPerceptionCount;
void Entity_RemoveC(World*, void (__cdecl *)(Entity*,Perception*),Perception*);
Perception::~Perception() {
    delete[] records;
    context=0;
    records=0;
    tracked[0]=0;
    tracked[1]=0;
    tracked[2]=0;
    tracked[3]=0;
    tracked[4]=0;
    tracked[5]=0;
    soundPool=0; originProperty=0;axisProperty=0;groupProperty=0;coneProperty=0;
    if(--gPerceptionCount == 0) {
        if(gPairFlags) {gKaimFree(gPairFlags);gPairFlags=0;}
        if(gPairExpiry) {gKaimFree(gPairExpiry);gPairExpiry=0;}
        if(gPairLineExpiry) {gKaimFree(gPairLineExpiry);gPairLineExpiry=0;}
        if(gPairDistances) {gKaimFree(gPairDistances);gPairDistances=0;}
    }
    Entity_RemoveC(gWorld,OnSubjectRemoved,this);
}

// Unmatched: remaining pair and perception updates need vector/iterator lifetimes.
