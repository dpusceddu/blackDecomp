#include "include_asm.h"

#include "kynapse/parameter_tables.hpp"
#ifdef NON_MATCHING
#include "kynapse/graph/parameters.hpp"
#endif

BufferSet::BufferSet()
    : total(0), weight(1.0f)
{
    unsigned int i;
    if (gTableSizeA) {
        values = (float*)KaimAllocate(gTableSizeA * 4);
        sums = (float*)KaimAllocate(gTableSizeA * 4);
    } else {
        values = 0;
        sums = 0;
    }
    if (gTableSizeB)
        ranks = (float*)KaimAllocate(gTableSizeB * 4);
    else
        ranks = 0;
    for (i = 0; i < gTableSizeA; ++i) {
        values[i] = 0;
        sums[i] = 0;
    }
    for (i = 0; i < gTableSizeB; ++i) {
        ranks[i] = -(float)i / 100.0f;
    }
}

IndexTable::IndexTable()
{
    if (gTableSizeA)
        indices = (unsigned int*)KaimAllocate(gTableSizeA * 4);
    else
        indices = 0;
    if (gTableSizeB)
        values = (float*)KaimAllocate(gTableSizeB * 4);
    else
        values = 0;
    for (unsigned int i = 0; i < gTableSizeA; ++i)
        indices[i] = 0;
    for (unsigned int i = 0; i < gTableSizeB; ++i) {
        values[i] = -(float)i / 100.0f;
    }
}

void ParameterTables::Update(float step)
{
    unsigned int slot;
    if (step == kDefaultFloat)
        step = 0.001f;
    if (gPreUpdateHook)
        gPreUpdateHook();
    gUpdateStep = step;
    gUpdateZero = 0.0f;
    gSavedFloat = gElapsed;
    gElapsed += step;
    for (slot = 0; slot < countA; ++slot) {
        a40[slot] = 0;
        a44[slot] = 0;
    }
    for (slot = 0; slot < gSlotOwner->slotCount; ++slot) {
        sets[slot].total = 0;
        for (unsigned int i = 0; i < countA; ++i)
            sets[slot].total += sets[slot].sums[i];
    }
    if (gSlotOwner->slotCount > 0)
        qsort(order, gSlotOwner->slotCount, 4, gCompare);
    gSelected = (unsigned int)-1;
    selected = 0;
    fired = false;
}

ParameterTables::~ParameterTables()
{
    if (a20) memoryRelease(a20);
    if (a24) memoryRelease(a24);
    if (a28) memoryRelease(a28);
    if (b2c) memoryRelease(b2c);
    if (a40) memoryRelease(a40);
    if (a44) memoryRelease(a44);
    if (c30) memoryRelease(c30);
    if (order) memoryRelease(order);
    if (sets) delete[] sets;
    if (indexTables) delete[] indexTables;
    if (a3c) memoryRelease(a3c);
    for (unsigned int i = 0; i < gTableSizeA; ++i)
        if (((char**)a14)[i]) memoryRelease(((char**)a14)[i]);
    if (a14) memoryRelease(a14);
    for (unsigned int i = 0; i < gTableSizeB; ++i)
        if (((char**)b10)[i]) memoryRelease(((char**)b10)[i]);
    if (b10) memoryRelease(b10);
    for (unsigned int i = 0; i < gTableSizeC; ++i)
        if (((char**)c18)[i]) memoryRelease(((char**)c18)[i]);
    if (c18) memoryRelease(c18);
}



