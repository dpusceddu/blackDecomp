#include "game/graphics/resource_collection.h"

void func_001C8420(BkResourceCollectionPS2* collection, void* item) {
    s32 i;
    for (i = 0; i < collection->count; i++) {
        if (collection->items[i] == item) return;
    }
    collection->items[collection->count++] = item;
    collection->total += M2C_FIELD(item, s32*, 0x64);
}
