#ifndef BLACK_RENDERWARE_CORE_PLUGIN_H
#define BLACK_RENDERWARE_CORE_PLUGIN_H
#include "auto/prelude.h"
/* VERIFIED accessed fields: the matched plugin destructor walk uses these offsets.
   Remaining members are PS2 access views, not allocation-size assertions. */
typedef struct RwPluginPS2 RwPluginPS2;
typedef struct RwRegistryPS2 RwRegistryPS2;
struct RwRegistryPS2 { s32 size, original_size, max_size, static_alloc; RwPluginPS2 *first, *last; };
struct RwPluginPS2 { s32 offset, size, id; void *read, *write, *stream_size, *always, *rights; void *construct, *destruct, *copy; s32 unknown; RwPluginPS2 *next, *previous; RwRegistryPS2 *registry; };
typedef char RwPluginPS2_next_offset[(unsigned)&((RwPluginPS2 *)0)->next == 0x30 ? 1 : -1];
#endif
