/* Recovered PS2 data types, shared by the translation units and by the m2c context (build/auto/ctx.c).
 *
 * Hand-maintained. The layouts are recovered guesses: a structure is UNVERIFIED unless its mark says a matched function
 * accesses members through it. Offsets and sizes are asserted at the end. Names are working names, not the original's.
 * Signatures that use these types are in ps2/prototypes.h. */
#ifndef PS2_RECOVERED_TYPES_H
#define PS2_RECOVERED_TYPES_H
#include "ps2/prelude.h"

typedef struct PS2AnimationExpression PS2AnimationExpression;
typedef struct PS2CollisionQueue PS2CollisionQueue;
typedef struct PS2GameObjectManager PS2GameObjectManager;
typedef struct PS2GameObjectRecord PS2GameObjectRecord;
typedef struct PS2KaimBufferSet PS2KaimBufferSet;
typedef struct PS2KaimChildBuffer PS2KaimChildBuffer;
typedef struct PS2KaimClassDescriptor PS2KaimClassDescriptor;
typedef struct PS2KaimClassRegistry PS2KaimClassRegistry;
typedef struct PS2KaimIndexTable PS2KaimIndexTable;
typedef struct PS2KaimParameterTables PS2KaimParameterTables;
typedef struct PS2LiveCollision PS2LiveCollision;
typedef struct PS2PendingCollision PS2PendingCollision;
typedef struct RecoveredAIActionEvent RecoveredAIActionEvent;
typedef struct RecoveredAIActionHeader RecoveredAIActionHeader;
typedef struct RecoveredAIActionPolicy RecoveredAIActionPolicy;
typedef struct RecoveredAIActionStack RecoveredAIActionStack;
typedef struct RecoveredAICompletionRecord RecoveredAICompletionRecord;
typedef struct RecoveredAIController RecoveredAIController;
typedef struct RecoveredAIQueuedActionEvent RecoveredAIQueuedActionEvent;
typedef struct RecoveredNodeGraph RecoveredNodeGraph;
typedef struct RecoveredNodeSearch RecoveredNodeSearch;
typedef struct RecoveredRouteNode RecoveredRouteNode;
typedef struct RecoveredRouteRequest RecoveredRouteRequest;
typedef struct RecoveredRouteStorage RecoveredRouteStorage;

/* PS2AnimationExpression, 12 bytes: UNVERIFIED */
struct PS2AnimationExpression {
    u8 kind; /* 0x0 */
    char childCount; /* 0x1 */
    s16 event; /* 0x2 */
    f32 value; /* 0x4 */
    PS2AnimationExpression **children; /* 0x8 */
};

/* PS2PendingCollision, 12 bytes: UNVERIFIED */
struct PS2PendingCollision {
    u8 active; /* 0x0 */
    u8 flag; /* 0x1 */
    u8 unknown02[2]; /* 0x2 */
    PS2GameObjectRecord *object; /* 0x4 */
    f32 stamp; /* 0x8 */
};

/* PS2CollisionQueue, 640 bytes: UNVERIFIED */
struct PS2CollisionQueue {
    PS2LiveCollision *live[16]; /* 0x0 */
    PS2PendingCollision pending[48]; /* 0x40 */
};

/* PS2GameObjectManager, 23720 bytes: UNVERIFIED */
struct PS2GameObjectManager {
    u8 unknown00[32]; /* 0x0 */
    f32 stamp; /* 0x20 */
    u8 unknown24[23680]; /* 0x24 */
    PS2GameObjectRecord *first; /* 0x5CA4 */
};

/* PS2GameObjectRecord, 200 bytes: UNVERIFIED */
struct PS2GameObjectRecord {
    u64 name; /* 0x0 */
    u8 unknown08[168]; /* 0x8 */
    PS2GameObjectRecord *next; /* 0xB0 */
    u8 unknownb4[16]; /* 0xB4 */
    s32 type; /* 0xC4 */
};

/* PS2KaimBufferSet, 24 bytes: UNVERIFIED */
struct PS2KaimBufferSet {
    void **vtable; /* 0x0 */
    f32 *sums; /* 0x4 */
    f32 total; /* 0x8 */
    f32 weight; /* 0xC */
    f32 *values; /* 0x10 */
    f32 *ranks; /* 0x14 */
};

