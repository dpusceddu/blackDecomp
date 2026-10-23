#include "kynapse/perception.hpp"

#ifdef NONMATCHING
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
#endif
