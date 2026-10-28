#include "include_asm.h"
#include "ps2/prelude.h"

typedef struct Recovered_RecordLink {
    struct Recovered_RecordLink* next;
    struct Recovered_RecordLink* previous;
} Recovered_RecordLink;

// Partial views of the observed list and query fields. Original class names,
// complete extents, untouched storage and meanings inferred only from drafts are UNVERIFIED.
typedef struct Recovered_Record {
    s128 value;
    struct Recovered_Record* owner;
    Recovered_RecordLink primary;
    Recovered_RecordLink pending;
    s32 child_count;
    Recovered_RecordLink children;
    f32 squared_distance;
    void* payload;
    s32 unknown38;
    s32 unknown3C;
} Recovered_Record;

typedef s32 (*Recovered_RecordCallback)(Recovered_Record*, s32, void*);
typedef struct Recovered_RecordManager {
    Recovered_RecordLink roots;
    Recovered_RecordLink active;
    Recovered_RecordLink pending;
    Recovered_RecordLink available;
    f32 margin;
    f32 thresholds[4];
    s32 group_size;
    s32 unknown38;
    s32 available_count;
    u32 unknown40;
    u8 querying;
    u8 unknown45[3];
    const s128* query_value;
    void* query_shape;
    void* query_volume;
    u32 unknown54;
    Recovered_RecordCallback callback;
    u32 unknown5C;
    u32 unknown60;
    void* context;
} Recovered_RecordManager;

void func_002734B8(Recovered_RecordManager*, Recovered_Record*);
void func_00273340(Recovered_RecordManager*, Recovered_Record*);
void func_002733E0(Recovered_RecordManager*, Recovered_Record*);

typedef char RecoveredRecordPrefixSize[sizeof(Recovered_Record) == 0x40 ? 1 : -1];
typedef char RecoveredRecordPrimaryOffset[(u32) & ((Recovered_Record*)0)->primary == 0x14 ? 1 : -1];
typedef char RecoveredRecordPendingOffset[(u32) & ((Recovered_Record*)0)->pending == 0x1C ? 1 : -1];
typedef char RecoveredManagerCountOffset[(u32) & ((Recovered_RecordManager*)0)->available_count == 0x3C ? 1 : -1];
typedef char RecoveredManagerCallbackOffset[(u32) & ((Recovered_RecordManager*)0)->callback == 0x58 ? 1 : -1];
typedef char RecoveredManagerContextOffset[(u32) & ((Recovered_RecordManager*)0)->context == 0x64 ? 1 : -1];

typedef struct Recovered_PoolNode {
    struct Recovered_PoolNode* next;
    struct Recovered_PoolNode* previous;
} Recovered_PoolNode;

typedef struct Recovered_FixedPool {
    Recovered_PoolNode* storage;
    u32 stride;
    u32 capacity;
    u32 alignment;
    Recovered_PoolNode* free;
} Recovered_FixedPool;

typedef struct Recovered_PoolList {
    Recovered_FixedPool* pool;
    Recovered_PoolNode* used;
} Recovered_PoolList;

extern s32 func_0027EFE8(s128, s128);
extern s32 func_0026F190(void*, s128);
extern s32 func_0026F0B0(s128, void*);
void func_00273960(Recovered_RecordManager*, Recovered_Record*, s32);

extern s32 D_003BFB40;
extern s32 D_0040EB74;
extern s32 D_0040EB78;
extern s32 D_003BFB3C;

void func_00272C18(s32 arg0, s32 arg1, f32 fparg0)
{
  unsigned int new_var;
 new_var = arg1 * 4; dummy_label_840098: ;
  *((f32 *) (((s8 *) (arg0 + new_var)) + (0x24 & 0xFFFFFFFFu))) = fparg0;
}

#include "ps2/recovered_types.h"
extern s32 func_002732E0(void *, void *);

s32 func_00272C28(void *arg0, void *arg1, s128 arg2, s32 *arg3) {
    M2C_FIELD(arg1, s128 *, 0) = (s128) arg2;
    M2C_FIELD(arg1, s32 **, 0x34) = arg3;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0x24) = 0;
    return func_002732E0(arg0, arg1);
}

