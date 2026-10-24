#include "include_asm.h"

#include "kynapse/graph/entity_manager.hpp"

void Perception::Reset()
{
    unsigned int pairs = (unsigned int)(PerceptionWorld()->maxEntities * (PerceptionWorld()->maxEntities - 1)) >> 1;
    if ((int)pairs > 0) {
        memset(gPairFlags, 0, pairs);
        memset(gPairExpiry, 0, pairs << 2);
        memset(gPairLineExpiry, 0, pairs << 2);
        memset(gPairDistances, 0, pairs << 2);
    }
    PerceptionRecord empty;
    for (unsigned int i=0;i<(unsigned int)PerceptionWorld()->maxEntities;++i)
        records[i]=empty;
    pendingCone = true;
    pendingGroup = true;
    pendingLine = true;
}

// Unmatched: iterator return view, authored-vector temporaries and floating guard/register lifetimes.
#if 0
bool Perception::Refresh(unsigned int index)
{
    Entity* self = context->actor;
    EntityTable* table = gWorld->table;
    EntityEntryIterator iterator=table->GetEntry(index);
    {
        EntityEntry* entry = iterator.entry;
        if (entry) {
            Entity* other = entry->entity;
            if (other != self) {
                if ((other->flags & D_00455F24) == 0)
                    return false;
                PerceptionRecord* record = &records[index];
                ParameterTables* tables = GetNameTables();
                char needCone = 1;
                if ((!dirtyCone && (!record->otherGroup || !dirtyGroup)) || gNow <= record->coneExpiry)
                    needCone = 0;
                bool pairDue = record->pairExpiry < gNow;
                unsigned char* base = (unsigned char*)gWorld->table->entries;
                unsigned int otherIndex = (unsigned int)(other->entry - base) / 0x14;
                unsigned int selfIndex = (unsigned int)(self->entry - base) / 0x14;
                if (tables->Consume(computeName, self)) {
                    UpdatePair(selfIndex, otherIndex, needCone);
                    tables->Accumulate(computeName, self);
                }
                bool changed = false;
                if (pairDue) {
                    int mine = -1;
                    if (groupProperty)
                        mine = groupProperty->group;
                    AuthoredGroup* theirs = (AuthoredGroup*)other->GetAuthoredProperty(&gKeyGroup);
                    int their = theirs ? theirs->group : -1;
                    if (mine == -1 || their == -1 || their == mine)
                        record->otherGroup = false;
                    else
                        record->otherGroup = true;
                    record->distance = Kaim_GetPairValue(selfIndex, otherIndex);
                    if (!soundPool)
                        record->heard = false;
                    else
                        record->heard = soundPool->Hears(self, other);
                    changed = true;
                    record->pairExpiry = gNow + recordInterval;
                }
                if (needCone) {
                    char free = Kaim_GetPairFlag(selfIndex, otherIndex);
                    record->blocked = free;
                    AuthoredVector* cone = coneProperty;
                    if (cone) {
                        float range = cone->value.x;
                        float angle = cone->value.y;
                        Vec3 origin = self->position;
                        Vec3 target = other->position;
                        Vec3 axis = self->direction;
                        if (originProperty) {
                            origin = EntityPropertyValue(originProperty);
                        }
                        AuthoredVector* property = (AuthoredVector*)other->GetAuthoredProperty(&gKeyPosition);
                        if (property) {
                            target = EntityPropertyValue(property);
                        }
                        if (axisProperty) {
                            axis = EntityPropertyValue(axisProperty);
                        }
                        if (!record->blocked && InCone(angle, range, &target, &origin, &axis)) {
                            record->inCone = true;
                            record->coneExpiry = gNow + recordInterval;
                            return true;
                        }
                        record->inCone = false;
                        record->coneExpiry = gNow + recordInterval;
                        return true;
                    }
                    record->inCone = free == 0;
                    changed = true;
                    record->coneExpiry = gNow + recordInterval;
                }
                return changed;
            }
        }
    }
    return false;
}
#endif

// Unmatched: iterator and authored-vector value-copy context and register allocation.
#if 0
void Perception::UpdatePair(int a, int b, unsigned char lineCheck)
{
    if (a < 0) return;
    if (a >= gWorld->maxEntities) return;
    if (b < 0) return;
    if (b >= gWorld->maxEntities) return;
    if (a == b) return;
    {
        EntityTable* table = gWorld->table;
        EntityEntryIterator first=table->GetEntry(a);
        EntityEntryIterator second=table->GetEntry(b);
        EntityEntry* secondEntry = second.entry;
        EntityEntry* firstEntry = first.entry;
        if (!firstEntry) return;
        if (!firstEntry->active) return;
        if (!secondEntry) return;
        if (!secondEntry->active) return;
        {
            int index;
            if (a > b)
                index = ((a - 1) * a) / 2 + b;
            else
                index = ((b - 1) * b) / 2 + a;
            Vec3 pointA = firstEntry->entity->position;
            Vec3 pointB = secondEntry->entity->position;
            if (gPairExpiry[index] < gNow) {
                gPairDistances[index] = Vec3_Length(&pointA, &pointB);
                gPairExpiry[index] = gNow + pairInterval;
            }
            if (lineCheck && gPairLineExpiry[index] < gNow) {
                AuthoredVector* property = (AuthoredVector*)firstEntry->entity->GetAuthoredProperty(&gKeyPosition);
                if (property) {
                    pointA = EntityPropertyValue(property);
                }
                property = (AuthoredVector*)secondEntry->entity->GetAuthoredProperty(&gKeyPosition);
                if (property) {
                    pointB = EntityPropertyValue(property);
                }
                bool visible = Kaim_CallHook(&pointA, &pointB, firstEntry->entity, 1);
                gPairFlags[index] = 1 - (visible != 0);
                gPairLineExpiry[index] = gNow + pairInterval;
            }
        }
    }
}
#endif

