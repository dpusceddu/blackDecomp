#include "include_asm.h"

#include "kynapse/perception.hpp"

Entity* Perception::NearestVisible()
{
    dirtyGroup = false;
    tracked[0] = 0;
    dirtyCone = true;
    pendingGroup = true;
    FindNearest();
    return tracked[0];
}

Entity* Perception::NearestClear()
{
    dirtyGroup = false;
    dirtyCone = true;
    tracked[1] = 0;
    pendingGroup = true;
    FindNearest();
    return tracked[1];
}

Entity* Perception::NearestAny()
{
    dirtyGroup = false;
    dirtyCone = false;
    tracked[2] = 0;
    pendingCone = true;
    FindNearest();
    return tracked[2];
}

Entity* Perception::NearestVisibleOtherGroup()
{
    dirtyCone = false;
    tracked[3] = 0;
    pendingLine = dirtyGroup = true;
    FindNearest();
    return tracked[3];
}

Entity* Perception::NearestAnyOtherGroup()
{
    dirtyGroup = false;
    dirtyCone = false;
    tracked[5] = 0;
    pendingCone = true;
    FindNearest();
    return tracked[5];
}

void OnSubjectRemoved(Entity* subject, Perception* perception)
{
    if (subject == perception->tracked[0]) {
        perception->tracked[0] = 0;
        perception->pendingCone = true;
    }
    if (subject == perception->tracked[1]) {
        perception->tracked[1] = 0;
        perception->pendingCone = true;
    }
    if (subject == perception->tracked[2]) {
        perception->tracked[2] = 0;
        perception->pendingCone = true;
    }
    if (subject == perception->tracked[3]) {
        perception->tracked[3] = 0;
        perception->pendingCone = true;
    }
    if (subject == perception->tracked[4]) {
        perception->tracked[4] = 0;
        perception->pendingCone = true;
    }
    if (subject == perception->tracked[5]) {
        perception->tracked[5] = 0;
        perception->pendingCone = true;
    }
}