void func_00272C58(Recovered_RecordManager* manager, Recovered_Record* record) {
    if (record->owner) {
        func_002734B8(manager, record);
        record->pending.next = 0;
    } else {
        record->primary.previous->next = record->primary.next;
        record->primary.next->previous = record->primary.previous;
        record->pending.next = 0;
    }
    record->primary.previous = 0;
    record->primary.next = 0;
    record->pending.previous = 0;
    record->owner = 0;
}

#ifdef NON_MATCHING
extern void func_00272DE8(Recovered_RecordManager*, Recovered_Record*, Recovered_RecordLink*, Recovered_Record*, s32);
extern void func_002730A0(Recovered_RecordManager*, Recovered_Record*);

static inline u8 RecordRadiusLess(f32 a, f32 b) {
    s32 result = 1;
    if (!(a < b)) result = 0;
    return result;
}

static inline f32 RecordRadius(s128 value) { return M2C_FIELD(&value, f32*, 12); }

// Unmatched: narrow comparison lowering and queued-link zero-store scheduling differ (9 instructions).
void func_00272CC0(Recovered_RecordManager* manager) {
    Recovered_RecordLink* link = manager->active.previous;
    while (link != &manager->active) {
        Recovered_Record* record = (Recovered_Record*)((s8*)link - 0x14);
        Recovered_RecordLink* current = link;
        link = link->previous;
        if (RecordRadiusLess(RecordRadius(record->value), manager->thresholds[manager->group_size - 1])) {
            if (manager->available_count < manager->group_size) break;
            current->previous->next = current->next;
            current->next->previous = current->previous;
            func_00272DE8(manager, 0, &manager->roots, record, 1);
        }
    }
    link = manager->pending.previous;
    while (link != &manager->pending) {
        Recovered_RecordLink* queued = link;
        func_002730A0(manager, (Recovered_Record*)((s8*)queued - 0x1C));
        queued->previous->next = queued->next;
        queued->next->previous = queued->previous;
        queued->next = 0;
        queued->previous = 0;
        link = manager->pending.previous;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00272CC0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00272DE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_002730A0);
s32 func_002732E0(void* arg0, void* arg1) {
    Recovered_RecordManager* manager = arg0;
    Recovered_Record* record = arg1;
    Recovered_RecordLink* first;
    Recovered_RecordLink* inserted;
    Recovered_RecordLink* former;
    if (record->owner) func_002734B8(manager, record);
    first = manager->active.next;
    record->primary.previous = &manager->active;
    inserted = &record->primary;
    record->primary.next = first;
    former = manager->active.next;
    former->previous = inserted;
    manager->active.next = inserted;
    return (s32)former;
}

void func_00273340(Recovered_RecordManager* manager, Recovered_Record* record) {
    if (!record->pending.next) {
        Recovered_RecordLink* first = manager->pending.next;
        record->pending.previous = &manager->pending;
        record->pending.next = first;
        manager->pending.next->previous = &record->pending;
        manager->pending.next = &record->pending;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00273378);
void func_002733E0(Recovered_RecordManager* manager, Recovered_Record* record) {
    Recovered_RecordLink* first;
    if (record->pending.next) {
        record->pending.previous->next = record->pending.next;
        record->pending.next->previous = record->pending.previous;
    }
    first = manager->available.next;
    record->primary.previous = &manager->available;
    record->primary.next = first;
    manager->available.next->previous = &record->primary;
    manager->available.next = &record->primary;
    manager->available_count++;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00273430);
void func_002734B8(Recovered_RecordManager* manager, Recovered_Record* record) {
    Recovered_Record* owner = record->owner;
    record->primary.previous->next = record->primary.next;
    record->primary.next->previous = record->primary.previous;
    owner->child_count--;
    record->owner = 0;
    if (owner->child_count == 0) {
        if (owner->owner) {
            func_002734B8(manager, owner);
        } else {
            owner->primary.previous->next = owner->primary.next;
            owner->primary.next->previous = owner->primary.previous;
        }
        func_002733E0(manager, owner);
    } else {
        func_00273340(manager, owner);
    }
}

#ifdef NON_MATCHING
// Unmatched: callback A0/A1 argument moves are reversed (2 instructions).
s32 func_00273568(Recovered_RecordManager* manager, s128 query, Recovered_RecordCallback callback, void* context) {
    s32 result = 1;
    Recovered_RecordLink* link;
    manager->querying = 1;
    manager->query_value = &query;
    manager->callback = callback;
    manager->context = context;
    for (link = manager->roots.next; link != &manager->roots; link = link->next) {
        result = func_00273648(manager, (Recovered_Record*)((s8*)link - 0x14), 1);
        if (!result) goto done;
    }
    for (link = manager->active.next; link != &manager->active; link = link->next) {
        Recovered_Record* record = (Recovered_Record*)((s8*)link - 0x14);
        result = func_0027EFE8(record->value, query);
        if (result) {
            result = callback(record, result, context);
            if (!result) break;
        }
    }
done:
    manager->querying = 0;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00273568);
#endif
s32 func_00273648(Recovered_RecordManager* manager, Recovered_Record* record, s32 classification) {
    Recovered_RecordLink* link;
    if (classification == 1) {
        classification = func_0027EFE8(record->value, *manager->query_value);
        if (!classification) return 1;
    }
    if (!record->child_count) return manager->callback(record, classification, manager->context);
    link = record->children.next;
    while (link != &record->children) {
        Recovered_Record* child = (Recovered_Record*)((s8*)link - 0x14);
        link = link->next;
        if (!func_00273648(manager, child, classification)) return 0;
    }
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: manager and callback-record register allocation differs (18 instructions).
void func_00273708(Recovered_RecordManager* manager, void* shape, Recovered_RecordCallback callback, void* context) {
    Recovered_RecordLink* link;
    manager->querying = 1;
    manager->query_shape = shape;
    manager->callback = callback;
    manager->context = context;
    for (link = manager->roots.next; link != &manager->roots; link = link->next) {
        if (!func_002737E8(manager, (Recovered_Record*)((s8*)link - 0x14))) goto done;
    }
    for (link = manager->active.next; link != &manager->active; link = link->next) {
        Recovered_Record* record = (Recovered_Record*)((s8*)link - 0x14);
        s32 classification = func_0026F190(shape, record->value);
        if (classification && !callback(record, classification, context)) break;
    }
done:
    manager->querying = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00273708);
#endif
s32 func_002737E8(Recovered_RecordManager* manager, Recovered_Record* record) {
    Recovered_RecordLink* link;
    s32 classification = func_0026F190(manager->query_shape, record->value);
    if (!classification) return 1;
    if (!record->child_count) return manager->callback(record, classification, manager->context);
    link = record->children.next;
    while (link != &record->children) {
        Recovered_Record* child = (Recovered_Record*)((s8*)link - 0x14);
        link = link->next;
        if (!func_002737E8(manager, child)) return 0;
    }
    return 1;
}

void func_00273888(Recovered_RecordManager* manager, void* plane, Recovered_RecordCallback callback, void* context) {
    Recovered_RecordLink* link;
    manager->querying = 1;
    manager->query_volume = plane;
    manager->callback = callback;
    manager->context = context;
    for (link = manager->roots.next; link != &manager->roots; link = link->next) {
        func_00273960(manager, (Recovered_Record*)((s8*)link - 0x14), 1);
    }
    for (link = manager->active.next; link != &manager->active; link = link->next) {
        Recovered_Record* record = (Recovered_Record*)((s8*)link - 0x14);
        s32 classification = func_0026F0B0(record->value, manager->query_volume);
        if (classification) callback(record, classification, context);
    }
    manager->querying = 0;
}

void func_00273960(Recovered_RecordManager* manager, Recovered_Record* record, s32 classification) {
    Recovered_RecordLink* link;
    if (classification == 1) {
        classification = func_0026F0B0(record->value, manager->query_volume);
        if (!classification) return;
    }
    if (!record->child_count) {
        manager->callback(record, classification, manager->context);
    } else {
        link = record->children.next;
        while (link != &record->children) {
            Recovered_Record* child = (Recovered_Record*)((s8*)link - 0x14);
            link = link->next;
            func_00273960(manager, child, classification);
        }
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00273A18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00273CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00273F28);
#ifdef NON_MATCHING
// Unmatched: construction/copy cursor allocation and zero-store scheduling differ (22 instructions).
void func_00273F30(Recovered_FixedPool* pool, u32 count, u32 size, u32 alignment, const u8* initial, void* storage) {
    u32 i;
    u32 stride;
    Recovered_PoolNode* node;
    Recovered_PoolNode* first;
    if (!alignment)
        pool->alignment = 1;
    else
        pool->alignment = alignment;
    if (!count) {
        pool->stride = size;
        pool->free = 0;
        pool->storage = 0;
        pool->capacity = 0;
        return;
    }
    i = 1;
    first = (Recovered_PoolNode*)(((pool->alignment + (u32)storage + 7) & -pool->alignment) - 8);
    stride = (size + pool->alignment + 7) & -pool->alignment;
    pool->storage = first;
    pool->free = first;
    node = first;
    node->previous = 0;
    for (; i < count; i++) {
        Recovered_PoolNode* previous = node;
        node = (Recovered_PoolNode*)((u8*)previous + stride);
        previous->next = node;
        node->previous = previous;
    }
    node->next = 0;
    if (initial) {
        Recovered_PoolNode* template_node = pool->free;
        do {
            u32 remaining = size;
            const u8* source = initial;
            u8* destination = (u8*)template_node + 8;
            while (remaining) {
                *destination++ = *source++;
                remaining--;
            }
            template_node = template_node->next;
        } while (template_node);
    }
    pool->stride = stride;
    pool->capacity = count;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00273F30);
#endif

s32 func_00274018(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_2;

    var_2 = arg1 + 8;
    if (arg2 != 0) {
        var_2 = ((var_2 + arg2) - 1) & -arg2;
    }
    return (var_2 * arg0) + arg2;
}

void func_00274040(Recovered_FixedPool* pool) {
    Recovered_PoolNode* node;
    Recovered_PoolNode* previous;
    u32 remaining;
    if (!pool->storage || !pool->free) return;
    remaining = 0;
    for (node = pool->free; node; node = node->next) {
        node->previous = (Recovered_PoolNode*)1;
        remaining++;
    }
    previous = 0;
    node = pool->storage;
    for (;;) {
        if (node->previous == (Recovered_PoolNode*)1) {
            if (!previous) {
                pool->free = node;
                node->previous = 0;
            } else {
                previous->next = node;
                node->previous = previous;
            }
            remaining--;
            previous = node;
            if (!remaining) {
                node->next = 0;
                return;
            }
        }
        node = (Recovered_PoolNode*)((u8*)node + pool->stride);
    }
}

void func_002740D8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

s32 func_002740E8(s32 arg0, s32 arg1) {
    M2C_UNK *temp_2;
    M2C_UNK *temp_2_2;
    M2C_UNK *temp_3;
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0);
    temp_3 = M2C_FIELD(temp_5, M2C_UNK **, 0x10);
    if (temp_3 == NULL) {
        goto block_2;
    }
    goto block_4;
block_2:
    return 0;
block_4:
    M2C_FIELD(temp_5, M2C_UNK **, 0x10) = (M2C_UNK *) *temp_3;
    temp_2 = *temp_3;
    if (temp_2 == NULL) {
        goto block_6;
    }
    M2C_FIELD(temp_2, s32 *, 4) = 0;
block_6:
    temp_2_2 = M2C_FIELD(arg0, M2C_UNK **, 4);
    if (temp_2_2 == NULL) {
        goto block_8;
    }
    *temp_3 = temp_2_2;
    goto block_10;
block_8:
    *temp_3 = NULL;
    goto block_11;
block_10:
    M2C_FIELD(temp_2_2, M2C_UNK **, 4) = temp_3;
block_11:
    M2C_FIELD(arg0, M2C_UNK **, 4) = temp_3;
    return (s32) temp_3;
}

void func_00274138(Recovered_PoolList* list, Recovered_PoolNode* node) {
    if (node->next) node->next->previous = node->previous;
    if (node->previous) {
        node->previous->next = node->next;
        node->previous = 0;
    } else {
        if (node->next)
            list->used = node->next;
        else
            list->used = 0;
    }
    node->next = list->pool->free;
    if (node->next) node->next->previous = node;
    list->pool->free = node;
}

void func_00274190(Recovered_PoolList* list) {
    Recovered_PoolNode* head = list->used;
    if (head) {
        Recovered_PoolNode* tail = head;
        while (tail->next) tail = tail->next;
        tail->next = list->pool->free;
        if (tail->next) tail->next->previous = tail;
        list->pool->free = head;
        list->used = 0;
    }
}

void func_002741F0(s32 arg0, s32 arg1, s32 arg2) {
    D_003BFB40 = arg0;
    if (arg0 > 0) {
        D_0040EB74 = arg1;
        D_0040EB78 = arg2;
        return;
    }
    D_0040EB74 = 0;
    D_0040EB78 = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00274228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00274270);

void func_00274350(s32 arg0) {
    D_003BFB3C = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00274360);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_002743D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00274540);

void func_00274920(void) {

}

extern u8 D_00492A50[];
extern void func_00275260(const char*, u16*, s32);
extern void func_00275DC0(s32, f32, f32, f32, const u16*, s128);
extern f32 func_00274AA8(void*, f32, f32, const char*);

void func_00274928(const char* text, s128 color, s32 unicode, f32 x, f32 y, f32 scale) {
    u16 buffer[128];
    if (unicode) {
        func_00275260(text, buffer, 128);
        func_00275DC0(D_003BFB3C, x, y, scale, buffer, color);
    } else {
        func_00274AA8(D_00492A50, x, y, text);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_002749C0);
#ifdef NON_MATCHING

typedef struct Recovered_FontColor {
    u8 rgba[4];
} Recovered_FontColor;

typedef struct Recovered_FontVertex {
    f32 x, y, z, unknown0C;
    s32 u, v;
    f32 reciprocal;
    u32 unknown1C;
    f32 rgba[4];
    u8 unknown30[0x10];
} Recovered_FontVertex;

typedef struct Recovered_FontState {
    f32 scale_x, scale_y;
    Recovered_FontColor color;
    f32 reciprocal;
    Recovered_FontVertex vertices[500];
} Recovered_FontState;

extern f32 D_00449438[];

// Unmatched: scalar initialization scheduling and vertex-loop allocation differ (32 instructions).
s32 func_002749C8(Recovered_FontState* font, void* texture, const Recovered_FontColor* color, const f32* scale) {
    u32 i;
    Recovered_FontVertex* vertex;
    font->scale_x = scale[0] * (1.0f / 192.0f);
    font->scale_y = scale[1] * (1.0f / 192.0f);
    font->color = *color;
    i = 0;
    vertex = font->vertices;
    font->reciprocal = 1.0f / M2C_FIELD(texture, f32*, 0x80);
    do {
        vertex->z = D_00449438[6];
        vertex->u = 0;
        vertex->reciprocal = font->reciprocal;
        vertex->v = 0;
        vertex->rgba[0] = font->color.rgba[0];
        vertex->rgba[1] = font->color.rgba[1];
        vertex->rgba[2] = font->color.rgba[2];
        vertex->rgba[3] = font->color.rgba[3];
        i++;
        vertex++;
    } while (i < 500);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_002749C8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488_272c18", func_00274AA8);
extern u32 D_004406E8[];
extern const u8* D_00440AE8[];
extern u8 D_003BFB60[][0x40], D_003C00E0[][0x40], D_003BFF20[][0x40], D_003C0360[][0x40];

void func_00274CD8(u32 index, const u8* entries) {
    u32* count = &D_004406E8[index];
    D_00440AE8[index] = entries;
    *count = 0;
    while (entries[0] | entries[1] | entries[2] | entries[3]) {
        entries += 4;
        (*count)++;
    }
}

s32 func_00274D40(void) {
    u32 i;
    for (i = 0; i < 256; i++) D_004406E8[i] = 0;
    for (i = 0; i < 15; i++) func_00274CD8(i + 0x21, D_003BFB60[i]);
    for (i = 0; i < 10; i++) func_00274CD8(i + 0x30, D_003C00E0[i]);
    for (i = 0; i < 7; i++) func_00274CD8(i + 0x3A, D_003BFF20[i]);
    for (i = 0; i < 26; i++) {
        func_00274CD8(i + 0x61, D_003C0360[i]);
        func_00274CD8(i + 0x41, D_003C0360[i]);
    }
    return 1;
}
