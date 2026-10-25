#include "include_asm.h"

#include "kynapse/graph/parameters.hpp"


// Unmatched: name-array reference and allocation register scheduling.




ParameterTables *GetNameTables() {
    if(!ParameterSingleton)ParameterSingleton=new ParameterTables;
    return ParameterSingleton;
}

int ParameterViews::FindAperiodicName(const char *name)const {
    for(unsigned int i=0;i<countA;++i)if(!_stricmp(name,((char**)a14)[i]))return i;
    return -1;
}
int ParameterViews::FindPeriodicName(const char *name)const {
    for(unsigned int i=0;i<countB;++i)if(!_stricmp(name,((char**)b10)[i]))return i;
    return -1;
}
int ParameterViews::FindEstimatedName(const char *name)const {
    for(unsigned int i=0;i<countC;++i)if(!_stricmp(name,((char**)c18)[i]))return i;
    return -1;
}
int CompareSets(const void* left, const void* right)
{
    ParameterTables* tables = GetNameTables();
    int a = *(const int*)left;
    int b = *(const int*)right;
    BufferSet* setA = &tables->sets[a];
    BufferSet* setB = &tables->sets[b];
    if (a == gSelected)
        return -1;
    if (b == gSelected) {
    later:
        return 1;
    }
    float scoreA = setA->total * setA->weight;
    float scoreB = setB->total * setB->weight;
    if (scoreA > scoreB)
        return -1;
    if (scoreA < scoreB)
        goto later;
    return 0;
}

void ParameterTables::Store(int index,SlotUser *user) {
    int slot=user->GetIndex();
    if(index>=0 && (unsigned int)index<countB && (unsigned int)slot<GetSlotOwner()->slotCount){BufferSet *set=sets+slot;set->ranks[index]=gSavedFloat;}
}
void ParameterTables::Accumulate(int index,SlotUser *user) {
    if(!(threshold<=0)) {
        int slot=user->GetIndex();
        if(index>=0 && (unsigned int)index<countA && (unsigned int)slot<GetSlotOwner()->slotCount) {
            BufferSet *set=sets+slot;
            float now=Kaim_QueryFloat();a40[index]+=now-set->values[index];
        }
    }
}
void ParameterViews::AccumulateIndex(int index,IndexUser *user) {
    if(!(threshold<=0)) {
        int slot=user->GetIndex();
        if(index>=0 && (unsigned int)index<countA && (unsigned int)slot<GetSlotOwner()->indexCount) {
            float now=Kaim_QueryFloat();a40[index]+=now-((float*)indexTables[slot].indices)[index];
        }
    }
}
void ParameterViews::AccumulateGlobal(int index) {
    if(!(threshold<=0) && index>=0 && (unsigned int)index<countA) {
        float now=Kaim_QueryFloat();a40[index]+=now-a3c[index];
    }
}
void ParameterViews::MarkFired() {
    if(!fired) {float now=Kaim_QueryFloat();if(threshold<now)fired=1;}
}

