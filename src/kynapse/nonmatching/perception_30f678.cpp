#include "kynapse/perception.hpp"

#ifdef NONMATCHING
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
#endif