/* PS2KaimChildBuffer, 36 bytes: UNVERIFIED */
struct PS2KaimChildBuffer {
    void **vtable; /* 0x0 */
    s32 unknown04; /* 0x4 */
    s32 unknown08; /* 0x8 */
    char *first; /* 0xC */
    char *name; /* 0x10 */
    char *value; /* 0x14 */
    PS2KaimChildBuffer **children; /* 0x18 */
    u32 capacity; /* 0x1C */
    u32 count; /* 0x20 */
};

/* PS2KaimClassDescriptor, 276 bytes: UNVERIFIED */
struct PS2KaimClassDescriptor {
    s32 index; /* 0x0 */
    void *factory; /* 0x4 */
    char name[256]; /* 0x8 */
    PS2KaimClassDescriptor *parent; /* 0x108 */
    u32 usageMask; /* 0x10C */
    void *vtable; /* 0x110 */
};

/* PS2KaimClassRegistry, 1028 bytes: UNVERIFIED */
struct PS2KaimClassRegistry {
    PS2KaimClassDescriptor *slots[256]; /* 0x0 */
    s32 count; /* 0x400 */
};

/* PS2KaimIndexTable, 12 bytes: UNVERIFIED */
struct PS2KaimIndexTable {
    void **vtable; /* 0x0 */
    u32 *indices; /* 0x4 */
    f32 *values; /* 0x8 */
};

/* PS2KaimParameterTables, 84 bytes: UNVERIFIED */
struct PS2KaimParameterTables {
    void **vtable; /* 0x0 */
    u32 countPeriodic; /* 0x4 */
    u32 countAperiodic; /* 0x8 */
    u32 countEstimated; /* 0xC */
    char **namesPeriodic; /* 0x10 */
    char **namesAperiodic; /* 0x14 */
    char **namesEstimated; /* 0x18 */
    f32 threshold; /* 0x1C */
    f32 *maxTime; /* 0x20 */
    s32 *maxCalls; /* 0x24 */
    f32 *weights; /* 0x28 */
    f32 *period; /* 0x2C */
    f32 *estimates; /* 0x30 */
    PS2KaimBufferSet *sets; /* 0x34 */
    PS2KaimIndexTable *indexTables; /* 0x38 */
    f32 *lastTime; /* 0x3C */
    f32 *accumulated; /* 0x40 */
    s32 *calls; /* 0x44 */
    s32 *order; /* 0x48 */
    s32 selected; /* 0x4C */
    u8 fired; /* 0x50 */
    u8 unknown51[3]; /* 0x51 */
};

/* PS2LiveCollision, 128 bytes: UNVERIFIED */
struct PS2LiveCollision {
    u8 unknown00[112]; /* 0x0 */
    PS2GameObjectRecord *object; /* 0x70 */
    u8 unknown74[8]; /* 0x74 */
    s32 state; /* 0x7C */
};

/* RecoveredAIActionEvent, 24 bytes: UNVERIFIED */
struct RecoveredAIActionEvent {
    u32 kind; /* 0x0 */
    u32 payload[5]; /* 0x4 */
};

/* RecoveredAIActionHeader, 40 bytes: used by 8 matching functions */
struct RecoveredAIActionHeader {
    void *brain; /* 0x0 */
    void *vtable; /* 0x4 */
    u32 phase; /* 0x8 */
    u8 unknown0c[24]; /* 0xC */
    u32 payload; /* 0x24 */
};

/* RecoveredAIActionPolicy, 136 bytes: UNVERIFIED */
struct RecoveredAIActionPolicy {
    u32 words[34]; /* 0x0 */
};

/* RecoveredAICompletionRecord, 148 bytes: UNVERIFIED */
struct RecoveredAICompletionRecord {
    f32 interval; /* 0x0 */
    f32 deadline; /* 0x4 */
    u8 complete; /* 0x8 */
    u8 result; /* 0x9 */
    u8 unknown0a[2]; /* 0xA */
    RecoveredAIActionPolicy policy; /* 0xC */
};

/* RecoveredAIQueuedActionEvent, 28 bytes: UNVERIFIED */
struct RecoveredAIQueuedActionEvent {
    u32 kind; /* 0x0 */
    RecoveredAIActionEvent event; /* 0x4 */
};

/* RecoveredAIActionStack, 2112 bytes: UNVERIFIED */
struct RecoveredAIActionStack {
    u32 kinds[8]; /* 0x0 */
    RecoveredAICompletionRecord records[8]; /* 0x20 */
    s32 count; /* 0x4C0 */
    RecoveredAIQueuedActionEvent events[21]; /* 0x4C4 */
    s32 eventCount; /* 0x710 */
    void *owner; /* 0x714 */
    RecoveredAIActionHeader *actions[74]; /* 0x718 */
};

