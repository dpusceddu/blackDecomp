#include "campaign/graph/path_object.hpp"
extern const unsigned char D_00452158,D_004524A0,D_004525B8;
namespace Kaim {
inline bool PathClassInfo::IsDerivedFrom(PathClassInfo *wanted) {
    PathClassInfo *info = this;
    do {
        if (wanted == info)
            return true;
        info = info->parent;
    } while (info);
    return false;
}

bool CPathObject::Init(ChildBuffers* config)
{
    const char* value = func_002E3330(config, "LinkedEdgeMax");
    if (value)
        capacity = func_0035E750(value);
    if (capacity < 1)
        capacity = 1;
    elements = new CLinkedEdge[capacity];
    listeners = func_002EC058(D_003C9ED4,&D_004525B8);
    return GetClassInfo()->IsDerivedFrom((PathClassInfo *)&D_004524A0);
}

bool CPathObject::Claim(int id, PathPropertySlot* slot)
{
    if (!id || !slot)
        return false;
    if (HasPathSlot(slot)) {
        for (unsigned int i = 0; i < elementCount; ++i) {
            if (elements[i].slot == slot)
                return true;
        }
    }
    if (elementCount >= capacity)
        return false;
    if (!HasPathSlot(slot))
        elements[elementCount].previous = 0;
    else
        elements[elementCount].previous = GetPathSlot(slot);
    SetPathSlot(slot, this);
    elements[elementCount].slot = slot;
    elements[elementCount].id = id;
    ++elementCount;
    return true;
}

bool CPathObject::Release(int id, PathPropertySlot *slot) {
    if (!id || !slot)
        return false;
    unsigned int found = 0;
    for (; found < elementCount; ++found) {
        if (elements[found].slot == slot)
            break;
    }
    if (found == elementCount)
        return false;
    CLinkedEdge *mine = &elements[found];
    OnRelease(id, slot);
    if (GetPathSlot(slot) == this) {
        SetPathSlot(slot, mine->previous);
        return true;
    }
    CPathObject *owner = (CPathObject *)GetPathSlot(slot);
    CLinkedEdge *link = 0;
    if (owner != this) {
        if (!owner)
            return false;
        while (true) {
            unsigned int index = 0;
            for (; index < owner->elementCount; ++index) {
                if (owner->elements[index].slot == slot)
                    break;
            }
            if (index == owner->elementCount)
                return false;
            link = &owner->elements[index];
            owner = (CPathObject *)link->previous;
            if (owner == this || !owner)
                break;
        }
    }
    if (owner && link) {
        unsigned int index = 0;
        for (; index < owner->elementCount; ++index) {
            if (owner->elements[index].slot == slot)
                break;
        }
        if (index != owner->elementCount) {
            link->previous = owner->elements[index].previous;
            return true;
        }
    }
    return false;
}
}
