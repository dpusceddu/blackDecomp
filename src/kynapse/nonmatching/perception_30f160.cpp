#include "kynapse/perception.hpp"

#ifdef NONMATCHING
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
#endif
