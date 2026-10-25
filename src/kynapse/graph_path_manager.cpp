#include "include_asm.h"

#include "kynapse/graph/path_manager.hpp"
using namespace Kaim;

inline bool IsA(PathClassInfo *wanted, PathClassInfo *info)
{
    do {
        if (wanted == info)
            return true;
        info = info->parent;
    } while (info);
    return false;
}

CPathObjectManager::~CPathObjectManager()
{
    delete[] segments;
    if (items)
        D_003C87E0(items);
    if (pathListenerCapacity) {
        D_003C87E0(pathListenerFunctions);
        D_003C87E0(pathListenerData);
        D_003C87E0(pathListenerOwners);
        pathListenerFunctions = 0;
        pathListenerData = 0;
        pathListenerOwners = 0;
        pathListenerCount = 0;
        pathListenerCapacity = 0;
    }
    func_002E1058(D_003C9ED4, (void*)func_002F5868, this);
    func_002E1098(D_003C9ED4, (void*)func_002F58E8, this);
}

unsigned int CPathObjectManager::GetSegments(CPointPair **out)
{
    if (!segments) {
        segmentCount = 0;
        for (unsigned int i = 0; i < count; ++i)
            segmentCount += items[i]->SegmentCount();
        if (segmentCount)
            segments = new CPointPair[segmentCount];
        unsigned int n = 0;
        for (unsigned int i = 0; i < count; ++i) {
            CPathObject *object = items[i];
            CPointPair *p = object->Segments();
            for (unsigned int j = 0; j < object->SegmentCount(); ++j)
                segments[n++] = p[j];
        }
    }
    *out = segments;
    return segmentCount;
}

// Unplaced draft, not compiled: readable code kept for reference whose PS2 address is not established (docs/units.md, "Drafts").
#if 0
// Unmatched: mirror-call virtual target registers differ despite matching control flow.
bool CPathObjectManager::Add(CPathObject *object)
{
    if (count >= capacity)
        return false;
    items[count] = object;
    ++count;
    if (!registry) {
        registry = (PathTypeRegistry*)func_002EC058(D_003C9ED4, &pathTypeRegistryClass);
        if (!registry)
            return false;
        for (unsigned int t = 0; t < registry->count; ++t) {
            PathTypeEntry *type = registry->entries[t];
            if (type->mirrored) {
                for (unsigned int i = 0; i < count; ++i)
                    items[i]->MirrorType(type->typeId);
            }
        }
    } else {
        for (unsigned int t = 0; t < registry->count; ++t) {
            PathTypeEntry *type = registry->entries[t];
            if (type->mirrored)
                object->MirrorType(type->typeId);
        }
    }
    return true;
}
#endif

bool CPathObjectManager::Configure(GraphConfig *config)
{
    if (!config)
        return false;
    {
        if (!_stricmp(config->GetSecond(), "MaxNbPathObjects")) {
            const char *text = config->GetValue();
            if (text) {
                capacity = func_0035E750(text);
                return true;
            }
            return false;
        }
    }
    return Ps2Math::Kynapse::IsPrivateProperty(config);
}

extern "C" void func_002F5868(CPathObject *object, CPathObjectManager *self)
{
    if (IsA(&pathObjectClass, object->GetClassInfo()))
        self->Add(object);
}

extern "C" void func_002F58E8(CPathObject *object, CPathObjectManager *self)
{
    if (IsA(&pathObjectClass, object->GetClassInfo()))
        self->Remove(object);
}

bool CPathObjectManager::Remove(CPathObject *object)
{
    object->Replay();
    bool found = false;
    unsigned int i;
    for (i = 0; i < count; ++i) {
        if (items[i] == object) {
            found = true;
            break;
        }
    }
    if (found) {
        for (; i < count - 1; ++i)
            items[i] = items[i + 1];
        --count;
        return true;
    }
    return false;
}

void CPathObjectManager::RemoveListener(PathListener function, void *data, void *owner)
{
    for (unsigned int i = 0; i < pathListenerCapacity; ++i) {
        if (pathListenerFunctions[i] == function && pathListenerData[i] == data && pathListenerOwners[i] == owner) {
            pathListenerFunctions[i] = 0;
            pathListenerData[i] = 0;
            pathListenerOwners[i] = 0;
            return;
        }
    }
}

void CPathObjectManager::NotifyListeners(void *subject, void *owner)
{
    for (unsigned int i = 0; i < pathListenerCapacity; ++i) {
        if (pathListenerFunctions[i] && (pathListenerOwners[i] == owner || !pathListenerOwners[i] || !owner))
            pathListenerFunctions[i](subject, pathListenerData[i]);
    }
}

void CPathObjectManager::AddListener(PathListener function, void *data, void *owner)
{
    unsigned int i = 0;
    for (; i < pathListenerCapacity && pathListenerFunctions[i]; ++i) {}
    if (i != pathListenerCapacity) {
        pathListenerFunctions[i] = function;
        pathListenerData[i] = data;
        pathListenerOwners[i] = owner;
    } else if (pathListenerCount == i) {
        if (!i)
            pathListenerCapacity = *(unsigned int*)((char*)D_003C9ED4 + 0x10);
        else
            pathListenerCapacity = i * 2;
        PathListener *oldFunctions = pathListenerFunctions;
        void **oldData = pathListenerData;
        void **oldOwners = pathListenerOwners;
        pathListenerFunctions = (PathListener*)Allocate(pathListenerCapacity * 4);
        pathListenerData = (void**)Allocate(pathListenerCapacity * 4);
        pathListenerOwners = (void**)Allocate(pathListenerCapacity * 4);
        for (i = 0; i < pathListenerCount; ++i) {
            pathListenerFunctions[i] = oldFunctions[i];
            pathListenerData[i] = oldData[i];
            pathListenerOwners[i] = oldOwners[i];
        }
        for (i = pathListenerCount; i < pathListenerCapacity; ++i) {
            pathListenerFunctions[i] = 0;
            pathListenerData[i] = 0;
            pathListenerOwners[i] = 0;
        }
        if (oldFunctions)
            D_003C87E0(oldFunctions);
        if (oldData)
            D_003C87E0(oldData);
        if (oldOwners)
            D_003C87E0(oldOwners);
        pathListenerFunctions[pathListenerCount] = function;
        pathListenerData[pathListenerCount] = data;
        pathListenerOwners[pathListenerCount] = owner;
        ++pathListenerCount;
    } else {
        for (i = 0; i < pathListenerCapacity; ++i) {
            if (!pathListenerFunctions[i]) {
                pathListenerFunctions[i] = function;
                pathListenerData[i] = data;
                pathListenerOwners[i] = owner;
                ++pathListenerCount;
                break;
            }
        }
    }
}