ParameterTables::ParameterTables()
{
    unsigned int i;
    threshold = 0.01f;
    if (gTableSizeA > 0) {
        a20 = (float*)KaimAllocate(gTableSizeA * 4);
        a24 = (int*)KaimAllocate(gTableSizeA * 4);
        a28 = (float*)KaimAllocate(gTableSizeA * 4);
        a40 = (float*)KaimAllocate(gTableSizeA * 4);
        a44 = (int*)KaimAllocate(gTableSizeA * 4);
        a14 = (float*)KaimAllocate(gTableSizeA * 4);
        a3c = (float*)KaimAllocate(gTableSizeA * 4);
    } else {
        a20 = 0;
        a24 = 0;
        a28 = 0;
        a40 = 0;
        a44 = 0;
        a14 = 0;
        a3c = 0;
    }
    if (gTableSizeB > 0) {
        b10 = (float*)KaimAllocate(gTableSizeB * 4);
        b2c = (float*)KaimAllocate(gTableSizeB * 4);
    } else {
        b10 = 0;
        b2c = 0;
    }
    if (gTableSizeC > 0) {
        c18 = (float*)KaimAllocate(gTableSizeC * 4);
        c30 = (float*)KaimAllocate(gTableSizeC * 4);
        for (i = 0; i < gTableSizeC; ++i) {
            c18[i] = 0;
            c30[i] = 0;
        }
    } else {
        c18 = 0;
        c30 = 0;
    }
    if (gSlotOwner->slotCount > 0) {
        sets = new BufferSet[gSlotOwner->slotCount];
        order = (int*)KaimAllocate(gSlotOwner->slotCount * 4);
    } else {
        sets = 0;
        order = 0;
    }
    if (gSlotOwner->indexCount > 0)
        indexTables = new IndexTable[gSlotOwner->indexCount];
    else
        indexTables = 0;
    countB = 0;
    countA = 0;
    countC = 0;
    for (i = 0; i < gTableSizeA; ++i) {
        a14[i] = 0;
        a20[i] = 60.0f;
        a24[i] = 10;
        a28[i] = 0;
    }
    for (i = 0; i < gTableSizeB; ++i) {
        b10[i] = 0;
        b2c[i] = 0.1f;
    }
    for (i = 0; i < GetSlotOwner()->slotCount; ++i)
        order[i] = i;
    gCompare = CompareSets;
}

#ifdef NON_MATCHING
// Unmatched: not compared to the original beyond its call and data references.
int AddPeriodicName(const char *name) {
    ParameterTables *tables=GetNameTables();
    if(tables->countB<gTableSizeB) {
        ((char**)tables->b10)[tables->countB++]=(char*)KaimAllocate(strlen(name)+1);
        strcpy(((char**)tables->b10)[tables->countB-1],name);
        return tables->countB-1;
    }
    return -1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/parameter_tables_2e7670", func_002E8650);
#endif
#ifdef NON_MATCHING
// Unmatched: name-array reference and allocation register scheduling.
int AddAperiodicName(const char *name) {
    ParameterTables *tables=GetNameTables();
    if(tables->countA<gTableSizeA) {
        ((char**)tables->a14)[tables->countA++]=(char*)KaimAllocate(strlen(name)+1);
        strcpy(((char**)tables->a14)[tables->countA-1],name);
        return tables->countA-1;
    }
    return -1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/parameter_tables_2e7670", func_002E8740);
#endif
#ifdef NON_MATCHING
// Unmatched: name-array reference and allocation register scheduling.
int AddEstimatedName(const char *name) {
    ParameterTables *tables=GetNameTables();
    if(tables->countC<gTableSizeC) {
        ((char**)tables->c18)[tables->countC++]=(char*)KaimAllocate(strlen(name)+1);
        strcpy(((char**)tables->c18)[tables->countC-1],name);
        return tables->countC-1;
    }
    return -1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/parameter_tables_2e7670", func_002E8830);
#endif
#ifdef NON_MATCHING
// Unmatched: threshold CFG and register allocation.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/parameter_tables_2e7670", func_002E8AB8);
#endif
#ifdef NON_MATCHING
// Unmatched: iterator cleanup and success/error block ordering.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/parameter_tables_2e7670", func_002E8C50);
#endif
#ifdef NON_MATCHING
// Unmatched: fired branch scheduling.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/parameter_tables_2e7670", func_002E8FA0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/parameter_tables_2e7670", func_002E90B8);
