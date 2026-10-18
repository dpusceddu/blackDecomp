#ifndef BLACK_EFFECTS_POOL_H
#define BLACK_EFFECTS_POOL_H
#include "auto/prelude.h"
/* Inferred effect names; field offsets and strides are observed on PS2. */
typedef struct BkEffectEntryPS2 { u8 prefix[0x60]; void *resource; u8 suffix[0xc]; } BkEffectEntryPS2;
typedef struct BkEffectResourcePS2 {
 u8 prefix[0x18]; void **effects; u8 unknown1c[0x16]; u16 effectCount;
} BkEffectResourcePS2;
typedef struct BkEffectPoolPS2 {
 BkEffectEntryPS2 entries[0x300]; u8 unknown15000[0x5000];
 u16 *indices, *reverseIndices; u16 activeCount,capacity; void *owner; BkEffectResourcePS2 *resource; f32 time; u16 pendingCount;
} BkEffectPoolPS2;
typedef struct BkEffectBatchPS2 {
 BkEffectEntryPS2 *entries; s16 entryCount; u16 flags; u8 *enabled;
 u8 unknownc[4]; void *material;
} BkEffectBatchPS2;
typedef struct BkEffectBucketPS2 { void *material; BkEffectBatchPS2 *batches[12]; u8 count; u8 padding[3]; } BkEffectBucketPS2;
typedef struct BkEffectRecordPS2 { s128 vectors[0x11]; } BkEffectRecordPS2;
typedef struct BkEffectRecordsPS2 { s32 count; u8 padding[0xc]; BkEffectRecordPS2 records[1]; } BkEffectRecordsPS2;
#endif