/* RecoveredAIController, 84 bytes: UNVERIFIED */
struct RecoveredAIController {
    u8 unknown00[48]; /* 0x0 */
    u32 state; /* 0x30 */
    u8 update; /* 0x34 */
    u8 routeFlag; /* 0x35 */
    u8 unknown36[3]; /* 0x36 */
    u8 routePending; /* 0x39 */
    u8 unknown3a[6]; /* 0x3A */
    u32 active; /* 0x40 */
    void *modes[4]; /* 0x44 */
};

/* RecoveredNodeGraph, 92 bytes: UNVERIFIED */
struct RecoveredNodeGraph {
    u8 pad00[12]; /* 0x0 */
    u32 nodeCount; /* 0xC */
    u8 pad10[8]; /* 0x10 */
    RecoveredRouteNode *nodes; /* 0x18 */
    u8 pad1c[56]; /* 0x1C */
    u32 heuristic; /* 0x54 */
    u32 cost; /* 0x58 */
};

/* RecoveredNodeSearch, 304 bytes: UNVERIFIED */
struct RecoveredNodeSearch {
    RecoveredRouteNode *result; /* 0x0 */
    u8 pad04[12]; /* 0x4 */
    f32 origin[4]; /* 0x10 */
    s32 cursor; /* 0x20 */
    u32 candidates[64]; /* 0x24 */
    s32 candidateCount; /* 0x124 */
    u8 active; /* 0x128 */
    u8 pad129[7]; /* 0x129 */
};

/* RecoveredRouteNode, 20 bytes: UNVERIFIED */
struct RecoveredRouteNode {
    u32 id; /* 0x0 */
    f32 position[3]; /* 0x4 */
    s32 graph; /* 0x10 */
};

/* RecoveredRouteRequest, 112 bytes: UNVERIFIED */
struct RecoveredRouteRequest {
    void *owner; /* 0x0 */
    void *next; /* 0x4 */
    s32 kind; /* 0x8 */
    s32 result; /* 0xC */
    f32 origin[4]; /* 0x10 */
    f32 destination[4]; /* 0x20 */
    RecoveredRouteNode *startNode; /* 0x30 */
    RecoveredRouteNode *endNode; /* 0x34 */
    f32 originLifted[3]; /* 0x38 */
    f32 destinationLifted[3]; /* 0x44 */
    RecoveredRouteStorage *storage; /* 0x50 */
    s32 firstPoint; /* 0x54 */
    u8 busy; /* 0x58 */
    u8 pad59[3]; /* 0x59 */
    f32 elapsed; /* 0x5C */
    u8 reuse; /* 0x60 */
    u8 pad61[15]; /* 0x61 */
};

/* RecoveredRouteStorage, 40 bytes: UNVERIFIED */
struct RecoveredRouteStorage {
    u8 pad00[4]; /* 0x0 */
    RecoveredNodeGraph *graph; /* 0x4 */
    s32 count; /* 0x8 */
    u32 *nodeIds; /* 0xC */
    u32 *links; /* 0x10 */
    f32 *points; /* 0x14 */
    s32 *edgeData; /* 0x18 */
    s32 field1c; /* 0x1C */
    u8 field20; /* 0x20 */
    u8 pad21[3]; /* 0x21 */
    f32 field24; /* 0x24 */
};

