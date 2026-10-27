#include "ps2/prelude.h"

/* Accessed collection prefix; the full allocation and original field names remain UNVERIFIED. */
typedef struct {
    s32 count, total;
    void* items[0];
} ResourceCollection;
void func_001C8420(ResourceCollection* collection, void* item) {
    s32 i;
    for (i = 0; i < collection->count; i++) {
        if (collection->items[i] == item) return;
    }
    collection->items[collection->count++] = item;
    collection->total += M2C_FIELD(item, s32*, 0x64);
}
