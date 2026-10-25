#ifndef RWA_EE_IO_CACHE_H
#define RWA_EE_IO_CACHE_H
#include "ps2/prelude.h"
/* DMA fallback buffer followed by its observed four-word cache state. */
typedef struct AudioIoCache {u8 buffer[8192];void*owner;s32 file;u32 position,bytes;}AudioIoCache;
#endif
