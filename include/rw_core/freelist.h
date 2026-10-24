#ifndef BLACK_RENDERWARE_CORE_FREELIST_H
#define BLACK_RENDERWARE_CORE_FREELIST_H
#include "ps2/prelude.h"
/* UNVERIFIED PS2 free-list block and bitmap layout. */
typedef struct RwFreeLinkPS2 {struct RwFreeLinkPS2 *next,*previous;} RwFreeLinkPS2;
typedef struct RwFreeListPS2 {
 u32 entry_size,entries_per_block,bitmap_bytes,alignment;
 RwFreeLinkPS2 blocks;u32 flags;RwFreeLinkPS2 global;
} RwFreeListPS2;
typedef char RwFreeListPS2_flags_offset[(unsigned)&((RwFreeListPS2 *)0)->flags==0x18?1:-1];
#endif
