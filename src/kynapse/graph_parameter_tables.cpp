#include "include_asm.h"

#include "kynapse/graph/parameters.hpp"


// Unmatched: name-array reference and allocation register scheduling.

#if 0
int AddPeriodicName(const char *name) {
    ParameterTables *tables=GetNameTables();
    if(tables->countB<gTableSizeB) {
        ((char**)tables->b10)[tables->countB++]=(char*)KaimAllocate(strlen(name)+1);
        strcpy(((char**)tables->b10)[tables->countB-1],name);
        return tables->countB-1;
    }
    return -1;
}
#endif
// Unmatched: name-array reference and allocation register scheduling.
#if 0
int AddAperiodicName(const char *name) {
    ParameterTables *tables=GetNameTables();
    if(tables->countA<gTableSizeA) {
        ((char**)tables->a14)[tables->countA++]=(char*)KaimAllocate(strlen(name)+1);
        strcpy(((char**)tables->a14)[tables->countA-1],name);
        return tables->countA-1;
    }
    return -1;
}
#endif
// Unmatched: name-array reference and allocation register scheduling.
#if 0
int AddEstimatedName(const char *name) {
    ParameterTables *tables=GetNameTables();
    if(tables->countC<gTableSizeC) {
        ((char**)tables->c18)[tables->countC++]=(char*)KaimAllocate(strlen(name)+1);
        strcpy(((char**)tables->c18)[tables->countC-1],name);
        return tables->countC-1;
    }
    return -1;
}
#endif

// Unmatched: threshold CFG and register allocation.
#if 0
bool ParameterTables::Consume(int index,SlotUser *user) {
    if(!(threshold<=0)) {
        unsigned int slot=user->GetIndex();
        if(index>=0 && (unsigned int)index<countA) {
            if(slot>=GetSlotOwner()->slotCount)return false;
            BufferSet *set=0;if(slot!=(unsigned int)-1)set=sets+slot;
            if(!fired) {
                float now=Kaim_QueryFloat();fired=threshold<now;
                if(!fired && a44[index]<a24[index] && !(a40[index]>a20[index])) {
                    ++a44[index];if(set){set->sums[index]=0;set->values[index]=now;}return true;
                }
            }
            if(set)set->sums[index]+=a28[index];
        }
        return false;
    }
    return true;
}
#endif

// Unmatched: iterator cleanup and success/error block ordering.
#if 0
bool ParameterTables::ConsumeList(int index,IndexUser *user) {
    if(threshold<=0)return true;
    if(index<0 || (unsigned int)index>=countA)return false;
    if(fired) {
        for(ParameterSlotIterator cursor(user->slots->first);cursor.IsValid();++cursor) {
            unsigned int slot=cursor.Get()->GetIndex();
            if(slot!=(unsigned int)-1)sets[slot].sums[index]+=a28[index];
        }
        return false;
    }
    float now=Kaim_QueryFloat();
    fired=threshold<now;
    if(!fired && a44[index]<a24[index] && !(a40[index]>a20[index])) {
        ++a44[index];
        for(ParameterSlotIterator cursor(user->slots->first);cursor.IsValid();++cursor) {
            unsigned int slot=cursor.Get()->GetIndex();
            if(slot!=(unsigned int)-1){sets[slot].sums[index]=0;sets[slot].values[index]=now;}
        }
        ((float*)indexTables[user->GetIndex()].indices)[index]=now;
        return true;
    }
    for(ParameterSlotIterator cursor(user->slots->first);cursor.IsValid();++cursor) {
        unsigned int slot=cursor.Get()->GetIndex();
        if(slot!=(unsigned int)-1)sets[slot].sums[index]+=a28[index];
    }
    return false;
}
#endif

// Unmatched: fired branch scheduling.
#if 0
bool ParameterViews::ConsumeGlobal(int index) {
    if(threshold<=0)return true;
    if(index>=0 && (unsigned int)index<countA && !fired) {
        float now=Kaim_QueryFloat();fired=threshold<now;
        if(!fired) {
            if(a44[index]>=a24[index])return false;
            if(a20[index]<a40[index])return false;
            ++a44[index];a3c[index]=now;return true;
        }
    }
    return false;
}
#endif
// Unmatched: recursive fallback and compiler tail recursion.
#if 0
int ParameterTables::NextSlot() {
    if(selected>=0 && (unsigned int)selected>=GetSlotOwner()->slotCount)return -1;
    int index=order[selected++];
    SlotTable *table=GetSlotOwner()->table;
    Slot *slot=(unsigned int)index<table->capacity?table->slots+index:0;
    if(!slot->active)return NextSlot();
    return index;
}
#endif
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

// Unmatched: rank-pointer helper register scheduling.
#if 0
bool ParameterTables::Raise(int index,SlotUser *user) {
    int slot=user->GetIndex();
    if(index>=0 && (unsigned int)index<countB && (unsigned int)slot<GetSlotOwner()->slotCount) {
        float *rank=sets[slot].ranks+index;
        if(*rank+b2c[index]<gSavedFloat){*rank=gSavedFloat;return true;}
    }
    return false;
}
#endif
// Unmatched: rank-pointer helper register scheduling.
#if 0
bool ParameterViews::RaiseIndex(int index,IndexUser *user) {
    int slot=user->GetIndex();
    if(index>=0 && (unsigned int)index<countB && (unsigned int)slot<GetSlotOwner()->indexCount) {
        float *rank=indexTables[slot].values+index;
        if(*rank+b2c[index]<gSavedFloat){*rank=gSavedFloat;return true;}
    }
    return false;
}
#endif
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
// Unmatched: float return register allocation.
#if 0
float ParameterTables::Remaining(int index)
{
    if (index < 0 || (unsigned int)index > countA - 1)
        return kDefaultFloat;
    if (threshold <= kDefaultFloat)
        return 3.402823466e38f;
    float now = gFloatHook ? gFloatHook() : kDefaultFloat;
    float left = threshold - now;
    if (left < kDefaultFloat)
        return kDefaultFloat;
    float room = a20[index] - a40[index];
    if (room < kDefaultFloat)
        return kDefaultFloat;
    if (!(left < room))
        return room;
    return left;
}
#endif
void ParameterViews::MarkFired() {
    if(!fired) {float now=Kaim_QueryFloat();if(threshold<now)fired=1;}
}

