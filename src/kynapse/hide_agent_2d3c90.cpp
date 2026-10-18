#include "kynapse/hide_agent.hpp"
using namespace HideRecovery;
extern char D_00404400[];
const char rodata_00404400[56] __asm__("D_00404400") __attribute__((aligned(8))) = "CHideAgent" "\000\000\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim11CGraphPoint" "\000\000\000";
extern unsigned int D_0044F018,D_003E2AE0,D_003E3428[];
extern unsigned int *D_0044F128;
extern int (*D_003C87E0)(void *);
extern "C" void *func_002D3C90();
extern "C" int func_002DFF98(HideAgent *,int);
extern "C" void func_002E00F0(void *,const char *,void *(*)(),int,int,int);
extern "C" void func_002D5008(int initialize,int priority) {
    if (priority==0xffff) {
        if (initialize) {
            func_002E00F0(&D_0044F018,D_00404400,func_002D3C90,0,0,0);
            return;
        }
        D_0044F128=&D_003E2AE0;
    }
}
extern "C" int func_002D50E8(HideAgent *self,int flags) {
    *(void **)self=D_003E3428;
    if (self->dangerous)D_003C87E0(self->dangerous);
    if (self->nodes)D_003C87E0(self->nodes);
    func_002DFF98(self,0);
    int result=flags&1;
    if (result)result=D_003C87E0(self);
    return result;
}
extern "C" int func_002D5178(HideAgent *self) {
    if (self->provider)return self->perception!=0;
    return 0;
}
extern "C" const Vec3 *func_002D5368(HideAgent *self) {
    if (self->found) {
        if (self->fresh)return &self->destination;
    }
    return &self->context->actor->position;
}
namespace HideRecovery {
    int HideAgent::AddDangerous(Actor *actor) {
        if (dangerousCount>=maxDangerous)return 0;
        dangerous[dangerousCount]=actor;
        ++dangerousCount;
        return 1;
    }
}
extern "C" void func_002D53B0() {
    func_002D5008(1,0xffff);
}
extern "C" void func_002D53D0() {
    func_002D5008(0,0xffff);
}

#ifdef NONMATCHING
// Unmatched: independent initialization-store scheduling differs.
extern "C" void func_002DFF10(HideAgent *, Context *);
extern "C" HideAgent *func_002D5068(HideAgent *self, Context *context) {
    func_002DFF10(self, context);
    *(void **)self = D_003E3428;
    self->rank = -1;
    self->currentId = 0x7fffffff;
    self->maxDangerous = 20;
    self->graphSlot = (unsigned int)-1;
    self->perception = 0;
    self->provider = 0;
    self->offsetProperty = 0;
    self->dangerous = 0;
    self->nodes = 0;
    self->dangerousCount = 0;
    self->graph = 0;
    self->lookup = 0;
    self->currentNode = 0;
    return self;
}
#endif