/* Compile-time checks of the recovered layouts. */
typedef char assert_PS2AnimationExpression_kind[(((int) &((PS2AnimationExpression *) 0)->kind) == 0) ? 1 : -1];
typedef char assert_PS2AnimationExpression_childCount[(((int) &((PS2AnimationExpression *) 0)->childCount) == 1) ? 1 : -1];
typedef char assert_PS2AnimationExpression_event[(((int) &((PS2AnimationExpression *) 0)->event) == 2) ? 1 : -1];
typedef char assert_PS2AnimationExpression_value[(((int) &((PS2AnimationExpression *) 0)->value) == 4) ? 1 : -1];
typedef char assert_PS2AnimationExpression_children[(((int) &((PS2AnimationExpression *) 0)->children) == 8) ? 1 : -1];
typedef char assert_PS2AnimationExpression_size[(sizeof(PS2AnimationExpression) == 12) ? 1 : -1];
typedef char assert_PS2PendingCollision_active[(((int) &((PS2PendingCollision *) 0)->active) == 0) ? 1 : -1];
typedef char assert_PS2PendingCollision_flag[(((int) &((PS2PendingCollision *) 0)->flag) == 1) ? 1 : -1];
typedef char assert_PS2PendingCollision_unknown02[(((int) &((PS2PendingCollision *) 0)->unknown02) == 2) ? 1 : -1];
typedef char assert_PS2PendingCollision_object[(((int) &((PS2PendingCollision *) 0)->object) == 4) ? 1 : -1];
typedef char assert_PS2PendingCollision_stamp[(((int) &((PS2PendingCollision *) 0)->stamp) == 8) ? 1 : -1];
typedef char assert_PS2PendingCollision_size[(sizeof(PS2PendingCollision) == 12) ? 1 : -1];
typedef char assert_PS2CollisionQueue_live[(((int) &((PS2CollisionQueue *) 0)->live) == 0) ? 1 : -1];
typedef char assert_PS2CollisionQueue_pending[(((int) &((PS2CollisionQueue *) 0)->pending) == 64) ? 1 : -1];
typedef char assert_PS2CollisionQueue_size[(sizeof(PS2CollisionQueue) == 640) ? 1 : -1];
typedef char assert_PS2GameObjectManager_unknown00[(((int) &((PS2GameObjectManager *) 0)->unknown00) == 0) ? 1 : -1];
typedef char assert_PS2GameObjectManager_stamp[(((int) &((PS2GameObjectManager *) 0)->stamp) == 32) ? 1 : -1];
typedef char assert_PS2GameObjectManager_unknown24[(((int) &((PS2GameObjectManager *) 0)->unknown24) == 36) ? 1 : -1];
typedef char assert_PS2GameObjectManager_first[(((int) &((PS2GameObjectManager *) 0)->first) == 23716) ? 1 : -1];
typedef char assert_PS2GameObjectManager_size[(sizeof(PS2GameObjectManager) == 23720) ? 1 : -1];
typedef char assert_PS2GameObjectRecord_name[(((int) &((PS2GameObjectRecord *) 0)->name) == 0) ? 1 : -1];
typedef char assert_PS2GameObjectRecord_unknown08[(((int) &((PS2GameObjectRecord *) 0)->unknown08) == 8) ? 1 : -1];
typedef char assert_PS2GameObjectRecord_next[(((int) &((PS2GameObjectRecord *) 0)->next) == 176) ? 1 : -1];
typedef char assert_PS2GameObjectRecord_unknownb4[(((int) &((PS2GameObjectRecord *) 0)->unknownb4) == 180) ? 1 : -1];
typedef char assert_PS2GameObjectRecord_type[(((int) &((PS2GameObjectRecord *) 0)->type) == 196) ? 1 : -1];
typedef char assert_PS2GameObjectRecord_size[(sizeof(PS2GameObjectRecord) == 200) ? 1 : -1];
typedef char assert_PS2KaimBufferSet_vtable[(((int) &((PS2KaimBufferSet *) 0)->vtable) == 0) ? 1 : -1];
typedef char assert_PS2KaimBufferSet_sums[(((int) &((PS2KaimBufferSet *) 0)->sums) == 4) ? 1 : -1];
typedef char assert_PS2KaimBufferSet_total[(((int) &((PS2KaimBufferSet *) 0)->total) == 8) ? 1 : -1];
typedef char assert_PS2KaimBufferSet_weight[(((int) &((PS2KaimBufferSet *) 0)->weight) == 12) ? 1 : -1];
typedef char assert_PS2KaimBufferSet_values[(((int) &((PS2KaimBufferSet *) 0)->values) == 16) ? 1 : -1];
typedef char assert_PS2KaimBufferSet_ranks[(((int) &((PS2KaimBufferSet *) 0)->ranks) == 20) ? 1 : -1];
typedef char assert_PS2KaimBufferSet_size[(sizeof(PS2KaimBufferSet) == 24) ? 1 : -1];
typedef char assert_PS2KaimChildBuffer_vtable[(((int) &((PS2KaimChildBuffer *) 0)->vtable) == 0) ? 1 : -1];
typedef char assert_PS2KaimChildBuffer_unknown04[(((int) &((PS2KaimChildBuffer *) 0)->unknown04) == 4) ? 1 : -1];
typedef char assert_PS2KaimChildBuffer_unknown08[(((int) &((PS2KaimChildBuffer *) 0)->unknown08) == 8) ? 1 : -1];
typedef char assert_PS2KaimChildBuffer_first[(((int) &((PS2KaimChildBuffer *) 0)->first) == 12) ? 1 : -1];
typedef char assert_PS2KaimChildBuffer_name[(((int) &((PS2KaimChildBuffer *) 0)->name) == 16) ? 1 : -1];
typedef char assert_PS2KaimChildBuffer_value[(((int) &((PS2KaimChildBuffer *) 0)->value) == 20) ? 1 : -1];
typedef char assert_PS2KaimChildBuffer_children[(((int) &((PS2KaimChildBuffer *) 0)->children) == 24) ? 1 : -1];
typedef char assert_PS2KaimChildBuffer_capacity[(((int) &((PS2KaimChildBuffer *) 0)->capacity) == 28) ? 1 : -1];
typedef char assert_PS2KaimChildBuffer_count[(((int) &((PS2KaimChildBuffer *) 0)->count) == 32) ? 1 : -1];
typedef char assert_PS2KaimChildBuffer_size[(sizeof(PS2KaimChildBuffer) == 36) ? 1 : -1];
typedef char assert_PS2KaimClassDescriptor_index[(((int) &((PS2KaimClassDescriptor *) 0)->index) == 0) ? 1 : -1];
typedef char assert_PS2KaimClassDescriptor_factory[(((int) &((PS2KaimClassDescriptor *) 0)->factory) == 4) ? 1 : -1];
typedef char assert_PS2KaimClassDescriptor_name[(((int) &((PS2KaimClassDescriptor *) 0)->name) == 8) ? 1 : -1];
typedef char assert_PS2KaimClassDescriptor_parent[(((int) &((PS2KaimClassDescriptor *) 0)->parent) == 264) ? 1 : -1];
typedef char assert_PS2KaimClassDescriptor_usageMask[(((int) &((PS2KaimClassDescriptor *) 0)->usageMask) == 268) ? 1 : -1];
typedef char assert_PS2KaimClassDescriptor_vtable[(((int) &((PS2KaimClassDescriptor *) 0)->vtable) == 272) ? 1 : -1];
typedef char assert_PS2KaimClassDescriptor_size[(sizeof(PS2KaimClassDescriptor) == 276) ? 1 : -1];
typedef char assert_PS2KaimClassRegistry_slots[(((int) &((PS2KaimClassRegistry *) 0)->slots) == 0) ? 1 : -1];
typedef char assert_PS2KaimClassRegistry_count[(((int) &((PS2KaimClassRegistry *) 0)->count) == 1024) ? 1 : -1];
typedef char assert_PS2KaimClassRegistry_size[(sizeof(PS2KaimClassRegistry) == 1028) ? 1 : -1];
typedef char assert_PS2KaimIndexTable_vtable[(((int) &((PS2KaimIndexTable *) 0)->vtable) == 0) ? 1 : -1];
typedef char assert_PS2KaimIndexTable_indices[(((int) &((PS2KaimIndexTable *) 0)->indices) == 4) ? 1 : -1];
typedef char assert_PS2KaimIndexTable_values[(((int) &((PS2KaimIndexTable *) 0)->values) == 8) ? 1 : -1];
typedef char assert_PS2KaimIndexTable_size[(sizeof(PS2KaimIndexTable) == 12) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_vtable[(((int) &((PS2KaimParameterTables *) 0)->vtable) == 0) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_countPeriodic[(((int) &((PS2KaimParameterTables *) 0)->countPeriodic) == 4) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_countAperiodic[(((int) &((PS2KaimParameterTables *) 0)->countAperiodic) == 8) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_countEstimated[(((int) &((PS2KaimParameterTables *) 0)->countEstimated) == 12) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_namesPeriodic[(((int) &((PS2KaimParameterTables *) 0)->namesPeriodic) == 16) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_namesAperiodic[(((int) &((PS2KaimParameterTables *) 0)->namesAperiodic) == 20) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_namesEstimated[(((int) &((PS2KaimParameterTables *) 0)->namesEstimated) == 24) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_threshold[(((int) &((PS2KaimParameterTables *) 0)->threshold) == 28) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_maxTime[(((int) &((PS2KaimParameterTables *) 0)->maxTime) == 32) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_maxCalls[(((int) &((PS2KaimParameterTables *) 0)->maxCalls) == 36) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_weights[(((int) &((PS2KaimParameterTables *) 0)->weights) == 40) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_period[(((int) &((PS2KaimParameterTables *) 0)->period) == 44) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_estimates[(((int) &((PS2KaimParameterTables *) 0)->estimates) == 48) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_sets[(((int) &((PS2KaimParameterTables *) 0)->sets) == 52) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_indexTables[(((int) &((PS2KaimParameterTables *) 0)->indexTables) == 56) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_lastTime[(((int) &((PS2KaimParameterTables *) 0)->lastTime) == 60) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_accumulated[(((int) &((PS2KaimParameterTables *) 0)->accumulated) == 64) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_calls[(((int) &((PS2KaimParameterTables *) 0)->calls) == 68) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_order[(((int) &((PS2KaimParameterTables *) 0)->order) == 72) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_selected[(((int) &((PS2KaimParameterTables *) 0)->selected) == 76) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_fired[(((int) &((PS2KaimParameterTables *) 0)->fired) == 80) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_unknown51[(((int) &((PS2KaimParameterTables *) 0)->unknown51) == 81) ? 1 : -1];
typedef char assert_PS2KaimParameterTables_size[(sizeof(PS2KaimParameterTables) == 84) ? 1 : -1];
typedef char assert_PS2LiveCollision_unknown00[(((int) &((PS2LiveCollision *) 0)->unknown00) == 0) ? 1 : -1];
typedef char assert_PS2LiveCollision_object[(((int) &((PS2LiveCollision *) 0)->object) == 112) ? 1 : -1];
typedef char assert_PS2LiveCollision_unknown74[(((int) &((PS2LiveCollision *) 0)->unknown74) == 116) ? 1 : -1];
typedef char assert_PS2LiveCollision_state[(((int) &((PS2LiveCollision *) 0)->state) == 124) ? 1 : -1];
typedef char assert_PS2LiveCollision_size[(sizeof(PS2LiveCollision) == 128) ? 1 : -1];
typedef char assert_RecoveredAIActionEvent_kind[(((int) &((RecoveredAIActionEvent *) 0)->kind) == 0) ? 1 : -1];
typedef char assert_RecoveredAIActionEvent_payload[(((int) &((RecoveredAIActionEvent *) 0)->payload) == 4) ? 1 : -1];
typedef char assert_RecoveredAIActionEvent_size[(sizeof(RecoveredAIActionEvent) == 24) ? 1 : -1];
typedef char assert_RecoveredAIActionHeader_brain[(((int) &((RecoveredAIActionHeader *) 0)->brain) == 0) ? 1 : -1];
typedef char assert_RecoveredAIActionHeader_vtable[(((int) &((RecoveredAIActionHeader *) 0)->vtable) == 4) ? 1 : -1];
typedef char assert_RecoveredAIActionHeader_phase[(((int) &((RecoveredAIActionHeader *) 0)->phase) == 8) ? 1 : -1];
typedef char assert_RecoveredAIActionHeader_unknown0c[(((int) &((RecoveredAIActionHeader *) 0)->unknown0c) == 12) ? 1 : -1];
typedef char assert_RecoveredAIActionHeader_payload[(((int) &((RecoveredAIActionHeader *) 0)->payload) == 36) ? 1 : -1];
typedef char assert_RecoveredAIActionHeader_size[(sizeof(RecoveredAIActionHeader) == 40) ? 1 : -1];
typedef char assert_RecoveredAIActionPolicy_words[(((int) &((RecoveredAIActionPolicy *) 0)->words) == 0) ? 1 : -1];
typedef char assert_RecoveredAIActionPolicy_size[(sizeof(RecoveredAIActionPolicy) == 136) ? 1 : -1];
typedef char assert_RecoveredAICompletionRecord_interval[(((int) &((RecoveredAICompletionRecord *) 0)->interval) == 0) ? 1 : -1];
typedef char assert_RecoveredAICompletionRecord_deadline[(((int) &((RecoveredAICompletionRecord *) 0)->deadline) == 4) ? 1 : -1];
typedef char assert_RecoveredAICompletionRecord_complete[(((int) &((RecoveredAICompletionRecord *) 0)->complete) == 8) ? 1 : -1];
typedef char assert_RecoveredAICompletionRecord_result[(((int) &((RecoveredAICompletionRecord *) 0)->result) == 9) ? 1 : -1];
typedef char assert_RecoveredAICompletionRecord_unknown0a[(((int) &((RecoveredAICompletionRecord *) 0)->unknown0a) == 10) ? 1 : -1];
typedef char assert_RecoveredAICompletionRecord_policy[(((int) &((RecoveredAICompletionRecord *) 0)->policy) == 12) ? 1 : -1];
typedef char assert_RecoveredAICompletionRecord_size[(sizeof(RecoveredAICompletionRecord) == 148) ? 1 : -1];
typedef char assert_RecoveredAIQueuedActionEvent_kind[(((int) &((RecoveredAIQueuedActionEvent *) 0)->kind) == 0) ? 1 : -1];
typedef char assert_RecoveredAIQueuedActionEvent_event[(((int) &((RecoveredAIQueuedActionEvent *) 0)->event) == 4) ? 1 : -1];
typedef char assert_RecoveredAIQueuedActionEvent_size[(sizeof(RecoveredAIQueuedActionEvent) == 28) ? 1 : -1];
typedef char assert_RecoveredAIActionStack_kinds[(((int) &((RecoveredAIActionStack *) 0)->kinds) == 0) ? 1 : -1];
typedef char assert_RecoveredAIActionStack_records[(((int) &((RecoveredAIActionStack *) 0)->records) == 32) ? 1 : -1];
typedef char assert_RecoveredAIActionStack_count[(((int) &((RecoveredAIActionStack *) 0)->count) == 1216) ? 1 : -1];
typedef char assert_RecoveredAIActionStack_events[(((int) &((RecoveredAIActionStack *) 0)->events) == 1220) ? 1 : -1];
typedef char assert_RecoveredAIActionStack_eventCount[(((int) &((RecoveredAIActionStack *) 0)->eventCount) == 1808) ? 1 : -1];
typedef char assert_RecoveredAIActionStack_owner[(((int) &((RecoveredAIActionStack *) 0)->owner) == 1812) ? 1 : -1];
typedef char assert_RecoveredAIActionStack_actions[(((int) &((RecoveredAIActionStack *) 0)->actions) == 1816) ? 1 : -1];
typedef char assert_RecoveredAIActionStack_size[(sizeof(RecoveredAIActionStack) == 2112) ? 1 : -1];
typedef char assert_RecoveredAIController_unknown00[(((int) &((RecoveredAIController *) 0)->unknown00) == 0) ? 1 : -1];
typedef char assert_RecoveredAIController_state[(((int) &((RecoveredAIController *) 0)->state) == 48) ? 1 : -1];
typedef char assert_RecoveredAIController_update[(((int) &((RecoveredAIController *) 0)->update) == 52) ? 1 : -1];
typedef char assert_RecoveredAIController_routeFlag[(((int) &((RecoveredAIController *) 0)->routeFlag) == 53) ? 1 : -1];
typedef char assert_RecoveredAIController_unknown36[(((int) &((RecoveredAIController *) 0)->unknown36) == 54) ? 1 : -1];
typedef char assert_RecoveredAIController_routePending[(((int) &((RecoveredAIController *) 0)->routePending) == 57) ? 1 : -1];
typedef char assert_RecoveredAIController_unknown3a[(((int) &((RecoveredAIController *) 0)->unknown3a) == 58) ? 1 : -1];
typedef char assert_RecoveredAIController_active[(((int) &((RecoveredAIController *) 0)->active) == 64) ? 1 : -1];
typedef char assert_RecoveredAIController_modes[(((int) &((RecoveredAIController *) 0)->modes) == 68) ? 1 : -1];
typedef char assert_RecoveredAIController_size[(sizeof(RecoveredAIController) == 84) ? 1 : -1];
typedef char assert_RecoveredNodeGraph_pad00[(((int) &((RecoveredNodeGraph *) 0)->pad00) == 0) ? 1 : -1];
typedef char assert_RecoveredNodeGraph_nodeCount[(((int) &((RecoveredNodeGraph *) 0)->nodeCount) == 12) ? 1 : -1];
typedef char assert_RecoveredNodeGraph_pad10[(((int) &((RecoveredNodeGraph *) 0)->pad10) == 16) ? 1 : -1];
typedef char assert_RecoveredNodeGraph_nodes[(((int) &((RecoveredNodeGraph *) 0)->nodes) == 24) ? 1 : -1];
typedef char assert_RecoveredNodeGraph_pad1c[(((int) &((RecoveredNodeGraph *) 0)->pad1c) == 28) ? 1 : -1];
typedef char assert_RecoveredNodeGraph_heuristic[(((int) &((RecoveredNodeGraph *) 0)->heuristic) == 84) ? 1 : -1];
typedef char assert_RecoveredNodeGraph_cost[(((int) &((RecoveredNodeGraph *) 0)->cost) == 88) ? 1 : -1];
typedef char assert_RecoveredNodeGraph_size[(sizeof(RecoveredNodeGraph) == 92) ? 1 : -1];
typedef char assert_RecoveredNodeSearch_result[(((int) &((RecoveredNodeSearch *) 0)->result) == 0) ? 1 : -1];
typedef char assert_RecoveredNodeSearch_pad04[(((int) &((RecoveredNodeSearch *) 0)->pad04) == 4) ? 1 : -1];
typedef char assert_RecoveredNodeSearch_origin[(((int) &((RecoveredNodeSearch *) 0)->origin) == 16) ? 1 : -1];
typedef char assert_RecoveredNodeSearch_cursor[(((int) &((RecoveredNodeSearch *) 0)->cursor) == 32) ? 1 : -1];
typedef char assert_RecoveredNodeSearch_candidates[(((int) &((RecoveredNodeSearch *) 0)->candidates) == 36) ? 1 : -1];
typedef char assert_RecoveredNodeSearch_candidateCount[(((int) &((RecoveredNodeSearch *) 0)->candidateCount) == 292) ? 1 : -1];
typedef char assert_RecoveredNodeSearch_active[(((int) &((RecoveredNodeSearch *) 0)->active) == 296) ? 1 : -1];
typedef char assert_RecoveredNodeSearch_pad129[(((int) &((RecoveredNodeSearch *) 0)->pad129) == 297) ? 1 : -1];
typedef char assert_RecoveredNodeSearch_size[(sizeof(RecoveredNodeSearch) == 304) ? 1 : -1];
typedef char assert_RecoveredRouteNode_id[(((int) &((RecoveredRouteNode *) 0)->id) == 0) ? 1 : -1];
typedef char assert_RecoveredRouteNode_position[(((int) &((RecoveredRouteNode *) 0)->position) == 4) ? 1 : -1];
typedef char assert_RecoveredRouteNode_graph[(((int) &((RecoveredRouteNode *) 0)->graph) == 16) ? 1 : -1];
typedef char assert_RecoveredRouteNode_size[(sizeof(RecoveredRouteNode) == 20) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_owner[(((int) &((RecoveredRouteRequest *) 0)->owner) == 0) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_next[(((int) &((RecoveredRouteRequest *) 0)->next) == 4) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_kind[(((int) &((RecoveredRouteRequest *) 0)->kind) == 8) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_result[(((int) &((RecoveredRouteRequest *) 0)->result) == 12) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_origin[(((int) &((RecoveredRouteRequest *) 0)->origin) == 16) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_destination[(((int) &((RecoveredRouteRequest *) 0)->destination) == 32) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_startNode[(((int) &((RecoveredRouteRequest *) 0)->startNode) == 48) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_endNode[(((int) &((RecoveredRouteRequest *) 0)->endNode) == 52) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_originLifted[(((int) &((RecoveredRouteRequest *) 0)->originLifted) == 56) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_destinationLifted[(((int) &((RecoveredRouteRequest *) 0)->destinationLifted) == 68) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_storage[(((int) &((RecoveredRouteRequest *) 0)->storage) == 80) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_firstPoint[(((int) &((RecoveredRouteRequest *) 0)->firstPoint) == 84) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_busy[(((int) &((RecoveredRouteRequest *) 0)->busy) == 88) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_pad59[(((int) &((RecoveredRouteRequest *) 0)->pad59) == 89) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_elapsed[(((int) &((RecoveredRouteRequest *) 0)->elapsed) == 92) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_reuse[(((int) &((RecoveredRouteRequest *) 0)->reuse) == 96) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_pad61[(((int) &((RecoveredRouteRequest *) 0)->pad61) == 97) ? 1 : -1];
typedef char assert_RecoveredRouteRequest_size[(sizeof(RecoveredRouteRequest) == 112) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_pad00[(((int) &((RecoveredRouteStorage *) 0)->pad00) == 0) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_graph[(((int) &((RecoveredRouteStorage *) 0)->graph) == 4) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_count[(((int) &((RecoveredRouteStorage *) 0)->count) == 8) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_nodeIds[(((int) &((RecoveredRouteStorage *) 0)->nodeIds) == 12) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_links[(((int) &((RecoveredRouteStorage *) 0)->links) == 16) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_points[(((int) &((RecoveredRouteStorage *) 0)->points) == 20) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_edgeData[(((int) &((RecoveredRouteStorage *) 0)->edgeData) == 24) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_field1c[(((int) &((RecoveredRouteStorage *) 0)->field1c) == 28) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_field20[(((int) &((RecoveredRouteStorage *) 0)->field20) == 32) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_pad21[(((int) &((RecoveredRouteStorage *) 0)->pad21) == 33) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_field24[(((int) &((RecoveredRouteStorage *) 0)->field24) == 36) ? 1 : -1];
typedef char assert_RecoveredRouteStorage_size[(sizeof(RecoveredRouteStorage) == 40) ? 1 : -1];

#endif
