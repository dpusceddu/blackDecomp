#ifndef KYNAPSE_NAME_REGISTRIES_H
#define KYNAPSE_NAME_REGISTRIES_H
#include "ps2/prelude.h"

/* Partial C views of the fixed-capacity registries. Exact class lookup confirms
 * its record name at +8 and registry count at +0x400; exact lazy singleton
 * accessors also confirm the count offsets. UNVERIFIED: complete record extents,
 * inline name capacity and value-record accesses remain provisional. The
 * 16-entry tables resolve pathfinder strategy objects; their concrete
 * interfaces remain unknown. */
typedef struct {
    u8 unk_00[8];
    char name[1]; // UNVERIFIED: inline name capacity is not established.
} Recovered_NamedClassRecord;

typedef struct {
    Recovered_NamedClassRecord* slots[256];
    s32 count;
} Recovered_NamedClassRegistry;

typedef struct {
    u32 unk_00;
    char name[256];
    void* value;
} Recovered_NamedValueRecord;

typedef struct {
    Recovered_NamedValueRecord* slots[16];
    s32 count;
} Recovered_NamedValueRegistry;

typedef char NamedClassRegistryCount[(u32) & ((Recovered_NamedClassRegistry*)0)->count == 0x400 ? 1 : -1];
typedef char NamedValueRegistryCount[(u32) & ((Recovered_NamedValueRegistry*)0)->count == 0x40 ? 1 : -1];
typedef char NamedValueRecordValue[(u32) & ((Recovered_NamedValueRecord*)0)->value == 0x104 ? 1 : -1];

Recovered_NamedClassRecord* func_00393978(const char* name);
void* func_00393A18(const char* name);
void* func_00393AC0(const char* name);
void* func_00393B68(const char* name);
void* func_00393C10(const char* name);
#endif