#ifdef NONMATCHING
// Unmatched: configuration return branches differ.
extern const char D_00404350[];
extern const char D_00404358[];
extern const char D_00404368[];
extern const char D_00404378[];
extern const char D_00404388[];
extern const char D_00404398[];
namespace HideRecovery {
    bool HideAgent::Configure(ChildBuffers* entry)
   {
        if (!entry)
        return false;
        const char* key = entry->GetSecond();
        if (!func_00360838(key, D_00404350)) {
            ItemList* list = (ItemList*)((ClassRegistryB*)gEngine)->FindByClass(&gTypeListClass);
            if (!list)
            return false;
            const char* value = entry->GetValue();
            if (value) {
                void* id = list->IdByName(value);
                if (!id)
                return false;
                return SetGraph(id);
            }
        }
        else if (!func_00360838(key, D_00404358)) {
            const char* value = entry->GetValue();
            if (value) {
                if (!func_00360838(value, D_00404368)) {
                    mode = 1;
                    return true;
                }
                if (!func_00360838(value, D_00404378)) {
                    mode = 2;
                    return true;
                }
            }
        }
        else if (!func_00360838(key, D_00404388)) {
            const char* value = entry->GetValue();
            if (value) {
                long parsed = func_0035E730(value);
                Engine* engine = gEngine;
                maxDeltaHeight = func_00291C68(parsed) * engine->unit;
                return true;
            }
        }
        else if (!func_00360838(key, D_00404398)) {
            const char* value = entry->GetValue();
            if (value) {
                maxDangerous = func_0035E750(value);
                return true;
            }
        }
        if (entry->GetSecond() && *entry->GetSecond() == '_')
        return true;
        return false;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: allocator lifetimes and preparation/validation branches differ.
namespace HideRecovery {
    bool HideAgent::Init(ChildBuffers* config)
   {
        destination = gOrigin;
        allHidden = false;
        active = false;
        dangerousCount = 0;
        found = false;
        fresh = true;
        stage = -1;
        farLimit = 0;
        nearLimit = 3.4028235e38f;
        hasBest = false;
        bestScore = -3.4028235e38f;
        maxDeltaHeight = gEngine->unit;
        NameTable* names = GetNameTables();
        computeName = names->FindName("CHideAgent::ComputeDestination");
        nextTime = 0;
        checkName = names->FindName("CHideAgent::CheckPositionVisible");
        graph = 0;
        mode = 2;
        if (ConfigureAll(config)) {
            provider = (TargetEntity*)((ClassRegistryA*)context)->FindByClass(&gTargetClass);
            perception = ((ClassRegistryA*)context)->FindByClass(&gPerceptionClass);
            lookup = (LookupService*)((ClassRegistryB*)gEngine)->FindByClass(&gLookupClass);
            offsetProperty = (VectorProperty*)context->actor->GetAuthoredProperty(&gKeyPosition);
            if (Prepare()) {
                if (Validate()) {
                    if (maxDangerous > 0) {
                        dangerous = (Actor**)KaimAllocate(maxDangerous * 4);
                        nodes = (void**)KaimAllocate(maxDangerous << 2);
                    }
                    return true;
                }
            }
        }
        return false;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: registry/component iterator registers differ.
namespace HideRecovery {
    bool HideAgent::SetGraph(void* id)
   {
        graph = (NodeGraph*)id;
        graphSlot = -1;
        section = 0;
        TypeList* types = (TypeList*)((ClassRegistryB*)gEngine)->FindByClass(&gTypeListClass);
        if (!types)
        return false;
        LookupService* slots = (LookupService*)((ClassRegistryB*)gEngine)->FindByClass(&gLookupClass);

        if (types->count > 0) {
            TypeEntry** cursor = types->entries;
            unsigned int i = 0;
            do {
                TypeEntry* entry = *cursor;
                if (entry->id == (int)graph) {
                    unsigned int j = 0;
                    if (entry->componentCount > 0) {

                        do {
                            if (entry->components[j]->GetClassInfo() == &gSectionClass) {
                                section = (NodeGraph*)entry->components[j];
                                break;
                            }
                            ++j;
                        }
                        while (j < entry->componentCount);
                    }
                    if (slots && !slots->Lookup(entry->key, &graphSlot))
                    graphSlot = -1;
                    return true;
                }
                ++i;
                ++cursor;
            }
            while (i < types->count);
        }
        return true;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: controller-object lifetimes and return branches differ.
namespace HideRecovery {
    bool HideAgent::Update()
   {
        bank->ClearActivation();
        allHidden = true;
        unsigned int i = 0;
        if (dangerousCount > 0) {
            do {
                if (!((Perception*)perception)->GetRecord(dangerous[i])->hidden) {
                    allHidden = false;
                    break;
                }
                ++i;
            }
            while (i < dangerousCount);
        }
        float now = gNow;
        if (nextTime < now) {
            ParameterTables* tables = (ParameterTables*)GetNameTables();
            if (tables->Consume(computeName, context->actor)) {
                found = Search();
                tables->Accumulate(computeName, context->actor);
                nextTime = now + 0.1f;
            }
        }
        if (!fresh)
        return true;
        if (!found) {
            destination = context->actor->position;
            return false;
        }
        bool ok;
        if (graphSlot != -1) {
            FollowQuery query((const int*)&destination, currentId, rank);
            ok = provider->QueryTransform(&query);
        }
        else {
            ok = provider->Query(&destination);
        }
        if (ok) {
            bank->Select(provider->id);
            active = provider->IsActive();
            return true;
        }
        return false;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: packed visibility-state and vector-temporary scheduling differs.
namespace HideRecovery {
    bool HideAgent::Search()
   {
        Vec3 offset = gOrigin;
        if (offsetProperty) {
            Vec3 propertyPosition = offsetProperty->value;
            offset.y = propertyPosition.y - context->actor->position.y;
        }
        if (visibilityState == 0x101) {
            Vec3 shifted;
            shifted.x = gOrigin.x + destination.x;
            shifted.y = offset.y + destination.y;
            shifted.z = gOrigin.z + destination.z;
            Vec3 observer = gOrigin;
            unsigned int i = 0;
            if (dangerousCount > 0) {
                do {
                    VectorProperty* property = (VectorProperty*)dangerous[i]->GetAuthoredProperty(&gKeyPosition);
                    if (property) {
                        Vec3 position;
                        position.x = property->value.x;
                        position.y = property->value.y;
                        position.z = property->value.z;
                        observer = position;
                    }
                    else {
                        observer = dangerous[i]->position;
                    }
                    if (Kaim_CallHook(&observer, &shifted, dangerous[i], 1))
                    goto rescan;
                    ++i;
                }
                while (i < dangerousCount);
            }
        }
        if (found && dangerousCount > 0 && fresh)
        return found;
        rescan:
        if (!graph)
        return false;
        Scan(&offset);
        return found;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: candidate loop and graph-query register allocation differs.
namespace HideRecovery {
    void HideAgent::Scan(const Vec3* offset)
   {
        if (stage == -1 && graphSlot != -1) {
            if (mode == 1) {
                unsigned int i = 0;
                if (dangerousCount > 0) {
                    do {
                        if (section) {
                            nodes[i] = NavigationGraph_QueryNode(&dangerous[i]->position, context->actor,
                            maxDeltaHeight, section, 0, 0);
                        }
                        else {
                            nodes[i] = NavigationGraph_FindNearestNode(graph, &dangerous[i]->position, context->actor,
                            maxDeltaHeight, 0, 0);
                        }
                        if (!nodes[i]) {
                            fresh = true;
                            hasBest = false;
                            found = false;
                            return;
                        }
                        ++i;
                    }
                    while (i < dangerousCount);
                }
            }
            else if (mode == 2) {
                void* node;
                if (section) {
                    node = NavigationGraph_QueryNode(&context->actor->position, context->actor, maxDeltaHeight, section,
                    0, 0);
                }
                else {
                    node = NavigationGraph_FindNearestNode(graph, &context->actor->position, context->actor,
                    maxDeltaHeight, 0, 0);
                }
                currentNode = node;
                if (!node) {
                    fresh = true;
                    hasBest = false;
                    found = false;
                    return;
                }
            }
        }
        unsigned int index = stage + 1;
        if (index < graph->count) {
            do {
                if (index < graph->capacity && graph->items[index].id != -1 && &graph->items[index]) {
                    bool handled;
                    if (!Consider(&graph->items[index], offset, &handled)) {
                        stage = index - 1;
                        fresh = false;
                        return;
                    }
                    if (handled == true)
                    break;
                }
                ++index;
            }
            while (index < graph->count);
        }
        fresh = true;
        stage = -1;
        bestScore = -3.4028235e38f;
        hasBest = false;
        Reset();
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: observer/target vector temporaries differ.
namespace HideRecovery {
    bool HideAgent::Test(const Candidate* candidate, const Vec3* offset, bool* seen)
   {
        Vec3 observer = gOrigin;
        Vec3 target;
        target.x = candidate->position.x + offset->x;
        target.y = candidate->position.y + offset->y;
        target.z = candidate->position.z + offset->z;
        *seen = false;
        ParameterTables* tables = (ParameterTables*)GetNameTables();
        bool result;
        if (tables->Consume(checkName, context->actor)) {
            bool visible = false;
            unsigned int i = 0;
            if (dangerousCount > 0) {
                do {
                    VectorProperty* property = (VectorProperty*)dangerous[i]->GetAuthoredProperty(&gKeyPosition);
                    if (property) {
                        Vec3 position;
                        position.x = property->value.x;
                        position.y = property->value.y;
                        position.z = property->value.z;
                        observer = position;
                    }
                    else {
                        observer = dangerous[i]->position;
                    }
                    visible = Kaim_CallHook(&observer, &target, dangerous[i], 1);
                }
                while (!visible && ++i < dangerousCount);
            }
            tables->Accumulate(checkName, context->actor);
            if (!visible) {
                *seen = true;
                return true;
            }
            return true;
        }
        else {
            result = false;
        }
        return result;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: controller-object lifetimes and distance-helper temporaries differ.
namespace HideRecovery {
    bool HideAgent::Evaluate(const Candidate* candidate, const Vec3* offset, float* score, bool* handled,
    bool* proceed)
   {
        *handled = false;
        *proceed = true;
        float total = 0;
        float spare = 0;
        bool seen;
        switch (mode) {
            case 1: {
                if (graphSlot != -1) {
                    VectorController from((const int*)candidate, graphSlot);
                    for (unsigned int i = 0; i < dangerousCount; ++i) {
                        void** node = (void**)nodes[i];
                        VectorController to((const int*)node, graphSlot, true);
                        float distance;
                        provider->Rate(&distance, &from, &to);
                        total = total + distance;
                    }
                }
                else {
                    unsigned int remaining = dangerousCount;
                    Actor** cursor = dangerous;
                    while (remaining != 0) {
                        Actor* actor = *cursor++;
                        --remaining;
                        float dx = actor->position.x - candidate->position.x;
                        float dy = actor->position.y - candidate->position.y;
                        float dz = actor->position.z - candidate->position.z;
                        total = total + sqrtf(dx * dx + dy * dy + dz * dz);
                    }
                }
                if (!(total > farLimit))
                return false;
                *proceed = Test(candidate, offset, &seen);
                if (!*proceed)
                return false;
                if (!seen)
                return false;
                farLimit = total;
                *score = total;
                return true;
            }
            case 2: {
                if (graphSlot != -1) {
                    VectorController from((const int*)candidate, graphSlot);
                    VectorController to((const int*)currentNode, graphSlot);
                    provider->Rate(&total, &from, &to);
                }
                else {
                    float dx = context->actor->position.x - candidate->position.x;
                    float dy = context->actor->position.y - candidate->position.y;
                    float dz = context->actor->position.z - candidate->position.z;
                    total = dx * dx + dy * dy + dz * dz;
                }
                if (!(total < nearLimit))
                return false;
                *proceed = Test(candidate, offset, &seen);
                if (!*proceed)
                return false;
                if (!seen)
                return false;
                nearLimit = total;
                *score = 1.0f / total;
                return true;
            }
        }
        return false;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: one redundant argument reload differs.
namespace HideRecovery {
    bool HideAgent::Consider(const Candidate* candidate, const Vec3* offset, bool* handled)
   {
        if (candidate->id != currentId) {
            *handled = false;
            bool proceed = true;
            float score;
            bool usable = Evaluate(candidate, offset, &score, handled, &proceed);
            if (!proceed)
            return false;
            if (usable) {
                if (score > bestScore || !hasBest) {
                    destination = candidate->position;
                    currentId = candidate->id;
                    rank = graphSlot;
                    found = true;
                    hasBest = true;
                }
            }
        }
        return true;
    }
}
#endif

#ifdef NONMATCHING
// Unmatched: owned constants require four-byte placement, but SN emits eight-byte section alignment.
extern const float D_00404454;
namespace HideRecovery {
    void HideAgent::Reset() {
        farLimit = 0.0f;
        nearLimit = D_00404454;
    }
}
#endif
