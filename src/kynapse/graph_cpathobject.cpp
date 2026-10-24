#include "kynapse/graph/path_object.hpp"
extern const unsigned char D_00452158,D_004524A0,D_004525B8;
namespace Kaim {
void CPathObject::Replay()
{
    unsigned int i; PathTypeRegistry* registry = (PathTypeRegistry*)func_002EC058(D_003C9ED4,&D_00452158);
    if (registry) {
        for(i = 0; i < registry->count; ++i) {
            int id = registry->entries[i]->typeId;
            if (registry->HasId(id)) {
                if (registry->entries[i]->mirrored)
                    OnType(id);
            }
        }
        for(i = 0; i < elementCount; ++i) {
            CLinkedEdge* record = &elements[i];
            if (registry->HasId(record->id))
                Release(record->id, record->slot);
        }
        elementCount = 0;
    }
}
}
#include "kynapse/graph/path_object.hpp"
extern const unsigned char D_00452158,D_004524A0,D_004525B8;
namespace Kaim {
CPathObject::~CPathObject()
{
    delete[] elements;
}
}

#if 0

// Unmatched: class-hierarchy traversal loop arrangement.
#include "kynapse/graph/path_object.hpp"
extern const unsigned char D_00452158,D_004524A0,D_004525B8;
namespace Kaim {
bool CPathObject::Init(ChildBuffers* config)
{
    const char* value = func_002E3330(config, "LinkedEdgeMax");
    if (value)
        capacity = func_0035E750(value);
    if (capacity < 1)
        capacity = 1;
    elements = new CLinkedEdge[capacity];
    listeners = func_002EC058(D_003C9ED4,&D_004525B8);
    PathClassInfo* info = GetClassInfo();
    do {
        if (info == (PathClassInfo *)&D_004524A0)
            return true;
        info = info->parent;
    } while (info);
    return false;
}
}

// Unmatched: slot accessor inline context and scan loops.
#include "kynapse/graph/path_object.hpp"
extern const unsigned char D_00452158,D_004524A0,D_004525B8;
namespace Kaim {
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
    elements[elementCount].previous = HasPathSlot(slot) ? GetPathSlot(slot) : 0;
    SetPathSlot(slot, this);
    elements[elementCount].slot = slot;
    elements[elementCount].id = id;
    ++elementCount;
    return true;
}
}

// Unmatched: owner-chain helper context and loop lifetimes.
#include "kynapse/graph/path_object.hpp"
extern const unsigned char D_00452158,D_004524A0,D_004525B8;
namespace Kaim {
bool CPathObject::Release(int id, PathPropertySlot* slot)
{
    if (!id || !slot)
        return false;
    unsigned int found = 0;
    for (; found < elementCount; ++found) {
        if (elements[found].slot == slot)
            break;
    }
    if (found == elementCount)
        return false;
    CLinkedEdge* mine = &elements[found];
    OnRelease(id, slot);
    CPathObject* owner = (CPathObject*)GetPathSlot(slot);
    if (owner == this) {
        SetPathSlot(slot, mine->previous);
        return true;
    }
    CLinkedEdge* link = 0;
    for (; owner != this; owner = (CPathObject*)link->previous) {
        if (!owner)
            return false;
        unsigned int index = 0;
        for (; index < owner->elementCount; ++index) {
            if (owner->elements[index].slot == slot)
                break;
        }
        if (index == owner->elementCount)
            return false;
        link = &owner->elements[index];
    }
    if (owner && link) {
        unsigned int index = 0;
        for (; index < elementCount; ++index) {
            if (elements[index].slot == slot)
                break;
        }
        if (index != elementCount) {
            link->previous = elements[index].previous;
            return true;
        }
    }
    return false;
}
}

#endif

unsigned int Kaim::CPathObject::Slot5(unsigned int a, unsigned int b, PathCallback *callback, unsigned int c)
{
    return callback->Filter(a, b, c);
}
void Kaim::CPathObject::OnType(int)
{
    Notify(0);
}