// Unmatched: iterator temporary lifetime, packed request flags and float register allocation.
#if 0
void Perception::FindNearest(){
 float visible=3.402823466e+38F,clearGroup=3.402823466e+38F,any=3.402823466e+38F,visibleGroup=3.402823466e+38F,clear=3.402823466e+38F,anyGroup=3.402823466e+38F;
 EntityEntryIterator it;it.entry=0;it=gWorld->table->Begin();
 for(;it.entry;it.entry=it.entry->next){
  Entity*other=it.entry->entity;unsigned int index=((SlotUser*)other)->GetIndex();
  if(it.entry && other!=context->actor && (other->flags&gEntityManagerClass.mask) && (Refresh(index)||(*(unsigned int*)&pendingCone&0xffffff))){
   PerceptionRecord*r=&records[index];
   if(r->inCone){if(!tracked[0]||r->distance<visible){tracked[0]=other;visible=r->distance;}
    if(r->otherGroup && (!tracked[3]||r->distance<visibleGroup)){tracked[3]=other;visibleGroup=r->distance;}}
   if(!r->blocked){if(!tracked[1]||r->distance<clear){tracked[1]=other;clear=r->distance;}
    if(r->otherGroup && (!tracked[4]||r->distance<clearGroup)){tracked[4]=other;clearGroup=r->distance;}}
   if(!tracked[2]||r->distance<any){tracked[2]=other;any=r->distance;}
   if(r->otherGroup && (!tracked[5]||r->distance<anyGroup)){tracked[5]=other;anyGroup=r->distance;}
  }
 }
 pendingCone=false;if(dirtyCone)pendingGroup=false;if(dirtyGroup)pendingLine=false;
}
#endif

#ifdef NON_MATCHING
#include "kynapse/perception.hpp"

// Unmatched: iterator/vector lifetimes and branch scheduling differ.
bool Perception::Refresh(unsigned int index)
{
    Entity* self = context->actor;
    EntityTable* table = gWorld->table;
    EntityEntryIterator iterator;
    iterator = table->GetEntry(index);
    {
        EntityEntry* entry = iterator.entry;
        if (entry) {
            Entity* other = entry->entity;
            if (other != self) {
                if ((other->flags & gEntityManagerClass.mask) == 0)
                    return false;
                PerceptionRecord* record = &records[index];
                ParameterTables* tables = GetNameTables();
                char needCone = 1;
                if ((!dirtyCone && (!record->otherGroup || !dirtyGroup)) || gNow <= record->coneExpiry)
                    needCone = 0;
                bool pairDue = record->pairExpiry < gNow;
                unsigned char* base = (unsigned char*)gWorld->table->entries;
                unsigned int otherIndex = (int)(other->entry - base) / 0x14;
                unsigned int selfIndex = (int)(self->entry - base) / 0x14;
                if (tables->Consume(computeName, self)) {
                    UpdatePair(selfIndex, otherIndex, needCone);
                    tables->Accumulate(computeName, self);
                }
                bool changed = false;
                if (pairDue) {
                    int mine = -1;
                    if (groupProperty)
                        mine = groupProperty->group;
                    AuthoredGroup* theirs = (AuthoredGroup*)other->GetAuthoredProperty(&gKeyGroup);
                    int their = theirs ? theirs->group : -1;
                    if (mine == -1 || their == -1 || their == mine)
                        record->otherGroup = false;
                    else
                        record->otherGroup = true;
                    record->distance = Kaim_GetPairValue(selfIndex, otherIndex);
                    if (!soundPool)
                        record->heard = false;
                    else
                        record->heard = soundPool->Hears(self, other);
                    changed = true;
                    record->pairExpiry = gNow + recordInterval;
                }
                if (needCone) {
                    char free = Kaim_GetPairFlag(selfIndex, otherIndex);
                    record->blocked = free;
                    AuthoredVector* cone = coneProperty;
                    if (cone) {
                        float range = cone->value.x;
                        float angle = cone->value.y;
                        Vec3 origin = self->position;
                        Vec3 target = other->position;
                        Vec3 axis = self->direction;
                        if (originProperty) {
                            origin = Vec3(originProperty->value.x, originProperty->value.y, originProperty->value.z);
                        }
                        AuthoredVector* property = (AuthoredVector*)other->GetAuthoredProperty(&gKeyPosition);
                        if (property) {
                            target = Vec3(property->value.x, property->value.y, property->value.z);
                        }
                        if (axisProperty) {
                            axis = Vec3(axisProperty->value.x, axisProperty->value.y, axisProperty->value.z);
                        }
                        if (!record->blocked && InCone(angle, range, &target, &origin, &axis)) {
                            record->inCone = true;
                            record->coneExpiry = gNow + recordInterval;
                            return true;
                        }
                        record->inCone = false;
                        record->coneExpiry = gNow + recordInterval;
                        return true;
                    }
                    record->inCone = free == 0;
                    changed = true;
                    record->coneExpiry = gNow + recordInterval;
                }
                return changed;
            }
        }
    }
    return false;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030F160);
