#ifndef GAME_RESOURCE_VALUE_H
#define GAME_RESOURCE_VALUE_H
#include "game/value_ratio.h"

/* The snapshot is copied as 28 native bytes. Only the two unsigned values
 * consumed by the native accessors have known widths; wider semantics and
 * unused bytes remain UNVERIFIED. */
typedef struct {
    u32 value;
    u8 unk_04[4];
    u32 scaledValue;
    u8 unk_0C[16];
} Recovered_ResourceValueMetadata;

typedef struct {
    u32 unk_00;
    const char* name;
    u8 unk_08[8];
    Recovered_ResourceValueMetadata metadata;
} Recovered_ResourceValueDescriptor;

typedef struct {
    Recovered_ValueRatioSource base;
    Recovered_ResourceValueDescriptor* descriptor;
} Recovered_ResourceValue;

typedef char ResourceValueMetadataSize[sizeof(Recovered_ResourceValueMetadata) == 0x1C ? 1 : -1];
typedef char ResourceValueDescriptorOffset[(u32)&((Recovered_ResourceValue*)0)->descriptor == 0x18 ? 1 : -1];
typedef char ResourceValueStride[sizeof(Recovered_ResourceValue) == 0x20 ? 1 : -1];

void ResourceValue_Initialize(Recovered_ResourceValue* self);
void ResourceValue_Bind(Recovered_ResourceValue* self, Recovered_ResourceValueDescriptor* descriptor, s32 convert);
f32 ResourceValue_Get(Recovered_ResourceValue* self);
u32 ResourceValue_GetScaled(Recovered_ResourceValue* self);
#endif
