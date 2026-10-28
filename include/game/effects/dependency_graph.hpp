#ifndef BLACK_GAME_EFFECT_DEPENDENCY_GRAPH_HPP
#define BLACK_GAME_EFFECT_DEPENDENCY_GRAPH_HPP

// Partial parameter and graph access views; original class identities are UNVERIFIED.
struct EffectParameter {
    unsigned offset;
    char unknown04[16];
};
struct EffectInstance;
struct EffectObjectVtable {
    char unknown00[0xa0];
    short enabledAdjust;
    unsigned short unknowna2;
    int (*enabled)(void*, EffectInstance*);
};
struct EffectBinding {
    unsigned unknown00[2];
    EffectInstance* item;
    void* other;
};
struct EffectObject {
    EffectObjectVtable* vtable;
    char unknown04[0x5c];
    EffectBinding* bindings;
    int bindingCount;
};

struct EffectDefinition;
struct EffectInstance {
    unsigned index;
    EffectDefinition* definition;
};
struct EffectDefinition {
    char unknown00[24];
    EffectParameter* parameters;
    char unknown1c[28];
    unsigned *sourceIndices, *targetIndices;
    char unknown40[16];
    EffectObject** objects;
    char unknown54[8];
    EffectInstance embedded;
    EffectParameter sourceDefault, targetDefault;
    char unknown8c[8];
    EffectObject* defaultObject;
};
struct PendingEffects {
    unsigned entries[64];
    unsigned readIndex;
    unsigned writeIndex;
    inline void Reset() {
        writeIndex = -1;
        readIndex = 0;
    }
};
struct EffectHistory {
    EffectInstance* entries[32];
    unsigned readIndex;
    unsigned writeIndex;
    inline void Reset() {
        writeIndex = -1;
        readIndex = 0;
    }
};
struct EffectGraphRows {
    unsigned long rows[64];
};
struct EffectGraph {
    void* context;
    unsigned char* values;
    unsigned long* rows;
    void* other;
    EffectGraphRows cache;
    char unknown210[0x1388];
    unsigned char* cursor;
    PendingEffects pending;
    EffectHistory history;
    unsigned unknown172c;
};
extern "C" int func_00388F48(void*, EffectInstance*);
static inline EffectObject* Object(EffectInstance* item) {
    if (item == &item->definition->embedded) return item->definition->defaultObject;
    if (!item->definition->objects) return 0;
    return item->definition->objects[item->index];
}
static inline int Enabled(EffectObject* object, EffectInstance* item) {
    if (!object->vtable->enabled((char*)object + object->vtable->enabledAdjust, item)) return 0;
    for (int i = object->bindingCount; --i >= 0;) {
        EffectBinding* binding = &object->bindings[i];
        if (binding->item == item) {
            if (binding->other) return func_00388F48(binding->other, item);
            return 1;
        }
    }
    return 1;
}

#endif
