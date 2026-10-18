#ifndef BLACK_EFFECTS_EMITTER_H
#define BLACK_EFFECTS_EMITTER_H
#include "game/effects/vector.h"
/* Inferred names; PS2 record strides and accessed offsets only. */
typedef struct {s128 transform[4];char *resource;u32 unknown44;f32 birthTime,lastUpdate;s128 ranges[5];f32 rate,expiry;void *owner;u32 flags;} BkEffectEmitterRecordPS2;
typedef struct BkEffectEmitterNodePS2 {struct BkEffectEmitterNodePS2 *next;u8 unknown[0x18];} BkEffectEmitterNodePS2;
typedef struct {u8 prefix[0x28];void *emitterDefs;u8 unknown2c[0xa];u16 emitterCount;} BkEffectEmitterResourcePS2;
typedef struct {
 BkEffectEmitterRecordPS2 records[1024];BkEffectEmitterResourcePS2 *resource;BkEffectEmitterNodePS2 nodes[256];
 BkEffectEmitterNodePS2 *freeHead;u32 count0,count1;void *emitters;u16 *indices,*reverseIndices;u16 activeCount,capacity,emitterCount;
} BkEffectEmittersPS2;
typedef struct {u8 prefix[0x40];void *resource;u8 suffix[0x1c];} BkEffectLightPS2;
typedef struct { BkEffectLightPS2 lights[256];void *resource;char *definitions;u32 activeCount;u16 definitionCount; } BkEffectLightsPS2;
#endif
