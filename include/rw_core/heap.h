#ifndef BLACK_RENDERWARE_CORE_HEAP_H
#define BLACK_RENDERWARE_CORE_HEAP_H
#include "ps2/prelude.h"
/* UNVERIFIED PS2 allocator access views; confirm with a matching typed consumer. */
typedef struct RwHeapBlockPS2 RwHeapBlockPS2;
typedef struct RwHeapEntryPS2 { u32 bytes; RwHeapBlockPS2 *block; } RwHeapEntryPS2;
struct RwHeapBlockPS2 { RwHeapBlockPS2 *previous, *next; u32 bytes; RwHeapEntryPS2 *free_entry; u32 reserved[4]; };
typedef struct RwHeapSegmentPS2 { RwHeapBlockPS2 *start; u32 bytes; struct RwHeapSegmentPS2 *next; } RwHeapSegmentPS2;
typedef struct RwHeapPS2 { u32 bytes; RwHeapSegmentPS2 *segments; RwHeapBlockPS2 *first; RwHeapEntryPS2 *entries; u32 capacity, count; s32 dirty; } RwHeapPS2;
typedef char RwHeapPS2_count_offset[(unsigned)&((RwHeapPS2 *)0)->count == 0x14 ? 1 : -1];
#endif
