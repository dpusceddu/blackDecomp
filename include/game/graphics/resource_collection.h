#ifndef BLACK_GRAPHICS_RESOURCE_COLLECTION_H
#define BLACK_GRAPHICS_RESOURCE_COLLECTION_H
#include "ps2/prelude.h"

/* The insertion helper confirms count/total at 0/4 and the pointer array at 8.
 * UNVERIFIED: original identity, capacity and the units of each resource's word at 0x64. */
typedef struct {
    s32 count, total;
    void* items[0];
} BkResourceCollectionPS2;
typedef char ResourceCollectionItemsOffset[(u32) & ((BkResourceCollectionPS2*)0)->items == 8 ? 1 : -1];
#endif