#endif

#ifdef NON_MATCHING
#include "kynapse/perception.hpp"

// Unmatched: iterator lifetimes and floating-point register allocation differ.
void Perception::FindNearest()
{
    float farthest = 3.402823466e+38F;
    float nearestAny = farthest;
    float nearestAnyOther = farthest;
    float nearestVisible = farthest;
    float nearestVisibleOther = farthest;
    float nearestClear = farthest;
    float nearestClearOther = farthest;
    EntityEntryIterator iterator(0);
    iterator = gWorld->table->Begin();
    while (iterator.entry) {
        EntityEntry* entry = iterator.entry;
        Entity* other = entry->entity;
        int index = ((SlotUser*)other)->GetIndex();
        if (entry && other != context->actor && (other->flags & gEntityManagerClass.mask)) {
            if (Refresh(index) || (*(unsigned int*)&pendingCone & 0xffffff)) {
                PerceptionRecord* record = &records[index];
                if (record->inCone) {
                    if (!tracked[0] || record->distance < nearestVisible) {
                        tracked[0] = other;
                        nearestVisible = record->distance;
                    }
                    if (record->otherGroup && (!tracked[3] || record->distance < nearestVisibleOther)) {
                        tracked[3] = other;
                        nearestVisibleOther = record->distance;
                    }
                }
                if (!record->blocked) {
                    if (!tracked[1] || record->distance < nearestClear) {
                        tracked[1] = other;
                        nearestClear = record->distance;
                    }
                    if (record->otherGroup && (!tracked[4] || record->distance < nearestClearOther)) {
                        tracked[4] = other;
                        nearestClearOther = record->distance;
                    }
                }
                if (!tracked[2] || record->distance < nearestAny) {
                    tracked[2] = other;
                    nearestAny = record->distance;
                }
                if (record->otherGroup && (!tracked[5] || record->distance < nearestAnyOther)) {
                    tracked[5] = other;
                    nearestAnyOther = record->distance;
                }
            }
        }
        iterator.entry = iterator.entry->next;
    }
    pendingCone = false;
    if (dirtyCone) pendingGroup = false;
    if (dirtyGroup) pendingLine = false;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030F678);
#endif

#ifdef NON_MATCHING
#include "kynapse/perception.hpp"

// Unmatched: iterator/vector temporaries and square-root scheduling differ.
void Perception::UpdatePair(int a, int b, unsigned char lineCheck)
{
    if (a < 0) return;
    if (a >= gWorld->maxEntities) return;
    if (b < 0) return;
    if (b >= gWorld->maxEntities) return;
    if (a == b) return;
    {
        EntityTable* table = gWorld->table;
        EntityEntryIterator first;
        first = table->GetEntry(a);
        EntityEntryIterator second;
        second = table->GetEntry(b);
        EntityEntry* secondEntry = second.entry;
        EntityEntry* firstEntry = first.entry;
        if (!firstEntry) return;
        if (!firstEntry->active) return;
        if (!secondEntry) return;
        if (!secondEntry->active) return;
        {
            int index;
            if (a > b)
                index = ((a - 1) * a) / 2 + b;
            else
                index = ((b - 1) * b) / 2 + a;
            Vec3 pointA = firstEntry->entity->position;
            Vec3 pointB = secondEntry->entity->position;
            if (gPairExpiry[index] < gNow) {
                float dx = pointB.x - pointA.x;
                float dy = pointB.y - pointA.y;
                float dz = pointB.z - pointA.z;
                gPairDistances[index] = sqrtf(dz * dz + dx * dx + dy * dy);
                gPairExpiry[index] = gNow + pairInterval;
            }
            if (lineCheck && gPairLineExpiry[index] < gNow) {
                AuthoredVector* property = (AuthoredVector*)firstEntry->entity->GetAuthoredProperty(&gKeyPosition);
                if (property) {
                    Vec3 value(property->value.x, property->value.y, property->value.z);
                    pointA = value;
                }
                property = (AuthoredVector*)secondEntry->entity->GetAuthoredProperty(&gKeyPosition);
                if (property) {
                    Vec3 value(property->value.x, property->value.y, property->value.z);
                    pointB = value;
                }
                bool visible = Kaim_CallHook(&pointA, &pointB, firstEntry->entity, 1);
                gPairFlags[index] = 1 - (visible != 0);
                gPairLineExpiry[index] = gNow + pairInterval;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030F940);
#endif
